#include <stdio.h>
#include <windows.h>
#include <winreg.h>
#include <string.h>
#include <shellapi.h>
#include <tchar.h>

int CloseKey(HKEY hKey);

int main()
{
    LSTATUS lResult;
    HKEY hKey;

    lResult = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_READ, &hKey);

    if (lResult != ERROR_SUCCESS)
    {
        if (lResult == ERROR_FILE_NOT_FOUND)
        {
            printf("Key was not found.\n");
            return 1;
        }
        else
        {
            printf("Error while opening the key\n");
            return 1;
        }
    }

    DWORD cSubKeys, maxSubkeyLen, cValues, maxValueLen, retCode;

    RegQueryInfoKey(hKey,
        NULL, NULL, NULL,
        &cSubKeys, &maxSubkeyLen,
        NULL, &cValues, &maxValueLen,
        NULL, NULL, NULL);

    TCHAR valueName[256];
    BYTE data[1024];
    DWORD valueNameSize, dataSize, type;
    DWORD index = 0;

    if (cValues == 0)
    {
        _tprintf(TEXT("The opened key is empty\n"));
        return CloseKey(hKey);
    }

    while (1)
    {
        valueNameSize = sizeof(valueName);
        dataSize = sizeof(data);
        lResult = RegEnumValue(hKey, index, valueName, &valueNameSize, NULL, &type, (LPBYTE)data, &dataSize);

        if (lResult != ERROR_SUCCESS)
        {
            break;
        }

        data[dataSize] = '\0';

        _tprintf(TEXT("(%d) %s -> %s\n"), index + 1, valueName, data);

        index++;
    }

    return CloseKey(hKey);
}

int CloseKey(HKEY hKey)
{
    RegCloseKey(hKey);
    return 0;
}