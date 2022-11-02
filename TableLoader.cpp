// Copyright 2022 Larkin
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//     http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// See the License for the specific language governing permissions and
// limitations under the License.
//--------------------------------------------------------------------
//#include <stdio.h> //для printf
//#include <stdarg.h>
//#include <Dialogs.hpp>
#include <Classes.hpp>
//#include <ustring.h>
//#include <UnicodeString>
#pragma hdrstop
#include "TableLoader.h"
//--------------------------------------------------------------------
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
//--------------------------------------------------------------------
//[секция] ... это список ссылок, также как в LoadFromFile. Возвращает кол-во строк в секции
int TableLoader::GetSection(const UnicodeString SectionName, ...)
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
   int **intArg;   lrchar **lrcharArg;  UnicodeString **strArg;   bool **boolArg;
   int CurrI=0, CurrC=0, CurrA=0, CurrB=0;
   va_list ap;
   va_start(ap, SectionName);
   lrchar t = FFormat[0];
   for (int i=0; t!='\0'; t = FFormat[++i])
   {
      switch (t)
      {
         case 'i':
            if ((intArg = va_arg(ap, int**)) != 0)
               *intArg = MemInt[CurrI++] + sPos;
         break;
         case 'c':
            if ((lrcharArg = va_arg(ap, lrchar**)) != 0)
               *lrcharArg = MemChar[CurrC++] + sPos;
         break;
         case 's':
            if ((strArg = va_arg(ap, UnicodeString**)) != 0)
               *strArg = MemStr[CurrA++] + sPos;
         break;
         case 'b':
            if ((boolArg = va_arg(ap, bool**)) != 0)
               *boolArg = MemBool[CurrB++] + sPos;
         break;
         //default:    va_arg(ap, lrchar);
      }
      //(1)
   }
    //throw EDBEditError("fefe");
   va_end(ap);
   return sSize;
}
//--------------------------------------------------------------------
int TableLoader::RegColumn(int* &Field, int ColNum, const UnicodeString SectionName)
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
//--------------------------------------------------------------------
int TableLoader::RegColumn(lrchar* &Field, int ColNum, const UnicodeString SectionName)
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
//--------------------------------------------------------------------
int TableLoader::RegColumn(UnicodeString* &Field, int ColNum, const UnicodeString SectionName)
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
//--------------------------------------------------------------------
int TableLoader::RegColumn(bool* &Field, int ColNum, const UnicodeString SectionName)
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
//--------------------------------------------------------------------
//Загрузка из файла, format: i-int c-lrchar s-Ansi b-bool, ... список ссылок на переменные
int TableLoader::Load(UnicodeString Filename, bool FileOrResource, const char *format, ...)
{
	TStringList *file = NULL;
	TResourceStream *ptRes = NULL;
	try {
	file = new TStringList;
	if (FileOrResource)
	{
		//try {
		file->LoadFromFile(Filename);
		/*	}catch (...)
		{  delete file;
			throw;   }*/
	} else //Resource
	{
		//try {
		ptRes = new TResourceStream(0,Filename, L"RT_RCDATA");
		file->LoadFromStream(ptRes);
		//TODO: Добавить кодирование
		/*} catch (...)
		{   delete file;
			throw; 	}*/
	}
	if (file->Count <= 1) //????
   {
		delete file;
      delete ptRes;
      return 0;
   }
	if (FRowCount > 0)
      Clear();
   //Нужно пробежаться по файлу и удалить лишние строки
   if (IgnoreFirstString)
      file->Delete(0); //Первая лишняя
   FRowCount = file->Count;
   String str;
   for (int i=0; i<file->Count; i++)
   {
      str = file->Strings[i];
		if (str.Pos("[end]") > 0)
      {
         FRowCount = i;
         break;
      }
      if ((!str.IsEmpty())&&(str[1] == '['))
         if (str.Pos(']') > 0)
         {
            SectionEnsureCapacity(FSectionCount+1);
            //UnicodeString g = str.SubString(2, str.Pos(']')-2);
            FSections[FSectionCount].Pos = i;
            //strcpy(FSections[SectionCount].Name, g.c_str());
            FSections[FSectionCount].Name = new UnicodeString(str.SubString(2, str.Pos(']')-2));
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
   int maxints=0, maxlrchars=0, maxstrings=0, maxbools=0 ;
   //Разбор строки формата
	FFormat = strdup(format);
   for (unsigned int i=0; i<strlen(format); ++i)
      switch (format[i])
		{
			case 'I':
			case 'i': maxints++; break;
			case 'C':
			case 'c': maxlrchars++; break;
			case 'S':
			case 's': maxstrings++; break;
			case 'B':
			case 'b': maxbools++; break;
         default: FFormat[i] = '0';
      }
   FColCount += maxints; FColCount += maxlrchars; FColCount += maxstrings; FColCount += maxbools;
   //----------------------
   //Создание массивов по кооличеству строк в файле
   if (maxints > 0)
   {
      MemInt = new int*[maxints];
      for (int i=0; i<maxints; ++i)
         MemInt[i] = new int[FRowCount];
   }
   if (maxlrchars > 0)
   {
      MemChar = new lrchar*[maxlrchars];
      for (int i=0; i<maxlrchars; ++i)
         MemChar[i] = new lrchar[FRowCount];
   }
   if (maxstrings > 0)
   {
      MemStr = new UnicodeString* [maxstrings];
      for (int i=0; i<maxstrings; ++i)
         MemStr[i] = new UnicodeString[FRowCount];
   }
   if (maxbools > 0)
   {
      MemBool = new bool* [maxbools];
      for (int i=0; i<maxbools; ++i)
         MemBool[i] = new bool[FRowCount];
   }
   //-----------------------------------------------
   //Началось считывание файл и разбор по словам
   //lrchar del='\t';    //Это разделитель ' '  '\t'
   int p;   //Индекс разделителя
   String word;   //Это отдельные слова
   int curr, currstr, currint, currlrchar, currbool;
   for (int i=0; i<FRowCount; ++i)
   {
      curr=0; currstr=0; currint=0; currlrchar=0; currbool=0;
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
				REPEAT:
            switch (format[curr])
				{
					case 'I': 	currint++;
									curr++;
									goto REPEAT;
					case 'C': 	currlrchar++;
									curr++;
									goto REPEAT;
					case 'S': 	currstr++;
									curr++;
									goto REPEAT;
					case 'B': 	currbool++;
									curr++;
									goto REPEAT;
					case 'i' :  MemInt [currint][i] =word.ToIntDef(0);
                           /*printf("d=%d ",MemInt[currint][i]);*/
									currint++;
                           break;
					case 'c' :  MemChar[currlrchar][i]= word.operator [](1);
                           /*printf("c=%c ", MemChar[currlrchar][i]);*/
                           currlrchar++;
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
               case 'c' :  MemChar[currlrchar][i]= '0'; /*printf("c=%c ", MemChar[currlrchar][i]);*/ currlrchar++; break;
               case 's' :  MemStr [currstr][i] = ""; /*printf("s=%s ",MemStr[currstr][i]);*/ currstr++; break;
               case 'b' :  MemBool[currbool][i]= false; /*printf("b=%d ",MemBool[currbool][i]);*/ currbool++; break;
               //default :
            }
         }
         curr++;
      }
   }

   /*
   for (int i=0;i<maxlrchars;i++)
	 maslrchar[i][nCount]='\0';
   return nCount;
   }   */
   int **intArg;
   lrchar **lrcharArg;
   UnicodeString **strArg;
   bool **boolArg;
   va_list ap;
   va_start(ap, format);
   lrchar t = format[0];
   for (int i=0; t!='\0'; t = format[++i])
   {
      switch (t)
		{
			case 'I':
         case 'i':
            if ((intArg = va_arg(ap, int**)) != 0)
					*intArg = MemInt[IntCount++];
			break;
			case 'C':
         case 'c':
            if ((lrcharArg = va_arg(ap, lrchar**)) != 0)
					*lrcharArg = MemChar[CharCount++];
			break;
			case 'S':
         case 's':
            if ((strArg = va_arg(ap, UnicodeString**)) != 0)
					*strArg = MemStr[StrCount++];
			break;
			case 'B':
         case 'b':
            if ((boolArg = va_arg(ap, bool**)) != 0)
					*boolArg = MemBool[BoolCount++];
			break;
         //default:    va_arg(ap, lrchar);
      }
		//(1)
   }
    //throw EDBEditError("fefe");
   va_end(ap);
		  /////////*/
	}
	__finally
	{
		delete file;
		delete ptRes;
	}
	return FRowCount;
}
//--------------------------------------------------------------------
void TableLoader::SectionEnsureCapacity(int count)
{
   if (count > SectionCapacity)
   {
      SectionCapacity = 4;
      while ( SectionCapacity < count )
         SectionCapacity *= 2;
      if (FSections)
			FSections = (TLSection*) realloc (FSections, SectionCapacity*sizeof(TLSection));
      else
         FSections = (TLSection*) malloc (SectionCapacity*sizeof(TLSection));
   }
}
//--------------------------------------------------------------------
void __fastcall TableLoader::Clear()
{  /*
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
	FColCount = 0;   */
}
//--------------------------------------------------------------------
void TableLoader::AddRowToSection(UnicodeString SectionName, UnicodeString text, int Pos)
{
}
//--------------------------------------------------------------------
TLSection* TableLoader::FindSection(UnicodeString SectionName)
{
   for (int i=0; i<FSectionCount; ++i)
      if (SectionName == *FSections[i].Name)
         return &FSections[i];
   return NULL;
}
//--------------------------------------------------------------------
void TableLoader::GetCount(int &IntCount, int &CharCount, int &BoolCount, int &StrCount)
{
	StrCount = StrCount;
	IntCount = IntCount;
	CharCount = CharCount;
	BoolCount = BoolCount;
}
//--------------------------------------------------------------------
__fastcall TableLoader::~TableLoader()
{
   //Clear();
}
//-----------------------------------------------------------------------
#pragma package(smart_init)
