// Copyright 2022 Larkin
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//     http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// See the License for the specific language governing permissions and
// limitations under the License.
/******************************************************************\
* TableLoader - �������� ������ �� ��������� ������. ������ 1.1    *
\******************************************************************/
#ifndef TableLoaderH
#define TableLoaderH

class TableLoader
{
private:
   char *FFormat;
   //Mem ����������� [Count][FRowCount]
   AnsiString **MemStr;
   int **MemInt;
   char **MemChar;
   bool **MemBool;
   int StrCount, IntCount, CharCount, BoolCount;
   int FRowCount;
   int FColCount;

protected:    
   struct Section
   {
      AnsiString *Name;
      int Pos; //������� ������ � 0
      int Size;//���-�� �����
   } *FSections;
   void SectionEnsureCapacity(int count);
   int SectionCapacity;
   int FSectionCount;

public:     
   __fastcall TableLoader();
   __property char* Format = {read = FFormat};
   __property int RowCount = {read = FRowCount};
   __property int ColCount = {read = FColCount};
   __property int SectionCount = {read = FSectionCount};
   __property Section* Sections = {read = FSections};
   Section* FindSection(AnsiString SectionName);
   bool IgnoreFirstString; //������������ ������ ����� � �����. defaul=true
   bool IgnoreDelimitersPack; //������������ �����������, ������ ������. defauly=true
   char Delimiter;      //����������� �������� (���������)
   void AddRowToSection(AnsiString SectionName, AnsiString text, int Pos);
   //�������� �� �����, format: i-int c-char s-Ansi b-bool, ... ������ ������ �� ����������
   int LoadFromFile(AnsiString Filename, const char *format, ...);
   //[������] ... ��� ������ ������, ����� ��� � LoadFromFile. ���������� ���-�� ����� � ������
   int GetSection(const AnsiString SectionName, ...);
   //RegColumn - ������������� ������ �� ������� � ������. ColNum - ����� ������� ����� ����. ���������� ���-�� ����� � ������
   int RegColumn(int* &Field, int ColNum, const AnsiString SectionName = "");
   int RegColumn(char* &Field, int ColNum, const AnsiString SectionName = "");
   int RegColumn(AnsiString* &Field, int ColNum, const AnsiString SectionName = "");
   int RegColumn(bool* &Field, int ColNum, const AnsiString SectionName = "");
   void __fastcall Clear();
   __fastcall ~TableLoader();   
};
#endif
