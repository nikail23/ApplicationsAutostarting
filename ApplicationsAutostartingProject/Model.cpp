#include "Model.h"
#define SUBKEY "Software\\Microsoft\\Windows\\CurrentVersion\\Run"

#if defined(_WIN64)
#define CROSS_ACCESS KEY_WOW64_32KEY
#else
#define CROSS_ACCESS KEY_WOW64_64KEY
#endif

AutostartListModel::AutostartListModel()
{
	Refresh();
}

void AutostartListModel::Refresh()
{
	appsList = LoadListFromRegistry();
}

std::list<AutostartedAppInfo> AutostartListModel::LoadListFromRegistry()
{
	std::list<AutostartedAppInfo> list = std::list<AutostartedAppInfo>();
	HKEY currentKey;
	DWORD result = RegOpenKeyEx(HKEY_CURRENT_USER, SUBKEY, 0, KEY_READ | CROSS_ACCESS, &currentKey);
	if (result == ERROR_SUCCESS)
	{
		DWORD valuesCount, maxValueNameSize, maxValueDataSize;

		RegQueryInfoKey(currentKey, NULL, 0, NULL, NULL, NULL, NULL, &valuesCount, &maxValueNameSize, &maxValueDataSize, NULL, NULL);
		for (unsigned int i = 0; i < valuesCount; i++)
		{
			LPSTR valueName = (LPSTR)malloc((++maxValueNameSize) * sizeof(CHAR));
			DWORD valueNameSize = maxValueNameSize;
			DWORD valueType;
			LPBYTE valueData = (LPBYTE)malloc((maxValueDataSize) * sizeof(BYTE));
			DWORD valueDataSize = maxValueDataSize;

			result = RegEnumValue(currentKey, i, valueName, &valueNameSize, NULL, &valueType, valueData, &valueDataSize);
			if (result == ERROR_SUCCESS && valueType == REG_SZ)
			{
				list.push_back({ (char*)valueName, (char*)valueData });
			}
		}
		RegCloseKey(currentKey);
	}
	return list;
}

BOOL AutostartListModel::IsInRegister(AutostartedAppInfo appInfo)
{
	std::list<AutostartedAppInfo> list = LoadListFromRegistry();
	for (auto iter = list.begin(); iter != list.end(); iter++)
	{
		if ((*iter).appExePath == appInfo.appExePath) {
			return TRUE;
		}
	}
	return FALSE;
}

BOOL AutostartListModel::Add(AutostartedAppInfo appInfo)
{
	if (IsInRegister(appInfo)) {
		MessageBox(GetActiveWindow(), "Current app already autostarted!", "Error!", MB_ICONERROR);
		return FALSE;
	}
	else {
		appsList.push_back(appInfo);
		return WriteToRegistry(appInfo);
	}
}

BOOL AutostartListModel::WriteToRegistry(AutostartedAppInfo appInfo)
{
	HKEY key;

	if (EXIT_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER, SUBKEY, 0, KEY_SET_VALUE | CROSS_ACCESS, &key)) {
		RegSetValueEx(key, appInfo.appName, 0, REG_SZ, (BYTE*)appInfo.appExePath, strlen(appInfo.appExePath));
		RegCloseKey(key);
		return TRUE;
	}	
	return FALSE;
}

BOOL AutostartListModel::Delete(AutostartedAppInfo appInfo)
{
	for (auto iter = appsList.begin(); iter != appsList.end(); iter++)
	{
		if (((*iter).appExePath == appInfo.appExePath) && ((*iter).appName == appInfo.appName)) {

		}
	}
	return FALSE;
}

std::list<AutostartedAppInfo> AutostartListModel::Get()
{
	return appsList;
}
