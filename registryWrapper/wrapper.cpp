#include "wrapper.h"

/*
   This function, RegWrite, is a C++ wrapper for Windows Registry manipulation. It is designed to simplify the process of writing registry entries. The function takes four parameters: the path to the registry key, the name of the registry entry, the value to be written, and the data type of the value.

   It performs the following tasks:
   1. Determines the root registry key based on the provided path, allowing for the specification of HKEY_CURRENT_USER (HKCU), HKEY_LOCAL_MACHINE (HKLM), or HKEY_CLASSES_ROOT (HKCR) as the base key.
   2. Adjusts the path to exclude the root key prefix (e.g., "HKCU\") to obtain the subkey where the value will be written.
   3. Attempts to create the specified registry key using RegCreateKeyEx, ensuring it is non-volatile and writable.
   4. If the key creation is successful, it proceeds to write the value to the registry using RegSetValueEx, including the name, type, and value data.
   5. If the value writing operation fails, it throws a runtime_error with an error message, otherwise, it closes the registry key.

   In summary, this function simplifies the process of writing registry entries in the Windows Registry by abstracting the details of key creation and value writing, making it more convenient for developers to work with the Windows Registry.
*/
void Wrapper::RegWrite(LPCWSTR path, LPCWSTR name, LPCWSTR value, DWORD type) {
    HKEY rootKey = HKEY_CURRENT_USER; // default

    const wchar_t* branch[] { L"HKCU\\", L"HKLM\\", L"HKCR\\" };
    HKEY keys[] { HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE, HKEY_CLASSES_ROOT };

    for (int j = 0; j < sizeof(branch); j++) {
        if (wcsncmp(path, branch[j], 5) == 0) {
            rootKey = keys[j];
            path += 5;
            break;
        }
    }

    try {
        if (RegCreateKeyEx(rootKey, path, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &rootKey, NULL) == ERROR_SUCCESS) {
            if (RegSetValueEx(rootKey, name, 0, type, (LPBYTE)value, ((wcslen(value) + 1) * sizeof(wchar_t))) == ERROR_SUCCESS) {
                RegCloseKey(rootKey);
            }
            else {
                throw std::runtime_error("failed to RegSetValueEx");
            }
            
        }
        else {
            throw std::runtime_error("failed to RegCreateKeyEx");
        }
    }
    catch (const std::exception& ex) {
        MessageBoxA(NULL, ex.what(), "error", MB_ICONERROR);
    }
}

void Wrapper::RegWrite(LPCWSTR path, LPCWSTR name, DWORD value, DWORD type) {
    HKEY rootKey = HKEY_CURRENT_USER; // default

    const wchar_t* branch[]{ L"HKCU\\", L"HKLM\\", L"HKCR\\" };
    HKEY keys[]{ HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE, HKEY_CLASSES_ROOT };
        
    for (int j = 0; j < sizeof(branch); j++) {
        if (wcsncmp(path, branch[j], 5) == 0) {
            rootKey = keys[j];
            path += 5;
            break;
        }
    }

    try {
        if (RegCreateKeyEx(rootKey, path, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &rootKey, NULL) == ERROR_SUCCESS) {
            if (RegSetValueEx(rootKey, name, 0, type, (LPBYTE)&value, sizeof(value)) == ERROR_SUCCESS) {
                RegCloseKey(rootKey);
            }
            else {
                throw std::runtime_error("failed to RegSetValueEx");
            }
        }
        else {
            throw std::runtime_error("failed to RegCreateKeyEx");
        }
    }
    catch (const std::exception& ex) {
        MessageBoxA(NULL, ex.what(), "error", MB_ICONERROR);
    }
}

/*
   This function, RegDel, is a C++ wrapper for Windows Registry manipulation. It simplifies the process of deleting registry keys in the Windows Registry. The function takes a single parameter, which is the path to the registry key to be deleted.

   The function performs the following tasks:
   1. Determines the root registry key based on the provided path, allowing for the specification of HKEY_CURRENT_USER (HKCU), HKEY_LOCAL_MACHINE (HKLM), or HKEY_CLASSES_ROOT (HKCR) as the base key.
   2. Adjusts the path to exclude the root key prefix (e.g., "HKCU\") to identify the specific key to be deleted.
   3. Attempts to delete the specified registry key using the RegDeleteKey function.
   4. If the key deletion is successful, it closes the root key.
   5. If the deletion operation fails, it throws a runtime_error with an error message and displays an error message in a message box using MessageBoxA.

   In summary, this function simplifies the process of deleting registry keys in the Windows Registry by abstracting the details of key deletion and handling any potential errors, making it more convenient for developers to work with the Windows Registry.
*/

void Wrapper::RegDel(LPCWSTR path) {
    HKEY rootKey = HKEY_CURRENT_USER; // default

    const wchar_t* branch[]{ L"HKCU\\", L"HKLM\\", L"HKCR\\" };
    HKEY keys[]{ HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE, HKEY_CLASSES_ROOT };

    for (int j = 0; j < sizeof(branch); j++) {
        if (wcsncmp(path, branch[j], 5) == 0) {
            rootKey = keys[j];
            path += 5;
            break;
        }
    }

    try {
        if (RegDeleteKey(rootKey, path) == ERROR_SUCCESS) {
            RegCloseKey(rootKey);
        }
        else {
            throw std::runtime_error("failed to RegDeleteKey");
        }
    }
    catch (const std::exception& ex) {
        MessageBoxA(NULL, ex.what(), "error", MB_ICONERROR);
    }
}

void Wrapper::RegDel(LPCWSTR path, LPCWSTR name) {
    HKEY rootKey = HKEY_CURRENT_USER; // default

    const wchar_t* branch[]{ L"HKCU\\", L"HKLM\\", L"HKCR\\" };
    HKEY keys[]{ HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE, HKEY_CLASSES_ROOT };

    for (int j = 0; j < sizeof(branch); j++) {
        if (wcsncmp(path, branch[j], 5) == 0) {
            rootKey = keys[j];
            path += 5;
            break;
        }
    }

    try {
        if (RegOpenKeyEx(rootKey, path, 0, KEY_ALL_ACCESS, &rootKey) == ERROR_SUCCESS) {
            if (RegDeleteValue(rootKey, name) == ERROR_SUCCESS) {
                RegCloseKey(rootKey);
            }
            else {
                throw std::runtime_error("failed to RegDeleteValue");
            }
        }
        else {
            throw std::runtime_error("failed to RegOpenKeyEx");
        }
    }
    catch (const std::exception& ex) {
        MessageBoxA(NULL, ex.what(), "error", MB_ICONERROR);
    }
}