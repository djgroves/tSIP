#ifndef FormMessageH
#define FormMessageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TfrmMessage : public TForm
{
__published:	// IDE-managed Components
	TRichEdit *memoMain;
	TPanel *pnlBottom;
    TMemo *memoInput;
	TPanel *pnlTop;
	TLabel *lblNumber;
	TEdit *edTarget;
	TPanel *pnlButtons;
	TButton *btnSend;
	TSpeedButton *btnSendOnEnter;
    void __fastcall memoInputKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall btnSendOnEnterClick(TObject *Sender);
    void __fastcall btnSendClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
	AnsiString target;
	bool incoming;
public:		// User declarations
	__fastcall TfrmMessage(TComponent* Owner);
	void __fastcall MyWndProc (Messages::TMessage &Msg);
	void _SendMsg();
	void SetTarget(AnsiString target);
	AnsiString GetTarget(void) {
		return target;
	}
	void SetIncoming(void) {
		incoming = true;
	}
	bool GetIncoming(void) {
    	return incoming;
	}
	void AddIncomingMessage(AnsiString contentType, AnsiString body);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMessage *frmMessage;
//---------------------------------------------------------------------------
#endif

