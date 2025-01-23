FLONG WINAPI ManageRegW(HKEY hKey, LPCWSTR lpSubKey, LPCWSTR lpValueName, DWORD dwType, BYTE lpData, LPBYTE lpData2, bool isSet, bool isString) {
    HKEY hkResult;
    if (isSet == false) {
        if (isString == false) {
            RegCreateKeyW(hKey, lpSubKey, &hkResult);
            RegSetValueExW(hkResult, lpValueName, 0, dwType, &lpData, sizeof(lpData));
        }
        else if (isString == true) {
            RegCreateKeyW(hKey, lpSubKey, &hkResult);
            RegSetValueExW(hkResult, lpValueName, 0, REG_SZ, lpData2, sizeof(lpData2) * 16);
        }
    }
    else if (isSet == true) {
        if (isString == false) {
            RegOpenKeyW(hKey, lpSubKey, &hkResult);
            RegSetValueExW(hkResult, lpValueName, 0, dwType, &lpData, sizeof(lpData));
        }
        else if (isString == true) {
            RegOpenKeyW(hKey, lpSubKey, &hkResult);
            RegSetValueExW(hkResult, lpValueName, 0, REG_SZ, lpData2, sizeof(lpData2) * 16);
        }
    }
}
