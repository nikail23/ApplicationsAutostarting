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
		BOOL WriteToRegistry(AutostartedAppInfo appInfo);
	public: 
		AutostartListModel();
		void Refresh();
		BOOL Add(AutostartedAppInfo appInfo);
		BOOL Delete(AutostartedAppInfo appInfo);
		std::list<AutostartedAppInfo> Get();
};

