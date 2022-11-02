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
* TableLoader - �������� ������ �� ��������� ������. ������ 1.5    *
* Unicode, LoadFromResource                                        *
\******************************************************************/
#ifndef TableLoaderH
#define TableLoaderH

typedef char lrchar;

class TableLoader
{
private:
   char *FFormat;
	//Mem ����������� [Count][FRowCount]
   UnicodeString **MemStr;
   int **MemInt;
	lrchar **MemChar;
   bool **MemBool;
	int StrCount, IntCount, CharCount, BoolCount;
   int FRowCount;
	int FColCount;
	void AddRowToSection(UnicodeString SectionName, UnicodeString text, int Pos);

protected:    
	struct Section
	{
		UnicodeString *Name;
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
	Section* FindSection(UnicodeString SectionName);
	bool IgnoreFirstString; //������������ ������ ����� � �����. defaul=true
	bool IgnoreDelimitersPack; //������������ �����������, ������ ������. defauly=true
	lrchar Delimiter;      //����������� �������� (���������)
	//�������� �� �����, format: i-int c-lrchar s-Unicode b-bool, ... ������ ������ �� ����������
	int Load(UnicodeString Filename, bool FileOrResource, const char *format, ...);
	//GetSection: ... ��� ������ ������, ����� ��� � LoadFromFile. ���������� ���-�� ����� � ������
	int GetSection(const UnicodeString SectionName, ...);
	//RegColumn - ������������� ������ �� ������� � ������. ColNum - ����� ������� ����� ����. ���������� ���-�� ����� � ������
	int RegColumn(int* &Field, int ColNum, const UnicodeString SectionName = "");
	int RegColumn(lrchar* &Field, int ColNum, const UnicodeString SectionName = "");
	int RegColumn(UnicodeString* &Field, int ColNum, const UnicodeString SectionName = "");
	int RegColumn(bool* &Field, int ColNum, const UnicodeString SectionName = "");
	void GetCount(int &IntCount, int &CharCount, int &BoolCount, int &StrCount);	void __fastcall Clear();
	__fastcall ~TableLoader();
};
#endif
