#pragma once
#include <string.h>

class CStringArray
{
	private:
		char** strings;    
	public:
		int count;
		CStringArray();
		void Add(const char*);
		char** Get();
};

