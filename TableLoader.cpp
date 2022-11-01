// Copyright 2022 Larkin
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//     http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// See the License for the specific language governing permissions and
// limitations under the License.
//---------------------------------------------------------------------------
//#include <stdio.h> //для printf
//#include <stdarg.h>
//#include <Dialogs.hpp>
#include <Classes.hpp>
#pragma hdrstop
#include "TableLoader.h"
//-----------------------------------------------------------------------
__fastcall TableLoader::TableLoader()
{
   MemStr  = NULL;
   MemInt  = NULL;
   MemChar = NULL;
   MemBool = NULL;
   StrCount = 0; IntCount = 0; CharCount = 0; BoolCount = 0;
   FRowCount = 0;
   IgnoreFirstString = true;
   IgnoreDelimitersPack = true;
   FFormat = NULL;
   //Vars = NULL;
   Delimiter = '\t';
   FSections = NULL;
   FSectionCount = 0;
   SectionCapacity = 0;
   FColCount = 0;
}
//-----------------------------------------------------------------------
//[секция] ... это список ссылок, также как в LoadFromFile. Возвращает кол-во строк в секции
int TableLoader::GetSection(const AnsiString SectionName, ...)
{
   if (FSectionCount == 0)      return -1;
   int sSize = FRowCount, sPos = 0;
   if (SectionName != "" )
   {
      for (int i=0; i<FSectionCount; ++i)
         if (SectionName == *FSections[i].Name)
         {    
            sSize = FSections[i].Size;
            sPos = FSections[i].Pos;
            break;
         }
   }
   int **intArg;   char **charArg;  AnsiString **strArg;   bool **boolArg;
   int CurrI=0, CurrC=0, CurrA=0, CurrB=0;
   va_list ap;
   va_start(ap, SectionName);
   char t = FFormat[0];
   for (int i=0; t!='\0'; t = FFormat[++i])
   {
      switch (t)
      {
         case 'i':
            if ((intArg = va_arg(ap, int**)) != 0)
               *intArg = MemInt[CurrI++] + sPos;
         break;
         case 'c':
            if ((charArg = va_arg(ap, char**)) != 0)
               *charArg = MemChar[CurrC++] + sPos;
         break;
         case 's':
            if ((strArg = va_arg(ap, AnsiString**)) != 0)
               *strArg = MemStr[CurrA++] + sPos;
         break;
         case 'b':
            if ((boolArg = va_arg(ap, bool**)) != 0)
               *boolArg = MemBool[CurrB++] + sPos;
         break;
         //default:    va_arg(ap, char);
      }
      //(1)
   }
    //throw EDBEditError("fefe");
   va_end(ap);
   return sSize;
}
//-----------------------------------------------------------------------
int TableLoader::RegColumn(int* &Field, int ColNum, const AnsiString SectionName)
{
   --ColNum;
   if (ColNum < 0)      return -1;
   if (ColNum >= IntCount)      return -1;
   if (SectionName != "")
   {
      for (int i=0; i<FSectionCount; ++i)
         if (SectionName == *FSections[i].Name)
         {
            Field = MemInt[ColNum] + FSections[i].Pos;
            return FSections[i].Size;
         }
      return 0;
   }
   else
      Field = MemInt[ColNum];
   return FRowCount;
}
//-----------------------------------------------------------------------
int TableLoader::RegColumn(char* &Field, int ColNum, const AnsiString SectionName)
{
   --ColNum;
   if (ColNum < 0)      return -1;
   if (ColNum >= CharCount)      return -1;
   if (SectionName != "")
   {
      for (int i=0; i<FSectionCount; ++i)
         if (SectionName == *FSections[i].Name)
         {
            Field = MemChar[ColNum] + FSections[i].Pos;
            return FSections[i].Size;
         }
      return 0;
   }
   else
      Field = MemChar[ColNum];
   return FRowCount;
}
//-----------------------------------------------------------------------
int TableLoader::RegColumn(AnsiString* &Field, int ColNum, const AnsiString SectionName)
{
   --ColNum;
   if (ColNum < 0)      return -1;
   if (ColNum >= StrCount)      return -1;
   if (SectionName != "")
   {
      for (int i=0; i<FSectionCount; ++i)
         if (SectionName == *FSections[i].Name)
         {
            Field = MemStr[ColNum] + FSections[i].Pos;
            return FSections[i].Size;
         }
      return 0;
   }
   else
      Field = MemStr[ColNum];
   return FRowCount;
}
//-----------------------------------------------------------------------
int TableLoader::RegColumn(bool* &Field, int ColNum, const AnsiString SectionName)
{
   --ColNum;
   if (ColNum < 0)      return -1;
   if (ColNum >= BoolCount)      return -1;
   if (SectionName != "")
   {
      for (int i=0; i<FSectionCount; ++i)
         if (SectionName == *FSections[i].Name)
         {
            Field = MemBool[ColNum] + FSections[i].Pos;
            return FSections[i].Size;
         }
      return 0;
   }
   else
      Field = MemBool[ColNum];
   return FRowCount;
}
//-----------------------------------------------------------------------
//Загрузка из файла, format: i-int c-char s-Ansi b-bool, ... список ссылок на переменные
int TableLoader::LoadFromFile(AnsiString Filename, const char *format, ...)
{
   TStringList *file = new TStringList;
   try { file->LoadFromFile(Filename);     }
   catch (...)
   {
      delete file;
      throw EFOpenError("Cannot open "+Filename);
   }
   if (file->Count <= 1)
   {
      delete file;
      return 0;
   }
   if (FRowCount > 0)
   {//тут должно быть удаление
      //~TableLoader();
      Clear();
   }
   //Нужно пробежаться по файлу и удалить лишние строки
   if (IgnoreFirstString)
      file->Delete(0); //Первая лишняя
   FRowCount = file->Count;
   String str;
   for (int i=0; i<file->Count; i++)
   {
      str = file->Strings[i];
      if (str == "[end]")
      {
         FRowCount = i;
         break;
      }
      if ((!str.IsEmpty())&&(str[1] == '['))
         if (str.Pos(']') > 0)
         {
            SectionEnsureCapacity(FSectionCount+1);
            //AnsiString g = str.SubString(2, str.Pos(']')-2);
            FSections[FSectionCount].Pos = i;
            //strcpy(FSections[SectionCount].Name, g.c_str());
            FSections[FSectionCount].Name = new AnsiString(str.SubString(2, str.Pos(']')-2));
            FSectionCount++;
            str = "";    
         }
      if (str.IsEmpty())  //Пустую строку удалить, будто её нет
      {  //ShowMessage("Удаляем пустую строку №"+IntToStr(i));
         file->Delete(i);
         FRowCount--;
         i--;
         continue;  //Это если пустые строки в конце документа
      }
   }
   //Установить размер секций
   if (FSectionCount > 0)
   {
      for (int i=0; i<FSectionCount-1; ++i)
         FSections[i].Size = FSections[i+1].Pos - FSections[i].Pos;
      FSections[FSectionCount-1].Size = FRowCount - FSections[FSectionCount-1].Pos;
   }
   //for (int i=0; i<FRowCount; ++i)
   //   printf("%s\n",file->Strings[i]);
   //----vars-------------
   int maxints=0, maxchars=0, maxstrings=0, maxbools=0 ;
   //Разбор строки формата
   FFormat = strdup(format);
   for (unsigned int i=0; i<strlen(format); ++i)
      switch (format[i])
      {
         case 'i': maxints++; break;
         case 'c': maxchars++; break;
         case 's': maxstrings++; break;
         case 'b': maxbools++; break;
         default: FFormat[i] = '0';
      }
   FColCount += maxints; FColCount += maxchars; FColCount += maxstrings; FColCount += maxbools;
   //----------------------
   //Создание массивов по кооличеству строк в файле
   if (maxints > 0)
   {
      MemInt = new int*[maxints];
      for (int i=0; i<maxints; ++i)
         MemInt[i] = new int[FRowCount];
   }
   if (maxchars > 0)
   {
      MemChar = new char*[maxchars];
      for (int i=0; i<maxchars; ++i)
         MemChar[i] = new char[FRowCount];
   }
   if (maxstrings > 0)
   {
      MemStr = new AnsiString* [maxstrings];
      for (int i=0; i<maxstrings; ++i)
         MemStr[i] = new AnsiString[FRowCount];
   }
   if (maxbools > 0)
   {
      MemBool = new bool* [maxbools];
      for (int i=0; i<maxbools; ++i)
         MemBool[i] = new bool[FRowCount];
   }
   //-----------------------------------------------
   //Началось считывание файл и разбор по словам
   //char del='\t';    //Это разделитель ' '  '\t'
   int p;   //Индекс разделителя
   String word;   //Это отдельные слова
   int curr, currstr, currint, currchar, currbool;
   for (int i=0; i<FRowCount; ++i)
   {
      curr=0; currstr=0; currint=0; currchar=0; currbool=0;
      str = file->Strings[i];
      while (str.Length() != 0)  //Вот цикл отделяющий слова
      {
         if ( (IgnoreDelimitersPack)&&(str[1] == Delimiter) ) //Для отсеивания лишних разделителей
         {
            str.Delete(1,1);
            continue;
         }
         p = str.Pos(Delimiter);
         if (p == 0)
         {
            word = str;
            str = "";
         }
         else
         {
            word = str.SubString(1,p-1);
            str.Delete(1,p);
         }
         //Слово получено
         ///printf("%s ",word);
         try
         {
            switch (format[curr])
            {
               case 'i' :  MemInt [currint][i] = StrToInt(word);
                           /*printf("d=%d ",MemInt[currint][i]);*/
                           currint++;
                           break;
               case 'c' :  MemChar[currchar][i]= word.operator [](1);
                           /*printf("c=%c ", MemChar[currchar][i]);*/
                           currchar++;
                           break;
               case 's' :  MemStr [currstr][i] = word;
                           /*printf("s=%s ",MemStr[currstr][i]);*/
                           currstr++;
                           break;
               case 'b' :  MemBool[currbool][i]= (word.operator [](1)) == '0' ? false : true;
                           /*printf("b=%d ",MemBool[currbool][i]);*/
                           currbool++;
                           break;
               //default :
            }
         } catch (EConvertError&)
         {
            switch (format[curr])
            {
               case 'i' :  MemInt [currint][i] = 0; /*printf("d=%d ",MemInt[currint][i]);*/ currint++;  break;
               case 'c' :  MemChar[currchar][i]= '0'; /*printf("c=%c ", MemChar[currchar][i]);*/ currchar++; break;
               case 's' :  MemStr [currstr][i] = ""; /*printf("s=%s ",MemStr[currstr][i]);*/ currstr++; break;
               case 'b' :  MemBool[currbool][i]= false; /*printf("b=%d ",MemBool[currbool][i]);*/ currbool++; break;
               //default :
            }
         }
         curr++;
      }
   }
   delete file;
   /*
   for (int i=0;i<maxchars;i++)
    maschar[i][nCount]='\0';
   return nCount;
   }   */
   int **intArg;
   char **charArg;
   AnsiString **strArg;
   bool **boolArg;
   va_list ap;
   va_start(ap, format);
   char t = format[0];
   for (int i=0; t!='\0'; t = format[++i])
   {
      switch (t)
      {
         case 'i':
            if ((intArg = va_arg(ap, int**)) != 0)
               *intArg = MemInt[IntCount++];
         break;
         case 'c':
            if ((charArg = va_arg(ap, char**)) != 0)
               *charArg = MemChar[CharCount++];
         break;
         case 's':
            if ((strArg = va_arg(ap, AnsiString**)) != 0)
               *strArg = MemStr[StrCount++];
         break;
         case 'b':
            if ((boolArg = va_arg(ap, bool**)) != 0)
               *boolArg = MemBool[BoolCount++];
         break;
         //default:    va_arg(ap, char);
      }
      //(1)
   }
    //throw EDBEditError("fefe");
   va_end(ap);
   return FRowCount;       /////////*/
}
//-----------------------------------------------------------------------
void TableLoader::SectionEnsureCapacity(int count)
{
   if (count > SectionCapacity)
   {
      SectionCapacity = 4;
      while ( SectionCapacity < count )
         SectionCapacity *= 2;
      if (FSections)
         FSections = (Section*) realloc (FSections, SectionCapacity*sizeof(Section));
      else
         FSections = (Section*) malloc (SectionCapacity*sizeof(Section));
   }
}
//-----------------------------------------------------------------------
void __fastcall TableLoader::Clear()
{
   if (FFormat)
   {
      free (FFormat);
      FFormat = NULL;
   }
   if (FSections)
   {
      for (int i=0; i<FSectionCount; ++i)
         delete FSections[i].Name;
      free (FSections);
      FSections = NULL;
      SectionCapacity = 0;
      FSectionCount = 0;
   }
   if (IntCount > 0)
   {
      for (int i=0; i<IntCount; ++i)
         delete []MemInt[i];
      delete []MemInt;
      MemInt = NULL;
      IntCount = 0;
   }
   if (CharCount > 0)
   {
      for (int i=0; i<CharCount; ++i)
         delete []MemChar[i];
      delete []MemChar;
      MemChar = NULL;
      CharCount = 0;
   }
   if (BoolCount > 0)
   {
      for (int i=0; i<BoolCount; ++i)
         delete []MemBool[i];
      delete []MemBool;
      MemBool = NULL;
      BoolCount = 0;
   }
   if (StrCount)
   {
      for (int i=0; i<StrCount; ++i)
         delete []MemStr[i];
      delete []MemStr;
      MemStr = NULL;
      StrCount = 0;
   }
   FRowCount = 0;
   FColCount = 0;
}
//-----------------------------------------------------------------------
void TableLoader::AddRowToSection(AnsiString SectionName, AnsiString text, int Pos)
{
}
//------------------------------------------------------------------------
TableLoader::Section* TableLoader::FindSection(AnsiString SectionName)
{
   for (int i=0; i<FSectionCount; ++i)
      if (SectionName == *FSections[i].Name)
         return &FSections[i];
   return NULL;
}
//------------------------------------------------------------------------
__fastcall TableLoader::~TableLoader()
{
   Clear();
}
//-----------------------------------------------------------------------
#pragma package(smart_init)
