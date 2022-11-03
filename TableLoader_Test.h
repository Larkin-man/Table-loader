//---------------------------------------------------------------------------
#ifndef TableLoader_TestH
#define TableLoader_TestH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TableLoader.cpp"
#include <Grids.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *Grid;
	TPopupMenu *PopupMenu1;
	TMenuItem *GetCount1;
	TStatusBar *StatusBar1;
	TPanel *Panel1;
	TEdit *Edit1;
	TEdit *Edit3;
	TCheckBox *IgnoreDelimPack;
	TCheckBox *IgnoreFirstString;
	TButton *LoadFromFileBtn;
	TButton *Resour;
	TEdit *Edit2;
	TButton *GetSection;
	TButton *Button1;
	TMemo *Sections;
	TRichEdit *Rich;
	TPanel *Panel2;
	TButton *LoadFromList;
	TCheckBox *RicheD;
	void __fastcall IgnoreDelimPackClick(TObject *Sender);
	void __fastcall IgnoreFirstStringClick(TObject *Sender);
	void __fastcall LoadFromFileBtnClick(TObject *Sender);
	void __fastcall GetSectionClick(TObject *Sender);
	void __fastcall ResourClick(TObject *Sender);
	void __fastcall StatusBar1Click(TObject *Sender);
	void __fastcall RicheDClick(TObject *Sender);
	void __fastcall LoadFromListClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	TableLoader ti;
	//int *pInt1 , *pInt2, *pInt3;
	int *pInt[4];
	String *pS1, *pS2;
	Char *pChar1, *pChar2;
	bool *pBool1;
	void Print(int Count);
	TStringList *List;
	DWORD Tick;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
