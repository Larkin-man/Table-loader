//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TableLoader_Test.h"
//---------------------------------------------------------------------------
//#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)	: TForm(Owner)
{
	ti.IgnoreFirstString = true;
	IgnoreDelimPack->Checked = ti.IgnoreDelimitersPack;
	IgnoreFirstString->Checked = ti.IgnoreFirstString;
	List = NULL;
	pInt[0]=NULL; pInt[1]=NULL; pInt[2]=NULL; pInt[3]=NULL;
	pS1=NULL; pS2=NULL; pChar1=NULL; pChar2=NULL; pBool1=NULL;
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
//ЗАГРУЗКА ИЗ ФАЙЛА
void __fastcall TForm1::LoadFromFileBtnClick(TObject *Sender)
{
	Tick = ::GetTickCount();
	pInt[3] = NULL;
	try {
//		ti.LoadFromFile(File->Text, "iiscs"//Edit3->Text.c_str()
//			, &pInt[0], &pInt[1], &pS1, &pChar1, &pBool1, &pS2);
		ti.LoadFromFile(File->Text, "i0ssics"//Edit3->Text.c_str()
		, &pInt[0], &pS1, &pBool1, &pInt[1], &pChar1, &pS2);
		//ti.LoadFromFile(Edit1->Text, "0i", &pInt[1] );
		StatusBar1Click(NULL);
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
		StatusBar1Click(NULL);
		return;
	}
	//Дополнительный столбец
//	if (pInt[2])
//		for (int i = 0; i < ti.RowCount; ++i)
//			pInt[2][i] = i;
	//Print(ti.RowCount);
}
//---------------------------------------------------------------------------
//ЗАГРУЗКА С ЛИСТА
void __fastcall TForm1::LoadFromListClick(TObject *Sender)
{
	pInt[3] = NULL;
	Tick = ::GetTickCount();
	try {
	//ti.LoadFromList(Rich->Lines, "iiscs"//Edit3->Text.c_str()
	//	, &pInt[0], &pInt[1], &pS1, &pChar1, &pBool1, &pS2);
	ti.LoadFromList(Rich->Lines, "i0ssics"//Edit3->Text.c_str()
		, &pInt[0], &pS1, &pBool1, &pInt[1], &pChar1, &pS2);
	StatusBar1Click(NULL);
	//ti.LoadFromFile(Edit1->Text, "si", &pS1, &pId);
	//iIiscbCs
	//ti.Load(Edit1->Text, Edit3->Text.c_str(), &pId, &pI, &pK, &pS1, &ch, &b, &pC, &pS2);
	}
	catch (EFOpenError& m)
	{
		ShowMessage (m.Message);
		StatusBar1Click(NULL);
		return;
	}
	Print(ti.RowCount > 1024 ? 1024 : ti.RowCount);
	RicheD->Checked = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::GetSectionClick(TObject *Sender)
{
	int Count = ti.GetSection(Edit2->Text, &pInt[0], &pInt[1], &pS1, &pChar1, &pBool1, &pS2);
	ShowMessage(IntToStr(Count)+" строчки.");
	Print(Count);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ResourClick(TObject *Sender)
{
	//TResourceStream* ptRes = new TResourceStream((int)HInstance, "UNITXT","RT_RCDATA");
	String dd = "UNITXT";
	//wchar_t hhh = dd.
	TResourceStream *ptRes = new TResourceStream(0,"UNITXT", L"RT_RCDATA");
	//Можно и сохранить
	//ptRes->SaveToFile("readme.txt");
	//Загружаем ресурс
	Sections->Lines->LoadFromStream(ptRes);
	delete ptRes;
}
//---------------------------------------------------------------------------

void TForm1::Print(int Count)
{
	if (pInt[3] == NULL) //Рег [3] на [1]
	  ti.RegColumn(pInt[3], 2);
	for (int i=0; i < Count; ++i)
	{
   	if (pInt[0])
			Grid->Cells[0][i] = pInt[0][i];
		//Grid->Cells[1][i] = pInt[3][i]; //pInt3[i]; там рег на 2
      if (pInt[1])
      	Grid->Cells[1][i] = pInt[1][i]; //pInt3[i]; там рег на 2
      if (pS1)
			Grid->Cells[2][i] = pS1[i];
      if (pChar1)
			Grid->Cells[3][i] = pChar1[i];
      if (pBool1)
			Grid->Cells[4][i] = (int)pBool1[i];
      if (pS2)
			Grid->Cells[5][i] = pS2[i];
	}
	Sections->Clear();
	for (int i = 0; i < ti.SectionCount; ++i)
		Sections->Lines->Add(*ti.Sections[i].Name+" " + IntToStr(ti.Sections[i].Pos)+" "+ IntToStr(ti.Sections[i].Size));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StatusBar1Click(TObject *Sender)
{
	int C[4];
	ti.GetCount(C[0], C[1], C[2], C[3]);
	StatusBar1->Panels->Items[0]->Text = "Row="+IntToStr(ti.RowCount)
		+"  Col="+IntToStr(ti.ColCount)+"  SectionC="+IntToStr(ti.SectionCount)
		+"   Int="+IntToStr(C[0]) + "  Str="+IntToStr(C[3])
		+"  Char="+IntToStr(C[1]) + "  Bool="+IntToStr(C[2]);
	if (Sender == NULL)
	{
		Tick = ::GetTickCount() - Tick;  //Вычислить время расчета
		StatusBar1->Panels->Items[0]->Text = StatusBar1->Panels->Items[0]->Text +
			" Время загрузки : "+FloatToStr(Tick)+" миллисек.";
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RicheDClick(TObject *Sender)
{
	Rich->Visible = RicheD->Checked;
	Grid->Visible = !RicheD->Checked;
	if	(Rich->Lines->Count < 2)		//if	(List == NULL)
	{
		//List->LoadFromFile(Edit1->Text);
		//List->Assign(Rich->Lines);
		Rich->Align = alClient;
		Rich->Lines->LoadFromFile(File->Text);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	delete List;
}
//---------------------------------------------------------------------------

