#include "Model.h"
#define AUTOSTART_SUBKEY "Software\\Microsoft\\Windows\\CurrentVersion\\Run"
#define ONCE_AUTOSTART_SUBKEY "Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce"

#if defined(_WIN64)
#define CROSS_ACCESS KEY_WOW64_32KEY
#else
#define CROSS_ACCESS KEY_WOW64_64KEY
#endif

AutostartListModel::AutostartListModel() {
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
	DWORD result = RegOpenKeyEx(HKEY_CURRENT_USER, AUTOSTART_SUBKEY, 0, KEY_READ | CROSS_ACCESS, &currentKey);
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
				list.push_back({ (char*)valueName, (char*)valueData, FALSE });
			}
		}
		RegCloseKey(currentKey);
	}
	result = RegOpenKeyEx(HKEY_CURRENT_USER, ONCE_AUTOSTART_SUBKEY, 0, KEY_READ | CROSS_ACCESS, &currentKey);
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
				list.push_back({ (char*)valueName, (char*)valueData, TRUE });
			}
		}
		RegCloseKey(currentKey);
	}
	return list;
}

BOOL AutostartListModel::Add(AutostartedAppInfo appInfo)
{
	return WriteToRegistry(appInfo);
}

BOOL AutostartListModel::WriteToRegistry(AutostartedAppInfo appInfo)
{
	HKEY key;
	if (appInfo.isOnce) {
		if (EXIT_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER, ONCE_AUTOSTART_SUBKEY, 0, KEY_SET_VALUE | CROSS_ACCESS, &key)) {
			RegSetValueEx(key, appInfo.appName, 0, REG_SZ, (BYTE*)appInfo.appExePath, strlen(appInfo.appExePath));
			RegCloseKey(key);
			return TRUE;
		}
		return FALSE;
	}
	else {
		if (EXIT_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER, AUTOSTART_SUBKEY, 0, KEY_SET_VALUE | CROSS_ACCESS, &key)) {
			RegSetValueEx(key, appInfo.appName, 0, REG_SZ, (BYTE*)appInfo.appExePath, strlen(appInfo.appExePath));
			RegCloseKey(key);
			return TRUE;
		}
		return FALSE;
	}
}

BOOL AutostartListModel::RemoveFromRegistry(AutostartedAppInfo appInfo)
{
	HKEY key;
	if (appInfo.isOnce) {
		if (EXIT_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER, ONCE_AUTOSTART_SUBKEY, 0, KEY_SET_VALUE | CROSS_ACCESS, &key)) {
			RegDeleteValue(key, appInfo.appName);
			RegCloseKey(key);
			return TRUE;
		}
		return FALSE;
	}
	else {
		if (EXIT_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER, AUTOSTART_SUBKEY, 0, KEY_SET_VALUE | CROSS_ACCESS, &key)) {
			RegDeleteValue(key, appInfo.appName);
			RegCloseKey(key);
			return TRUE;
		}
		return FALSE;
	}
}

BOOL AutostartListModel::Delete(int index)
{
	int i = 0;
	for (auto iter = appsList.begin(); iter != appsList.end(); iter++)
	{
		if (i == index) {
			return RemoveFromRegistry(*iter);
		}
		i++;
	}
	return FALSE;
}

std::list<AutostartedAppInfo> AutostartListModel::Get()
{
	return appsList;
}
