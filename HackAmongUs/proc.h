#pragma once

#ifndef PROC_H

#define PROC_H



#include <iostream>
#include <Windows.h>
#include <string>
#include <tlhelp32.h>
#include <vector>

DWORD GetProcId(const wchar_t* procName);

uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);

uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);


#endif // !PROC_H