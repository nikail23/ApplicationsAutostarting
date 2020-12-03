#include "Model.h"

AutostartListModel::AutostartListModel()
{
	/*HKEY rKey;
	TCHAR Reget[256] = { 0 };
	DWORD RegetPath = sizeof(Reget);

	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", NULL, KEY_QUERY_VALUE, &rKey);
	RegQueryValueEx(rKey, "Version", NULL, NULL, (LPBYTE)&Reget, &RegetPath);

	*/
}

void AutostartListModel::AddAll(std::initializer_list<AutostartedAppInfo> newAppsInfo)
{
	auto endIter = appsList.cend();
	appsList.insert(endIter, newAppsInfo);
}

void AutostartListModel::Add(AutostartedAppInfo appInfo)
{
	appsList.push_back(appInfo);
}

void AutostartListModel::Delete(AutostartedAppInfo appInfo)
{
	for (auto iter = appsList.begin(); iter != appsList.end(); iter++)
	{
		if (((*iter).appExePath == appInfo.appExePath) && ((*iter).appName == appInfo.appName)) {

		}
	}
}

char** AutostartListModel::Get()
{
	return nullptr;
}
