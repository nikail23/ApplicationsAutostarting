#pragma once
#include <windows.h>
#include <list>

struct AutostartedAppInfo
{
	char* appName;
	char* appExePath;
	BOOL isOnce;
};

class AutostartListModel
{
	private:
		std::list<AutostartedAppInfo> appsList;
		std::list<AutostartedAppInfo> LoadListFromRegistry();
		BOOL WriteToRegistry(AutostartedAppInfo appInfo);
		BOOL RemoveFromRegistry(AutostartedAppInfo appInfo);
	public: 
		AutostartListModel();
		void Refresh();
		BOOL Add(AutostartedAppInfo appInfo);
		BOOL Delete(int index);
		std::list<AutostartedAppInfo> Get();
};

