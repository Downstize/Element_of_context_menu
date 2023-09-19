#include <iostream>
#include <windows.h>
using namespace std;

int main() {
  
    HKEY key;
    if (RegCreateKey(HKEY_CLASSES_ROOT, L"*\\shell\\OpenWithTouch", &key) == ERROR_SUCCESS)
    {
        RegSetValueEx(key, nullptr, 0, REG_SZ, (BYTE*)L"Вывести размер файла", (wcslen(L"Вывести размер файла") + 1) * sizeof(wchar_t));
        RegCloseKey(key);

        if (RegCreateKey(HKEY_CLASSES_ROOT, L"*\\shell\\OpenWithTouch\\command", &key) == ERROR_SUCCESS) {
            wstring command = L"C:\\Windows\\System32\\cmd.exe /k \"echo Размер файла: & echo. & dir /-C /Q /A:-D \"%1\"\"";
            RegSetValueEx(key, nullptr, 0, REG_SZ, (BYTE*)command.c_str(), (command.size() + 1) * sizeof(wchar_t));
            RegCloseKey(key);
        }
        else {
            cerr << "Command key was not created" << endl;
            return 1;
        }
    }
    else {
        cerr << "Main key was not created!" << endl;
        return 1;
    }

    wcout << L"New custom element was created!" << endl;

    return 0;
}