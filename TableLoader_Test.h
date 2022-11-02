//---------------------------------------------------------------------------

#ifndef TableLoader_TestH
#define TableLoader_TestH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TableLoader.h"
#include <Grids.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *Grid;
	TEdit *Edit1;
	TButton *Load;
	TMemo *Sections;
	TCheckBox *IgnoreDelimPack;
	TCheckBox *IgnoreFirstString;
	TEdit *Edit2;
	TButton *GetSection;
	TButton *Button1;
	TEdit *Edit3;
	TPopupMenu *PopupMenu1;
	TMenuItem *GetCount1;
	TButton *Resour;
	TCheckBox *FromFile;
	void __fastcall IgnoreDelimPackClick(TObject *Sender);
	void __fastcall IgnoreFirstStringClick(TObject *Sender);
	void __fastcall LoadClick(TObject *Sender);
	void __fastcall GetSectionClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall GetCount1Click(TObject *Sender);
	void __fastcall ResourClick(TObject *Sender);
	void __fastcall FromFileClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	TableLoader ti;
	int *pId , *pK, *pI;
   UnicodeString *pS1, *pS2;
   char *ch, *pC;
	bool *b;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
