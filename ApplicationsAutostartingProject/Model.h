#pragma once
#include <windows.h>
#include <list>

struct AutostartedAppInfo
{
	char* appName;
	char* appExePath;
};

class AutostartListModel
{
	private:
		std::list<AutostartedAppInfo> appsList;
	public: 
		AutostartListModel();
		void AddAll(std::initializer_list<AutostartedAppInfo> newAppsInfo);
		void Add(AutostartedAppInfo appInfo);
		void Delete(AutostartedAppInfo appInfo);
		char** Get();
};

