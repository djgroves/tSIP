#include <vcl.h>
#pragma hdrstop

#include "FormMessage.h"
#include "SIMPLE_Messages.h"
#include "Settings.h"
#include "ControlQueue.h"

#include <stdio.h>
#include <time.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMessage *frmMessage;

//---------------------------------------------------------------------------
__fastcall TfrmMessage::TfrmMessage(TComponent* Owner)
	: TForm(Owner),
	incoming(false)
{
	SIMPLE_Messages::RegisterWindow(this);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMessage::MyWndProc (Messages::TMessage &Msg)
{
    if (Msg.Msg == WM_NOTIFY)
    {
		if (((NMHDR*)Msg.LParam)->code == EN_LINK)
        {
            ENLINK *E = (ENLINK*)Msg.LParam;
            if (E->msg == WM_LBUTTONDBLCLK)
				ShellExecute (NULL, NULL, memoMain->Text.SubString(E->chrg.cpMin + 1, E->chrg.cpMax - E->chrg.cpMin).c_str(), NULL, NULL, SW_SHOW);
		}
    }
	else
	{
		WndProc (Msg);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMessage::memoInputKeyDown(TObject *Sender, WORD &Key,
        TShiftState Shift)
{
	if (Key == VK_RETURN && !Shift.Contains(ssCtrl) && !memoInput->WantReturns && memoInput->Text != "")
	{
		_SendMsg();
	}
}
//---------------------------------------------------------------------------
void TfrmMessage::_SendMsg()
{
    edTarget->Enabled = false;
	AnsiString target = edTarget->Text;
	AnsiString msg = memoInput->Lines->Text;

	UA->SendMessage(0, target, ::AnsiToUtf8(msg));

    memoMain->SelStart = memoMain->Lines->Text.Length();

    memoMain->SelAttributes->Size = 8;
    memoMain->SelAttributes->Style = TFontStyles() << fsBold;
    memoMain->SelAttributes->Color = clDkGray;
    memoMain->Paragraph->FirstIndent = 0;
    memoMain->Lines->Add ("Me: (" + TimeToStr (Time())+ ") ");

    memoMain->SelAttributes->Size = 10;
    memoMain->SelAttributes->Style = TFontStyles();
    memoMain->SelAttributes->Color = clBlue;
    memoMain->Paragraph->FirstIndent = 10;
    memoMain->Lines->Add (msg);

    SendMessage (memoMain->Handle, WM_VSCROLL, SB_BOTTOM, NULL);

    memoInput->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMessage::FormCreate(TObject *Sender)
{
    SetWindowLong (Handle, GWL_EXSTYLE, GetWindowLong (Handle, GWL_EXSTYLE) | WS_EX_APPWINDOW);

    SendMessage (memoMain->Handle, EM_AUTOURLDETECT, TRUE, 0);
    SendMessage (memoMain->Handle, EM_SETEVENTMASK, 0, ENM_LINK);
    WindowProc = MyWndProc;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMessage::btnSendOnEnterClick(TObject *Sender)
{
	memoInput->WantReturns = !btnSendOnEnter->Down;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMessage::btnSendClick(TObject *Sender)
{
	if (memoInput->Lines->Text != "")
	{
		_SendMsg();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMessage::FormClose(TObject *Sender, TCloseAction &Action)
{
	SIMPLE_Messages::UnregisterWindow(this);
	Action = caFree;
}
//---------------------------------------------------------------------------

void TfrmMessage::SetTarget(AnsiString target)
{
	this->target = target;
	edTarget->Text = target;
	edTarget->Enabled = false;
}

void TfrmMessage::AddIncomingMessage(AnsiString contentType, AnsiString body)
{
	if (contentType == "text/plain")
	{
    	body = ::Utf8ToAnsi(body);
	}
    memoMain->SelStart = memoMain->Lines->Text.Length();
    memoMain->SelAttributes->Size = 8;
    memoMain->SelAttributes->Style = TFontStyles() << fsBold;
    memoMain->SelAttributes->Color = clBlack;
    memoMain->Paragraph->FirstIndent = 0;

    int current_time = time(NULL);
    char buf [30];
	tm *t;
	t = localtime ((long*)&current_time);
	strftime (buf, sizeof (buf), "%H:%M:%S", t);
	int TODO__PEER_DISPLAY;
	memoMain->Lines->Add ((AnsiString)"Peer: (" + buf + ") ");

    memoMain->SelAttributes->Size = 10;
    memoMain->SelAttributes->Style = TFontStyles();
    memoMain->SelAttributes->Color = clRed;
    memoMain->Paragraph->FirstIndent = 10;
    memoMain->Lines->Add (body);

    SendMessage (memoMain->Handle, WM_VSCROLL, SB_BOTTOM, NULL);

	FLASHWINFO f = {sizeof (f), Handle, FLASHW_TRAY | FLASHW_TIMERNOFG, 0, 0};
	if (GetForegroundWindow() != Handle)
    {
        FlashWindowEx (&f);
//            PlaySound(..., NULL, SND_ASYNC | SND_FILENAME);
	}
}

