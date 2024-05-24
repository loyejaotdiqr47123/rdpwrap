/*
Copyright 2014 Stas'M Corp.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include <algorithm>
#include "stdafx.h"
#include <Windows.h>
#include <stdlib.h>
#include "IniFile.h"
#include <vector>
#include <string>

INI_FILE::INI_FILE(wchar_t *FilePath)
{
	DWORD Status = 0;
	DWORD NumberOfBytesRead = 0;

	HANDLE hFile = CreateFile(FilePath, GENERIC_READ, FILE_SHARE_WRITE|FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return;
	}

	FileSize = GetFileSize(hFile, NULL);
	if (FileSize == INVALID_FILE_SIZE)
	{
		return;
	}

	FileRaw = new char[FileSize];
	Status = ReadFile(hFile, FileRaw, FileSize, &NumberOfBytesRead, NULL);
	if (!Status)
	{
		return;
	}

	CreateStringsMap();
	Parse();
}


INI_FILE::~INI_FILE()
{
	for (DWORD i = 0; i < IniData.SectionCount; i++)
	{
		delete[] IniData.Section[i].Variables;
	}
	delete[] IniData.Section;
	delete[] FileStringsMap;
	delete FileRaw;
}

/*
bool INI_FILE::CreateStringsMap()
{
	DWORD StringsCount = 1;

	for (DWORD i = 0; i < FileSize; i++)
	{
		if (FileRaw[i] == '\r' && FileRaw[i + 1] == '\n') StringsCount++;
	}

	FileStringsCount = StringsCount;

	FileStringsMap = new DWORD[StringsCount];
	FileStringsMap[0] = 0;

	StringsCount = 1;

	for (DWORD i = 0; i < FileSize; i++)
	{
		if (FileRaw[i] == '\r' && FileRaw[i + 1] == '\n')
		{
			FileStringsMap[StringsCount] = i + 2;
			StringsCount++;
		}
	}

	return true;
}
*/
bool INI_FILE::CreateStringsMap()
{
    DWORD StringsCount = 0;
    DWORD currentPosition = 0;

    for (DWORD i = 0; i < FileSize; ++i)
    {
        if (i < FileSize - 1 && FileRaw[i] == '\r' && FileRaw[i + 1] == '\n')
        {
            ++StringsCount;
            currentPosition = i + 2;
        }
    }

    if (currentPosition < FileSize)
    {
        ++StringsCount;
    }

    FileStringsCount = StringsCount;
    FileStringsMap = new DWORD[FileStringsCount + 1];
    FileStringsMap[0] = 0;

    currentPosition = 0;
    DWORD mapIndex = 1;
    for (DWORD i = 0; i < FileSize; ++i)
    {
        if (i < FileSize - 1 && FileRaw[i] == '\r' && FileRaw[i + 1] == '\n')
        {
            FileStringsMap[mapIndex] = currentPosition;
            ++mapIndex;
            currentPosition = i + 2;
        }
    }

    if (currentPosition < FileSize)
    {
        FileStringsMap[mapIndex] = currentPosition;
    }

    FileStringsMap[FileStringsCount] = FileSize;

    return true;
}
int INI_FILE::StrTrim(char* Str)
{
	size_t i = 0, j;
	while ((Str[i] == ' ') || (Str[i] == '\t'))
	{
		i++;
	}
	if (i>0)
	{
		for (j = 0; j < strlen(Str); j++)
		{
			Str[j] = Str[j + i];
		}
		Str[j] = '\0';
	}

	i = strlen(Str) - 1;
	while ((Str[i] == ' ') || (Str[i] == '\t'))
	{
		i--;
	}
	if (i < (strlen(Str) - 1))
	{
		Str[i + 1] = '\0';
	}
	return 0;
}

DWORD INI_FILE::GetFileStringFromNum(DWORD StringNumber, char *RetString, DWORD Size)
{
	DWORD CurrentStringNum = 0;
	DWORD EndStringPos = 0;
	DWORD StringSize = 0;

	if (StringNumber > FileStringsCount) return 0;

	for (DWORD i = FileStringsMap[StringNumber]; i < FileSize; i++)
	{
		if (i == (FileSize - 1))
		{
			EndStringPos = FileSize;
			break;
		}
		if (FileRaw[i] == '\r' && FileRaw[i + 1] == '\n')
		{
			EndStringPos = i;
			break;
		}
	}

	StringSize = EndStringPos - FileStringsMap[StringNumber];

	if (Size < StringSize) return 0;

	memset(RetString, 0x00, Size);
	memcpy(RetString, &(FileRaw[FileStringsMap[StringNumber]]), StringSize);
	return StringSize;
}

/*
bool INI_FILE::IsVariable(char *Str, DWORD StrSize)
{
	bool Quotes = false;

	for (DWORD i = 0; i < StrSize; i++)
	{
		if (Str[i] == '"' || Str[i] == '\'') Quotes = !Quotes;
		if (Str[i] == '=' && !Quotes) return true;
	}
	return false;
}
*/
/*
bool INI_FILE::IsVariable(char *Str, DWORD StrSize) {
    if (Str == nullptr || StrSize == 0) return false;

    char *equalsPos = std::find(Str, Str + StrSize, '=');
    if (equalsPos == Str + StrSize) return false;

    bool inQuotes = false;
    for (char *quotePos = Str; quotePos < equalsPos; ++quotePos) {
        if (*quotePos == '"
*/
bool INI_FILE::IsVariable(char *Str, DWORD StrSize)
{
    bool inQuotes = false;
    for (char c; StrSize--; ) {
        c = *Str++;
        if (c == '"' || c == '\'') inQuotes = !inQuotes;
        else if (c == '=' && !inQuotes) return true;
        else if (c == '\0') break;
    }
    return false;
}
/*
bool INI_FILE::FillVariable(INI_SECTION_VARIABLE *Variable, char *Str, DWORD StrSize)
{
	bool Quotes = false;

	for (DWORD i = 0; i < StrSize; i++)
	{
		if (Str[i] == '"' || Str[i] == '\'') Quotes = !Quotes;
		if (Str[i] == '=' && !Quotes)
		{
			memset(Variable->VariableName, 0, MAX_STRING_LEN);
			memset(Variable->VariableValue, 0, MAX_STRING_LEN);
			memcpy(Variable->VariableName, Str, i);
			memcpy(Variable->VariableValue, &(Str[i + 1]), StrSize - i - 1);
			StrTrim(Variable->VariableName);
			StrTrim(Variable->VariableValue);
			break;
		}
	}
	return true;
}
*/
bool INI_FILE::FillVariable(INI_SECTION_VARIABLE *Variable, char *Str, DWORD StrSize)
{
    char *pEqual = Str;
    bool inQuotes = false;

    while (*pEqual && pEqual - Str < StrSize) {
        if (*pEqual == '"' || *pEqual == '\'') inQuotes = !inQuotes;
        if (*pEqual == '=' && !inQuotes) break;
        pEqual++;
    }

    if (*pEqual != '=') return false; // no '=' found

    size_t nameLen = pEqual - Str;
    size_t valueLen = StrSize - (pEqual - Str) - 1;

    memset(Variable->VariableName, 0, MAX_STRING_LEN);
    memset(Variable->VariableValue, 0, MAX_STRING_LEN);

    strncpy(Variable->VariableName, Str, nameLen);
    strncpy(Variable->VariableValue, pEqual + 1, valueLen);

    StrTrim(Variable->VariableName);
    StrTrim(Variable->VariableValue);

    return true;
}
bool INI_FILE::Parse()
{
	DWORD CurrentStringNum = 0;
	char CurrentString[512];
	DWORD CurrentStringSize = 0;

	DWORD SectionsCount = 0;
	DWORD VariablesCount = 0;

	DWORD CurrentSectionNum = -1;
	DWORD CurrentVariableNum = -1;

	// Calculate sections count
	for (DWORD CurrentStringNum = 0; CurrentStringNum < FileStringsCount; CurrentStringNum++)
	{
		CurrentStringSize = GetFileStringFromNum(CurrentStringNum, CurrentString, 512);

		if (CurrentString[0] == ';') continue; // It's a comment

		if (CurrentString[0] == '[' && CurrentString[CurrentStringSize - 1] == ']')	// It's section declaration
		{
			SectionsCount++;
			continue;
		}
	}

	DWORD *SectionVariableCount = new DWORD[SectionsCount];
	memset(SectionVariableCount, 0x00, sizeof(DWORD)*SectionsCount);

	for (DWORD CurrentStringNum = 0; CurrentStringNum < FileStringsCount; CurrentStringNum++)
	{
		CurrentStringSize = GetFileStringFromNum(CurrentStringNum, CurrentString, 512);

		if (CurrentString[0] == ';') continue; // It's a comment


		if (CurrentString[0] == '[' && CurrentString[CurrentStringSize - 1] == ']')	// It's section declaration
		{
			CurrentSectionNum++;
			continue;
		}
		if (IsVariable(CurrentString, CurrentStringSize))
		{
			VariablesCount++;
			SectionVariableCount[CurrentSectionNum]++;
			continue;
		}
	}

	IniData.SectionCount = SectionsCount;
	IniData.Section = new INI_SECTION[SectionsCount];
	memset(IniData.Section, 0x00, sizeof(PINI_SECTION)*SectionsCount);

	for (DWORD i = 0; i < SectionsCount; i++)
	{
		IniData.Section[i].VariablesCount = SectionVariableCount[i];
		IniData.Section[i].Variables = new INI_SECTION_VARIABLE[SectionVariableCount[i]];
		memset(IniData.Section[i].Variables, 0x00, sizeof(INI_SECTION_VARIABLE)*SectionVariableCount[i]);
	}

	delete[] SectionVariableCount;

	CurrentSectionNum = -1;
	CurrentVariableNum = -1;

	for (DWORD CurrentStringNum = 0; CurrentStringNum < FileStringsCount; CurrentStringNum++)
	{
		CurrentStringSize = GetFileStringFromNum(CurrentStringNum, CurrentString, 512);

		if (CurrentString[0] == ';') // It's a comment
		{
			continue;
		}

		if (CurrentString[0] == '[' && CurrentString[CurrentStringSize - 1] == ']')
		{
			CurrentSectionNum++;
			CurrentVariableNum = 0;
			memset(IniData.Section[CurrentSectionNum].SectionName, 0, MAX_STRING_LEN);
			memcpy(IniData.Section[CurrentSectionNum].SectionName, &(CurrentString[1]), (CurrentStringSize - 2));
			continue;
		}

		if (IsVariable(CurrentString, CurrentStringSize))
		{
			FillVariable(&(IniData.Section[CurrentSectionNum].Variables[CurrentVariableNum]), CurrentString, CurrentStringSize);
			CurrentVariableNum++;
			continue;
		}
	}

	return true;
}

/*
bool INI_FILE::Parse() {
    std::vector<INI_SECTION> sections;
    int currentSectionNum = -1;

    for (DWORD currentStringNum = 0; currentStringNum < FileStringsCount; ++currentStringNum) {
        std::string currentString;
        DWORD currentStringSize = GetFileStringFromNum(currentStringNum, nullptr, 0);
        if (currentStringSize == 0) {
            continue; // Empty string or failed to get the size
        }

        currentString.resize(currentStringSize);
        if (!GetFileStringFromNum(currentStringNum, &currentString[0], currentStringSize + 1)) {
            continue; // Failed to get the string
        }

        if (currentString[0] == ';') {
            continue; // It's a comment
        }

        if (currentString[0] == '[' && currentString[currentString.length() - 1] == ']') {
            // It's a section declaration
            ++currentSectionNum;
            sections.emplace_back();
            sections[currentSectionNum].SectionName = currentString.substr(1, currentString.length() - 2);
            sections[currentSectionNum].VariablesCount = 0;
            continue;
        }

        if (IsVariable(currentString.c_str(), currentString.length())) {
            // It's a variable
            INI_SECTION_VARIABLE variable;
            if (FillVariable(&variable, currentString.c_str(), currentString.length())) {
                sections[currentSectionNum].Variables.push_back(variable);
                sections[currentSectionNum].VariablesCount++;
            }
        }
    }

    IniData.SectionCount = sections.size();
    IniData.Section = sections.data(); // Assuming IniData.Section is of type INI_SECTION*.

    return true;
}
*/
/*
bool INI_FILE::Parse() {
    std::vector<INI_SECTION> sections;
    DWORD currentSectionNum = -1;
    DWORD currentVariableNum = -1;

    for (DWORD currentStringNum = 0; currentStringNum < FileStringsCount; currentStringNum++) {
        char currentString[512];
        DWORD currentStringSize = GetFileStringFromNum(currentStringNum, currentString, 512);

        if (currentString[0] == ';') continue; // It's a comment

        if (currentString[0] == '[' && currentString[currentStringSize - 1] == ']') {
            // It's a section declaration
            currentSectionNum++;
            sections.emplace_back();
            sections[currentSectionNum].SectionName = std::string(&(currentString[1]), currentStringSize - 2);
            sections[currentSectionNum].VariablesCount = 0;
            currentVariableNum = 0;
            continue;
        }

        if (IsVariable(currentString, currentStringSize)) {
            // It's a variable
            sections[currentSectionNum].VariablesCount++;
            sections[currentSectionNum].Variables.emplace_back();
            FillVariable(&(sections[currentSectionNum].Variables[currentVariableNum]), currentString, currentStringSize);
            currentVariableNum++;
            continue;
        }
    }

    IniData.SectionCount = sections.size();
    IniData.Section = sections.data();

    return true;
}
*/
/*
bool INI_FILE::Parse() {
    DWORD CurrentStringNum = 0;
    char* CurrentString = nullptr;
    DWORD CurrentStringSize = 0;

    DWORD SectionsCount = 0;
    DWORD* SectionVariableCount = nullptr;

    DWORD CurrentSectionNum = 0;
    DWORD CurrentVariableNum = 0;

    for (CurrentStringNum = 0; CurrentStringNum < FileStringsCount; ++CurrentStringNum) {
        CurrentStringSize = GetFileStringFromNum(CurrentStringNum, nullptr, 0);
        CurrentString = new char[CurrentStringSize + 1];
        GetFileStringFromNum(CurrentStringNum, CurrentString, CurrentStringSize + 1);

        if (CurrentString[0] == ';') {
            delete[] CurrentString;
            continue;
        }

        if (CurrentString[0] == '[' && CurrentString[CurrentStringSize - 1] == ']') {
            ++SectionsCount;
        } else if (IsVariable(CurrentString, CurrentStringSize)) {
            if (SectionsCount > 0) {
                if (SectionVariableCount == nullptr) {
                    SectionVariableCount = new DWORD[SectionsCount];
                    memset(SectionVariableCount, 0, sizeof(DWORD) * SectionsCount);
                }
                ++SectionVariableCount[CurrentSectionNum];
            }
        }

        delete[] CurrentString;
    }

    IniData.SectionCount = SectionsCount;
    IniData.Section = new INI_SECTION[SectionsCount];
    memset(IniData.Section, 0, sizeof(INI_SECTION) * SectionsCount);

    for (CurrentStringNum = 0, CurrentSectionNum = 0, CurrentVariableNum = 0; 
         CurrentStringNum < FileStringsCount; 
         ++CurrentStringNum) {
        CurrentStringSize = GetFileStringFromNum(CurrentStringNum, nullptr, 0);
        CurrentString = new char[CurrentStringSize + 1];
        GetFileStringFromNum(CurrentStringNum, CurrentString, CurrentStringSize + 1);

        if (CurrentString[0] == ';') {
            delete[] CurrentString;
            continue;
        }

        if (CurrentString[0] == '[' && CurrentString[CurrentStringSize - 1] == ']') {
            memcpy(IniData.Section[CurrentSectionNum].SectionName, &CurrentString[1], CurrentStringSize - 2);
            IniData.Section[CurrentSectionNum].SectionName[CurrentStringSize - 2] = '\0';
            IniData.Section[CurrentSectionNum].VariablesCount = SectionVariableCount[CurrentSectionNum];
            IniData.Section[CurrentSectionNum].Variables = new INI_SECTION_VARIABLE[SectionVariableCount[CurrentSectionNum]];
            memset(IniData.Section[CurrentSectionNum].Variables, 0, sizeof(INI_SECTION_VARIABLE) * SectionVariableCount[CurrentSectionNum]);
            CurrentVariableNum = 0;
            ++CurrentSectionNum;
        } else if (IsVariable(CurrentString, CurrentStringSize)) {
            FillVariable(&(IniData.Section[CurrentSectionNum - 1].Variables[CurrentVariableNum]), CurrentString, CurrentStringSize);
            ++CurrentVariableNum;
        }

        delete[] CurrentString;
    }

    delete[] SectionVariableCount;

    return true;
}
*/

/*
bool INI_FILE::Parse()
{
	DWORD CurrentStringNum = 0;
	char CurrentString[512];
	DWORD CurrentStringSize = 0;

	DWORD SectionsCount = 0;
	DWORD VariablesCount = 0;

	DWORD CurrentSectionNum = -1;
	DWORD CurrentVariableNum = -1;

	// Calculate sections count
	for (DWORD CurrentStringNum = 0; CurrentStringNum < FileStringsCount; CurrentStringNum++)
	{
		CurrentStringSize = GetFileStringFromNum(CurrentStringNum, CurrentString, 512);

		if (CurrentString[0] == ';') continue; // It's a comment

		if (CurrentString[0] == '[' && CurrentString[CurrentStringSize - 1] == ']')	// It's section declaration
		{
			SectionsCount++;
			continue;
		}
	}

	DWORD *SectionVariableCount = new DWORD[SectionsCount];
	memset(SectionVariableCount, 0x00, sizeof(DWORD)*SectionsCount);

	for (DWORD CurrentStringNum = 0; CurrentStringNum < FileStringsCount; CurrentStringNum++)
	{
		CurrentStringSize = GetFileStringFromNum(CurrentStringNum, CurrentString, 512);

		if (CurrentString[0] == ';') continue; // It's a comment


		if (CurrentString[0] == '[' && CurrentString[CurrentStringSize - 1] == ']')	// It's section declaration
		{
			CurrentSectionNum++;
			continue;
		}
		if (IsVariable(CurrentString, CurrentStringSize))
		{
			VariablesCount++;
			SectionVariableCount[CurrentSectionNum]++;
			continue;
		}
	}

	IniData.SectionCount = SectionsCount;
	IniData.Section = new INI_SECTION[SectionsCount];
	memset(IniData.Section, 0x00, sizeof(PINI_SECTION)*SectionsCount);

	for (DWORD i = 0; i < SectionsCount; i++)
	{
		IniData.Section[i].VariablesCount = SectionVariableCount[i];
		IniData.Section[i].Variables = new INI_SECTION_VARIABLE[SectionVariableCount[i]];
		memset(IniData.Section[i].Variables, 0x00, sizeof(INI_SECTION_VARIABLE)*SectionVariableCount[i]);
	}

	delete[] SectionVariableCount;

	CurrentSectionNum = -1;
	CurrentVariableNum = -1;

	for (DWORD CurrentStringNum = 0; CurrentStringNum < FileStringsCount; CurrentStringNum++)
	{
		CurrentStringSize = GetFileStringFromNum(CurrentStringNum, CurrentString, 512);

		if (CurrentString[0] == ';') // It's a comment
		{
			continue;
		}

		if (CurrentString[0] == '[' && CurrentString[CurrentStringSize - 1] == ']')
		{
			CurrentSectionNum++;
			CurrentVariableNum = 0;
			memset(IniData.Section[CurrentSectionNum].SectionName, 0, MAX_STRING_LEN);
			memcpy(IniData.Section[CurrentSectionNum].SectionName, &(CurrentString[1]), (CurrentStringSize - 2));
			continue;
		}

		if (IsVariable(CurrentString, CurrentStringSize))
		{
			FillVariable(&(IniData.Section[CurrentSectionNum].Variables[CurrentVariableNum]), CurrentString, CurrentStringSize);
			CurrentVariableNum++;
			continue;
		}
	}

	return true;
}

*/
PINI_SECTION INI_FILE::GetSection(char *SectionName)
{
	for (DWORD i = 0; i < IniData.SectionCount; i++)
	{
		if (
			(strlen(IniData.Section[i].SectionName) == strlen(SectionName)) &&
			(memcmp(IniData.Section[i].SectionName, SectionName, strlen(SectionName)) == 0)
		)
		{
			return &IniData.Section[i];
		}
	}
	return NULL;
}

bool INI_FILE::SectionExists(char *SectionName)
{
	if (GetSection(SectionName) == NULL)	return false;
	return true;
}

bool INI_FILE::VariableExists(char *SectionName, char *VariableName)
{
	INI_SECTION_VARIABLE Variable = { 0 };
	return GetVariableInSectionPrivate(SectionName, VariableName, &Variable);
}

bool INI_FILE::GetVariableInSectionPrivate(char *SectionName, char *VariableName, INI_SECTION_VARIABLE *RetVariable)
{
	INI_SECTION *Section = NULL;
	INI_SECTION_VARIABLE *Variable = NULL;

	// Find section
	Section = GetSection(SectionName);
	if (Section == NULL)
	{
		SetLastError(318); // This region is not found
		return false;
	}

	// Find variable
	for (DWORD i = 0; i < Section->VariablesCount; i++)
	{
		if (
			(strlen(Section->Variables[i].VariableName) == strlen(VariableName)) &&
			(memcmp(Section->Variables[i].VariableName, VariableName, strlen(VariableName)) == 0)
		)
		{
			Variable = &(Section->Variables[i]);
			break;
		}
	}
	if (Variable == NULL)
	{
		SetLastError(1898); // Member of the group is not found
		return false;
	}

	memset(RetVariable, 0x00, sizeof(*RetVariable));
	memcpy(RetVariable, Variable, sizeof(*Variable));

	return true;
}

bool INI_FILE::GetVariableInSection(char *SectionName, char *VariableName, INI_VAR_STRING *RetVariable)
{
	bool Status = false;
	INI_SECTION_VARIABLE Variable = {};

	Status = GetVariableInSectionPrivate(SectionName, VariableName, &Variable);
	if (!Status)	return Status;

	memset(RetVariable, 0x00, sizeof(*RetVariable));
	memcpy(RetVariable->Name, Variable.VariableName, strlen(Variable.VariableName));
	memcpy(RetVariable->Value, Variable.VariableValue, strlen(Variable.VariableValue));

	return true;
}

bool INI_FILE::GetVariableInSection(char *SectionName, char *VariableName, INI_VAR_DWORD *RetVariable)
{
	bool Status = false;
	INI_SECTION_VARIABLE Variable = {};

	Status = GetVariableInSectionPrivate(SectionName, VariableName, &Variable);
	if (!Status)	return Status;

	memset(RetVariable, 0x00, sizeof(*RetVariable));
	memcpy(RetVariable->Name, Variable.VariableName, strlen(Variable.VariableName));

#ifndef _WIN64
	RetVariable->ValueDec = strtol(Variable.VariableValue, NULL, 10);
	RetVariable->ValueHex = strtol(Variable.VariableValue, NULL, 16);
#else
	RetVariable->ValueDec = _strtoi64(Variable.VariableValue, NULL, 10);
	RetVariable->ValueHex = _strtoi64(Variable.VariableValue, NULL, 16);
#endif
	return true;
}

bool INI_FILE::GetVariableInSection(char *SectionName, char *VariableName, INI_VAR_BYTEARRAY *RetVariable)
{
	bool Status = false;
	INI_SECTION_VARIABLE Variable = {};

	Status = GetVariableInSectionPrivate(SectionName, VariableName, &Variable);
	if (!Status)	return Status;

	DWORD ValueLen = strlen(Variable.VariableValue);
	if ((ValueLen % 2) != 0) return false;

	// for security reasons not more than 16 bytes
	if (ValueLen > 32) ValueLen = 32;  // 32 hex digits

	memset(RetVariable, 0x00, sizeof(*RetVariable));
	memcpy(RetVariable->Name, Variable.VariableName, strlen(Variable.VariableName));

	for (DWORD i = 0; i <= ValueLen; i++)
	{
		if ((i % 2) != 0) continue;

		switch (Variable.VariableValue[i])
		{
		case '0': break;
		case '1': RetVariable->Value[(i / 2)] += (1 << 4); break;
		case '2': RetVariable->Value[(i / 2)] += (2 << 4); break;
		case '3': RetVariable->Value[(i / 2)] += (3 << 4); break;
		case '4': RetVariable->Value[(i / 2)] += (4 << 4); break;
		case '5': RetVariable->Value[(i / 2)] += (5 << 4); break;
		case '6': RetVariable->Value[(i / 2)] += (6 << 4); break;
		case '7': RetVariable->Value[(i / 2)] += (7 << 4); break;
		case '8': RetVariable->Value[(i / 2)] += (8 << 4); break;
		case '9': RetVariable->Value[(i / 2)] += (9 << 4); break;
		case 'A': RetVariable->Value[(i / 2)] += (10 << 4); break;
		case 'B': RetVariable->Value[(i / 2)] += (11 << 4); break;
		case 'C': RetVariable->Value[(i / 2)] += (12 << 4); break;
		case 'D': RetVariable->Value[(i / 2)] += (13 << 4); break;
		case 'E': RetVariable->Value[(i / 2)] += (14 << 4); break;
		case 'F': RetVariable->Value[(i / 2)] += (15 << 4); break;
		}

		switch (Variable.VariableValue[i + 1])
		{
		case '0': break;
		case '1': RetVariable->Value[(i / 2)] += 1; break;
		case '2': RetVariable->Value[(i / 2)] += 2; break;
		case '3': RetVariable->Value[(i / 2)] += 3; break;
		case '4': RetVariable->Value[(i / 2)] += 4; break;
		case '5': RetVariable->Value[(i / 2)] += 5; break;
		case '6': RetVariable->Value[(i / 2)] += 6; break;
		case '7': RetVariable->Value[(i / 2)] += 7; break;
		case '8': RetVariable->Value[(i / 2)] += 8; break;
		case '9': RetVariable->Value[(i / 2)] += 9; break;
		case 'A': RetVariable->Value[(i / 2)] += 10; break;
		case 'B': RetVariable->Value[(i / 2)] += 11; break;
		case 'C': RetVariable->Value[(i / 2)] += 12; break;
		case 'D': RetVariable->Value[(i / 2)] += 13; break;
		case 'E': RetVariable->Value[(i / 2)] += 14; break;
		case 'F': RetVariable->Value[(i / 2)] += 15; break;
		}
	}
	RetVariable->ArraySize = ValueLen / 2;
	return true;
}

bool INI_FILE::GetVariableInSection(char *SectionName, char *VariableName, bool *RetVariable)
{
	bool Status = false;
	INI_SECTION_VARIABLE Variable = {};

	Status = GetVariableInSectionPrivate(SectionName, VariableName, &Variable);
	if (!Status)	return Status;

	*RetVariable = (bool)strtol(Variable.VariableValue, NULL, 10);
	return true;
}

bool INI_FILE::GetSectionVariablesList(char *SectionName, INI_SECTION_VARLIST *VariablesList)
{
	INI_SECTION *Section = NULL;

	Section = GetSection(SectionName);
	if (Section == NULL)
	{
		SetLastError(318); // This region is not found
		return false;
	}

	VariablesList->EntriesCount = Section->VariablesCount;

	VariablesList->NamesEntries = new INI_SECTION_VARLIST_ENTRY[VariablesList->EntriesCount];
	memset(VariablesList->NamesEntries, 0x00, sizeof(INI_SECTION_VARLIST_ENTRY)*VariablesList->EntriesCount);

	VariablesList->ValuesEntries = new INI_SECTION_VARLIST_ENTRY[VariablesList->EntriesCount];
	memset(VariablesList->ValuesEntries, 0x00, sizeof(INI_SECTION_VARLIST_ENTRY)*VariablesList->EntriesCount);

	for (DWORD i = 0; i < Section->VariablesCount; i++)
	{
		memcpy(VariablesList->NamesEntries[i].String, Section->Variables[i].VariableName,
			strlen(Section->Variables[i].VariableName));

		memcpy(VariablesList->ValuesEntries[i].String, Section->Variables[i].VariableValue,
			strlen(Section->Variables[i].VariableValue));
	}

	return true;
}


// ---------------------------- WCHAR_T BLOCK ----------------------------------------------

bool INI_FILE::SectionExists(wchar_t *SectionName)
{
	char cSectionName[MAX_STRING_LEN] = { 0x00 };

	wcstombs(cSectionName, SectionName, MAX_STRING_LEN);

	return GetSection(cSectionName);
}

bool INI_FILE::VariableExists(wchar_t *SectionName, wchar_t *VariableName)
{
	INI_SECTION_VARIABLE Variable = { 0 };

	char cSectionName[MAX_STRING_LEN] = { 0x00 };
	char cVariableName[MAX_STRING_LEN] = { 0x00 };

	wcstombs(cSectionName, SectionName, MAX_STRING_LEN);
	wcstombs(cVariableName, VariableName, MAX_STRING_LEN);

	return GetVariableInSectionPrivate(cSectionName, cVariableName, &Variable);
}

bool INI_FILE::GetVariableInSection(wchar_t *SectionName, wchar_t *VariableName, INI_VAR_STRING *RetVariable)
{
	char cSectionName[MAX_STRING_LEN] = { 0x00 };
	char cVariableName[MAX_STRING_LEN] = { 0x00 };

	wcstombs(cSectionName, SectionName, MAX_STRING_LEN);
	wcstombs(cVariableName, VariableName, MAX_STRING_LEN);

	return GetVariableInSection(cSectionName, cVariableName, RetVariable);
}

bool INI_FILE::GetVariableInSection(wchar_t *SectionName, wchar_t *VariableName, INI_VAR_DWORD *RetVariable)
{
	char cSectionName[MAX_STRING_LEN] = { 0x00 };
	char cVariableName[MAX_STRING_LEN] = { 0x00 };

	wcstombs(cSectionName, SectionName, MAX_STRING_LEN);
	wcstombs(cVariableName, VariableName, MAX_STRING_LEN);

	return GetVariableInSection(cSectionName, cVariableName, RetVariable);
}

bool INI_FILE::GetVariableInSection(wchar_t *SectionName, wchar_t *VariableName, INI_VAR_BYTEARRAY *RetVariable)
{
	char cSectionName[MAX_STRING_LEN] = { 0x00 };
	char cVariableName[MAX_STRING_LEN] = { 0x00 };

	wcstombs(cSectionName, SectionName, MAX_STRING_LEN);
	wcstombs(cVariableName, VariableName, MAX_STRING_LEN);

	return GetVariableInSection(cSectionName, cVariableName, RetVariable);
}

bool INI_FILE::GetVariableInSection(wchar_t *SectionName, wchar_t *VariableName, bool *RetVariable)
{
	char cSectionName[MAX_STRING_LEN] = { 0x00 };
	char cVariableName[MAX_STRING_LEN] = { 0x00 };

	wcstombs(cSectionName, SectionName, MAX_STRING_LEN);
	wcstombs(cVariableName, VariableName, MAX_STRING_LEN);

	return GetVariableInSection(cSectionName, cVariableName, RetVariable);
}

bool INI_FILE::GetSectionVariablesList(wchar_t *SectionName, INI_SECTION_VARLIST *VariablesList)
{
	char cSectionName[MAX_STRING_LEN] = { 0x00 };

	wcstombs(cSectionName, SectionName, MAX_STRING_LEN);

	return GetSectionVariablesList(cSectionName, VariablesList);
}