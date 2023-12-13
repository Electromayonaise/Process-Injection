#include <windows.h>

int main(void){
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    if(!CreateProcess(NULL, "C:\\Windows\\System32\\calc.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)){
        MessageBoxW(NULL, L"CreateProcess failed", L"Error", MB_OK);
        return EXIT_FAILURE;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return EXIT_SUCCESS;
}