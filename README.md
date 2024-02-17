<img src="https://user-images.githubusercontent.com/73097560/115834477-dbab4500-a447-11eb-908a-139a6edaec5c.gif">

<div align="center">
  <img src="https://github.com/Electromayonaise/Electromayonaise/blob/main/Assets/github-contribution-grid-snake%20blacktest(1).svg" alt="snake" />
</div>
<div id="user-content-toc">

# About the repo 

Malware development for educational purposes, introduction to Windows API and process injection. 

## Malware Development

Malware refers to any software that is designed to cause damage to a single computer, server, or computer network. Malware is a contraction for "malicious software." Examples of common malware includes viruses, worms, Trojan viruses, spyware, adware, and ransomware.

In order to be classified as malware, rather than a virus or worm, the software must be designed to specifically damage a computer or server. For example, software that secretly tracks what websites you visit and then sends you advertisements based on your browsing habits is not considered malware. However, software that is designed to send your browsing history to a third party without your consent is considered malware.

Malware is often disguised as, or embedded in, non-malicious files. For example, a program that claims it will speed up your computer may actually be sending confidential information to a remote intruder. Therefore, it is important to only download files and programs from trusted sources. It is also a good idea to use antivirus software, which will prevent malware from being downloaded onto your computer and will remove any malware software that has already been installed.

To start with malware development you need to know the basics of programming languages like C, C++, Python, Java, etc. You can start with C and C++ as they are the most basic languages and are used in most of the malware development, and have some concepts of assembly. For now, let's start with 3 important concepts: Processes, Threads, and Handles.

### Processes

A process is an instance of a computer program that is being executed. It contains the program code and its activity. Depending on the operating system (OS), a process may be made up of multiple threads of execution that execute instructions concurrently.

A computer program is a passive collection of instructions, while a process is the actual execution of those instructions. Several processes may be associated with the same program; for example, opening up several instances of the same program often means more than one process is being executed.

A process is said to own resources which are allocated to it, including memory, file handles, sockets, device handles, windows, and a process identifier. When the process terminates, the operating system reclaims most of the resources, but memory is often left allocated until it is needed by other processes. This is why a process may temporarily require more memory than its associated program's executable code.

This is why a common form of attack is to overflow the memory allocated to a process and inject malicious code into the process memory. This is called a buffer overflow attack. There is also process injection, which is a technique used by computer attackers to introduce a running process into another process, typically during the execution of malicious code.

### Threads

A thread is a path of execution within a process. Also, a process can contain multiple threads. Threads are sometimes called lightweight processes because they have their own stack but can access shared data. Because threads share the same address space as the process and other threads within the process, the operational cost of communication between the threads is low, which is an advantage. The disadvantage is that a problem with one thread in a process will certainly affect other threads and the viability of the process itself.

### Handles

A handle is an abstract reference to a resource that is used when application code interacts with computer operating system resources. Handles are used when a program references a resource such as a file, network object, registry key, or a process. The operating system generates a unique value for each handle to identify the resource and associates internal data structures with the handle. The application receives the handle and uses it to access the resource.

#### Process Handle

A process handle is a reference to a process object. You can use a process handle to manipulate many of the operating system resources associated with a process. For example, you can get or set the process priority class, terminate the process, and get or set the process affinity mask. You can also use a process handle to obtain a handle to a thread of the process by using the OpenThread function.

#### Thread Handle

A thread handle is a reference to a thread object. You can use a thread handle to manipulate many of the operating system resources that are associated with a thread. For example, you can use a thread handle to wait for a thread to terminate, specify the processor that a thread runs on, and retrieve the exit code of a thread.

## Windows API

The Windows API, informally WinAPI, is Microsoft's core set of application programming interfaces (APIs) available in the Microsoft Windows operating systems. The name Windows API collectively refers to several different platform implementations that are often referred to by their own names (for example, Win32 API); see the versions section. Almost all Windows programs interact with the Windows API. On the Windows NT line of operating systems, a small number (such as programs started early in the Windows startup process) use the Native API.

The Windows API consists of mostly "core" functions and is divided into sections known as "modules". Each module exposes a different set of interfaces (for example, WinInet is the API used for accessing the Internet). The primary Windows API modules are: kernel32.dll, user32.dll, gdi32.dll, advapi32.dll, shell32.dll, ole32.dll, odbc32.dll, comdlg32.dll, mpr.dll, wininet.dll, imm32.dll.

The Windows API is not object-oriented. It consists of one or more shared libraries (DLLs) which are loaded into a program's memory at runtime. The API consists of functions implemented, as with Win32, in system DLLs. The DLLs are imported into a program at compile time, and the program makes function calls to these DLLs via a mechanism known as the "run-time dynamic linking" (LoadLibrary/GetProcAddress) mechanism. The functions are mostly focused on GUI (Graphical User Interface) functions such as creating windows, receiving mouse clicks and key-strokes, drawing text and pictures, etc. The most commonly used API functions, such as those for memory management and character conversion, are part of the C standard library, which is implemented as a DLL, usually referred to as either MSVCRT.LIB or MSVCRT.DLL, which comes with all versions of Windows.

One thing to note is the hungarian notation, which we will often see in the Windows API. Hungarian notation is an identifier naming convention in computer programming, in which the name of a variable or function indicates its intention or kind, and in some dialects its type. The original Hungarian Notation uses intention or kind in its naming convention and is sometimes called Apps Hungarian as it became popular in the Microsoft Apps division in the development of Word, Excel and other apps. The notation was invented by Charles Simonyi from Microsoft, inspired by the notion of a type system and the Hungarian language. It consists in prefixing a variable's name with one or more letters representing the variable's type, for example: 

- h for a handle (usually an integer)
- p for a pointer
- c for a count
- dw for a double-word (32-bit integer)
- lp for a long pointer (64-bit pointer)
- sz for a zero-terminated string
- b for a boolean value (usually an integer with value 0 or 1)
- i for an integer

# Process Injection 

As I said before, process injection is a technique used by computer attackers to introduce a running process into another process, typically during the execution of malicious code. The general idea is to inject a malicious code into a process that is already running on the system, and then execute that code via the process. This is done by manipulating the memory space of the target process. The injected code runs under the same privileges as the target process. This is a very common technique used by malware to hide its presence on the system.

There are several ways to inject a process, but we will focus on shellcode injection and DLL injection.

## Shellcode Injection

Shellcode injection is a technique used to exploit a software vulnerability. It is the exploitation of a software bug in order to gain control of a computer system or allow privilege escalation or a denial of service on a computer system. Shellcode injection consists of the following main parts:

- The shellcode
- The shellcode injector
- The target

The shellcode is the code that we want to inject into the target process. The shellcode injector is the code that will inject the shellcode into the target process. The target is the process that we want to inject the shellcode into.

The code for shellcode injection on this repo is in the file `shellcodeInjection.cpp`. But the overall idea is to create a process in suspended mode, allocate memory in the process, write the shellcode into the allocated memory, and then resume the process. The shellcode on the file won't do anything, it's just a sample shellcode to show how the injection works. To get the shellcode, you can run a Kali Linux machine and use msfvenom to generate a shellcode. For example, to generate a shellcode that will spawn a reverse shell to your Kali Linux machine, and then inject it into a process to gain access to the machine. 

## DLL Injection

A DLL (Dynamic Link Library) is a library that contains code and data that can be used by more than one program at the same time. For example, in Windows operating systems, the Comdlg32 DLL performs common dialog box related functions. Therefore, each program can use the functionality that is contained in this DLL to implement an Open dialog box. This helps promote code reuse and efficient memory usage. The code in a DLL is usually shared among all the processes that use the DLL; that is, they occupy a single place in physical memory, and do not take up space in the page file. This is why a DLL is called a dynamic link library.

DLL injection is a technique used to inject a DLL into a process. DLL injection is often used by malware to hide its presence on the system. The code for DLL injection on this repo is in the file `dllInjection.cpp` The general idea is to inject a DLL into a process that is already running on the system, and then execute that DLL via the process. This is done by manipulating the memory space of the target process. The injected DLL runs under the same privileges as the target process. As you can see, it follows pretty much the same idea as shellcode injection, but instead of injecting shellcode, we inject a DLL. It is often used in game hacking, where you inject a DLL into a game process to gain access to the game's memory and then manipulate it to your advantage.

