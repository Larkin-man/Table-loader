//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TableLoader_Test.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	IgnoreDelimPack->Checked = ti.IgnoreDelimitersPack;
	IgnoreFirstString->Checked = ti.IgnoreFirstString;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::IgnoreDelimPackClick(TObject *Sender)
{
	ti.IgnoreDelimitersPack = IgnoreDelimPack->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::IgnoreFirstStringClick(TObject *Sender)
{
	ti.IgnoreFirstString = IgnoreFirstString->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LoadClick(TObject *Sender)
{
	try {
	ti.Load(Edit1->Text, FromFile->Checked, Edit3->Text.c_str(), &pId, &pK, &pS1, &ch, &b, &pS2);
	//ti.LoadFromFile(Edit1->Text, "si", &pS1, &pId);
	//iIiscbCs
	//ti.Load(Edit1->Text, FromFile->Checked, Edit3->Text.c_str(), &pId, &pI, &pK, &pS1, &ch, &b, &pC, &pS2);
	}
	catch (EFOpenError& m)
	{
		ShowMessage (m.Message);
		return;
	}
	for (int i=0; i<ti.RowCount; ++i)
	{
		Grid->Cells[0][i] = pId[i];
		Grid->Cells[1][i] = pK[i];
		Grid->Cells[2][i] = pS1[i];
		Grid->Cells[3][i] = ch[i];
		Grid->Cells[4][i] = (int)b[i];
		Grid->Cells[5][i] = pS2[i];
			/*Grid->Cells[6][i] = pI[i];
         pC[i] = i+64;
			Grid->Cells[7][i] = pC[i];       */
		//Grid->Cells[0][i] = pS1[i];
		//Grid->Cells[1][i] = pId[i];
	}
	Sections->Clear();
	for (int i = 0; i < ti.SectionCount; ++i)
	{
		Sections->Lines->Add(*ti.Sections[i].Name+" " + IntToStr(ti.Sections[i].Pos)+" "+ IntToStr(ti.Sections[i].Size));
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::GetSectionClick(TObject *Sender)
{
	int Count = ti.GetSection(Edit2->Text, &pId, &pK, &pS1, &ch, &b, &pS2);
	for (int i=0; i<Count; ++i)
	{
		Grid->Cells[0][i] = pId[i];
		Grid->Cells[1][i] = pK[i];
		Grid->Cells[2][i] = pS1[i];
		Grid->Cells[3][i] = ch[i];
		Grid->Cells[4][i] = (int)b[i];
		Grid->Cells[5][i] = pS2[i];
	}
  	//for (int i=0; i<Count; ++i)
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	Sections->Lines->Add((*ti.Sections[1].Name)[1]);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GetCount1Click(TObject *Sender)
{
	int C[4];
	ti.GetCount(C[0], C[1], C[2], C[3]);
	Sections->Lines->Add("Int="+IntToStr(C[0]));
	Sections->Lines->Add("Char="+IntToStr(C[1]));
	Sections->Lines->Add("Bool="+IntToStr(C[2]));
	Sections->Lines->Add("Str="+IntToStr(C[3]));
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ResourClick(TObject *Sender)
{
	//TResourceStream* ptRes = new TResourceStream((int)HInstance, "UNITXT","RT_RCDATA");
	UnicodeString dd = "UNITXT";
	//wchar_t hhh = dd.
	TResourceStream *ptRes = new TResourceStream(0,"UNITXT", L"RT_RCDATA");
	//Можно и сохранить
	//ptRes->SaveToFile("readme.txt");
	//Загружаем ресурс
	Sections->Lines->LoadFromStream(ptRes);
	delete ptRes;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FromFileClick(TObject *Sender)
{
	Edit1->Text = "UNITXT";
}
//---------------------------------------------------------------------------

