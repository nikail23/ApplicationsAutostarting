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
		std::list<AutostartedAppInfo> LoadListFromRegistry();
		BOOL IsInRegister(AutostartedAppInfo appInfo);
	public: 
		AutostartListModel();
		void Refresh();
		void Add(AutostartedAppInfo appInfo);
		void WriteToRegistry(AutostartedAppInfo appInfo);
		void Delete(AutostartedAppInfo appInfo);
		std::list<AutostartedAppInfo> Get();
};

