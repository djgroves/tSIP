//---------------------------------------------------------------------------

#ifndef FormContactsH
#define FormContactsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------

#include "common/Observer.h"
#include "Contacts.h"

class TfrmContacts : public TForm, Observer
{
__published:	// IDE-managed Components
	TListView *lvContacts;
	TPanel *pnlBottom;
	TEdit *edFilter;
	TImage *imgFilter;
	TPopupMenu *pupupContactList;
	TMenuItem *miAdd;
	TMenuItem *miEdit;
	TMenuItem *miDelete;
	TMenuItem *miCall;
	void __fastcall lvContactsData(TObject *Sender, TListItem *Item);
	void __fastcall lvContactsDblClick(TObject *Sender);
	void __fastcall pupupContactListPopup(TObject *Sender);
	void __fastcall miAddClick(TObject *Sender);
	void __fastcall miCallItemClick(TObject *Sender);
	void __fastcall miEditClick(TObject *Sender);
	void __fastcall miDeleteClick(TObject *Sender);
	void __fastcall edFilterChange(TObject *Sender);
	void __fastcall edFilterKeyPress(TObject *Sender, char &Key);
public:
	typedef void (__closure *CallbackCall)(AnsiString uri);
private:	// User declarations
	Contacts *contacts;
	CallbackCall callbackCall;
	struct FilteredEntry
	{
		int id;
		Contacts::Entry entry;
	};
	std::vector<FilteredEntry> filteredContacts;
	void FilterContacts(void);
	bool filterUsingNote;
	bool storeNoteInSeparateFile;
	TMenuItem *CreateCallItem(AnsiString uri, TPopupMenu *Owner);
public:		// User declarations
	__fastcall TfrmContacts(TComponent* Owner, Contacts *contacts, CallbackCall callbackCall);
	void obsUpdate(Observable* o, Argument * arg);
	void FilterUsingNote(bool state) {
		filterUsingNote = state;
	}
	void StoreNoteInSeparateFile(bool state) {
		storeNoteInSeparateFile = state;
	}
	void Scale(int percentage);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmContacts *frmContacts;
//---------------------------------------------------------------------------
#endif
