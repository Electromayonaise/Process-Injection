#include <windows.h>
#include <stdio.h>

/*
BOOL CreateProcessW(
    [in, optional] LPCWSTR lpApplicationName, // This is the path to the executable
    [in, out, optional] LPWSTR lpCommandLine, // This is the command line arguments
    [in, optional] LPSECURITY_ATTRIBUTES lpProcessAttributes, // This is the process security attributes
    [in, optional] LPSECURITY_ATTRIBUTES lpThreadAttributes, // This is the thread security attributes
    [in] BOOL bInheritHandles, // This is a boolean value that determines whether or not the new process will inherit the handles of the calling process
    [in] DWORD dwCreationFlags, // This is a set of flags that determine how the process is created
    [in, optional] LPVOID lpEnvironment, // This is a pointer to the environment block for the new process
    [in, optional] LPCWSTR lpCurrentDirectory, // This is the path to the current directory for the new process
    [in] LPSTARTUPINFOW lpStartupInfo, // This is a pointer to a STARTUPINFO or STARTUPINFOEX structure
    [out] LPPROCESS_INFORMATION lpProcessInformation // This is a pointer to a PROCESS_INFORMATION structure that receives identification information about the new process
)
*/

int main(void){

    STARTUPINFOW si = {0};
    PROCESS_INFORMATION pi = {0};

    // on the create process method call, it is important to note that the BELOW_NORMAL_PRIORITY_CLASS flag is used, this is key to malware development, as when a process is falged as REALTIME_PRIORITY_CLASS, 
    // it will be given priority over other processes, will be able to execute faster, and if it is a heavy process, it will be able to consume more resources
    if(!CreateProcessW(L"C:\\Windows\\System32\\notepad.exe", NULL, NULL, NULL, FALSE, BELOW_NORMAL_PRIORITY_CLASS, NULL, NULL, &si , &pi)){

        printf("(-) CreateProcess failed (%d).\n", GetLastError());
        return EXIT_FAILURE;

    } 
    // now we want to get the process id of the newly created process
    printf("(+) Process ID: %ld", pi.dwProcessId);
    return EXIT_SUCCESS;
}