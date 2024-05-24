// This file defines the main process for a Windows service, which is responsible for starting and managing the service. Here, we define multiple function types that help implement the main process.

#pragma once

// Include the header file for Windows version requirements
#include "targetver.h"

// Define macro to disable compiler warnings
#define WIN32_LEAN_AND_MEAN      
#define _CRT_SECURE_NO_WARNINGS


// Include the Windows header files
#include <windows.h>
#include <TlHelp32.h>

// Define function types
typedef VOID(WINAPI* SERVICEMAIN)(DWORD, LPTSTR*);
typedef VOID(WINAPI* SVCHOSTPUSHSERVICEGLOBALS)(VOID*);
typedef HRESULT(WINAPI* SLGETWINDOWSINFORMATIONDWORD)(PCWSTR, DWORD*);

// Implement the main process for the Windows service

