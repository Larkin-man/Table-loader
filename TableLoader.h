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
* TableLoader - Загрузка таблиц из текстовых файлов. Версия 1.1    *
\******************************************************************/
#ifndef TableLoaderH
#define TableLoaderH

class TableLoader
{
private:
   char *FFormat;
   //Mem обязательно [Count][FRowCount]
   String **MemStr;
   int **MemInt;
   char **MemChar;
   bool **MemBool;
   int StrCount, IntCount, CharCount, BoolCount;
   int FRowCount;
   int FColCount;

protected:    
   struct Section
   {
      String *Name;
      int Pos; //Позиция секции с 0
      int Size;//Кол-во строк
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
   Section* FindSection(String SectionName);
   bool IgnoreFirstString; //Игнорировать первую сроку в файле. defaul=true
   bool IgnoreDelimitersPack; //Игнорировать разделители, идущие подряд. defauly=true
   char Delimiter;      //Разделитель столбцов (табуляция)
   void AddRowToSection(String SectionName, String text, int Pos);
   //Загрузка из файла, format: i-int c-char s-Ansi b-bool, ... список ссылок на переменные
   int LoadFromFile(String Filename, const char *format, ...);
   //[секция] ... это список ссылок, также как в LoadFromFile. Возвращает кол-во строк в секции
   int GetSection(const String SectionName, ...);
   //RegColumn - устанавливает ссылку на столбец в секции. ColNum - Номер столбца соотв типа. Возвращает кол-во строк в секции
   int RegColumn(int* &Field, int ColNum, const String SectionName = "");
   int RegColumn(char* &Field, int ColNum, const String SectionName = "");
   int RegColumn(String* &Field, int ColNum, const String SectionName = "");
   int RegColumn(bool* &Field, int ColNum, const String SectionName = "");
   void __fastcall Clear();
   __fastcall ~TableLoader();   
};
#endif
