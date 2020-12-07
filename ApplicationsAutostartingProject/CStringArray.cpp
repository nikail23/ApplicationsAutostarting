#define _CRT_SECURE_NO_WARNINGS
#include "CStringArray.h"

CStringArray::CStringArray()
{
	strings = 0;
	count = 0;
}

void CStringArray::Add(const char* newString)
{
	char** newStrings = new char* [count + 1];
	memcpy(newStrings, strings, sizeof(char*) * count);
	delete[] strings;
	strings = newStrings;
	strings[count] = new char[strlen(newString) + 1];
	strcpy(strings[count], newString);
	count++;
}

char** CStringArray::Get()
{
	return strings;
}
