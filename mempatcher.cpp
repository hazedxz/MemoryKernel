/************************************************************************************************************************************
*
*
* 007 HOOK
* Code By: 007 + boy_scout
* msn: david_bs@live.com
* (c)2011
* www.etalking.com.ar
*
*
************************************************************************************************************************************/

#include "client.h"

//**********************************************************************************************************************************

const unsigned long PAGE_SIZE = 4096;

//**********************************************************************************************************************************

CMemoryPatcher::CMemoryPatcher()
{
	hKernel32 = 0;
	pfnCreateToolhelp32Snapshot = 0;
	pfnProcess32First = 0;
	pfnProcess32Next = 0;
	pfnModule32First = 0;
	pfnModule32Next = 0;
	pfnCloseToolhelp32Snapshot = 0;
}

//**********************************************************************************************************************************

CMemoryPatcher::~CMemoryPatcher()
{
	if ( hKernel32 )
		FreeLibrary (hKernel32);
}

//**********************************************************************************************************************************

void CMemoryPatcher::Error (const char* fmt, ...)
{
	va_list va_alist;
	char buf[512];
	va_start (va_alist, fmt);
	_vsnprintf (buf, sizeof(buf), fmt, va_alist);
	va_end (va_alist);
	szErrorMsg = buf;
}

//**********************************************************************************************************************************

bool CMemoryPatcher::Init()
{
	if ( (hKernel32 = LoadLibrary("kernel32.dll")) == 0 )
	{
		Error ("Could not open kernel32.dll: %s", strerror(errno));
		return false;
	}
	if ( (pfnCreateToolhelp32Snapshot = (HANDLE	(WINAPI*) (DWORD, DWORD)) GetProcAddress(hKernel32, "CreateToolhelp32Snapshot")) == 0 )
	{
		Error ("Could not get CreateToolhelp32Snapshot address\nIf you use Windows NT 4, you need libloader for NT.");
		return false;
	}
	if ( (pfnProcess32First = (BOOL (WINAPI*) (HANDLE, LPPROCESSENTRY32)) GetProcAddress(hKernel32, "Process32First")) == 0 )
	{
		Error ("Could not get Process32First address");
		return false;
	}
	if ( (pfnProcess32Next = (BOOL (WINAPI*) (HANDLE, LPPROCESSENTRY32)) GetProcAddress(hKernel32, "Process32Next")) == 0 )
	{
		Error ("Could not get Process32Next address");
		return false;
	}
	if ( (pfnModule32First = (BOOL (WINAPI*) (HANDLE, LPMODULEENTRY32)) GetProcAddress(hKernel32, "Module32First")) == 0 )
	{
		Error ("Could not get Module32First address");
		return false;
	}
	if ( (pfnModule32Next = (BOOL (WINAPI*) (HANDLE, LPMODULEENTRY32)) GetProcAddress(hKernel32, "Module32Next")) == 0 )
	{
		Error ("Could not get Process32Next address");
		return false;
	}
	pfnVirtualAllocEx = (LPVOID (WINAPI *) (HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect)) GetProcAddress(hKernel32, "VirtualAllocEx");
	pfnCloseToolhelp32Snapshot = (void (WINAPI*) (HANDLE)) GetProcAddress(hKernel32, "CloseToolhelp32Snapshot");
	return true;
}

//**********************************************************************************************************************************

void CMemoryPatcher::FreeProcessHandle(HANDLE hSnapShot)
{
	if ( hSnapShot != INVALID_HANDLE_VALUE )
	{
		if ( pfnCloseToolhelp32Snapshot )
			(*pfnCloseToolhelp32Snapshot)(hSnapShot);
		else
			CloseHandle(hSnapShot);
	}
}

//**********************************************************************************************************************************

bool CMemoryPatcher::FindModuleInProcess (const char * module_name, DWORD pid, MODULEENTRY32 * modentry)
{
	if ( pid )
		return ModulesLookup(pid, module_name, 0, modentry);
	HANDLE hAllProcesses = INVALID_HANDLE_VALUE;
	PROCESSENTRY32 hProcEntry;
	hProcEntry.dwSize = sizeof(PROCESSENTRY32);
	if ( (hAllProcesses = (*pfnCreateToolhelp32Snapshot) (TH32CS_SNAPPROCESS, 0)) == INVALID_HANDLE_VALUE )
	{
		Error ("CreateToolhelp32Snapshot: %s", strerror(errno));
        return false;
	}
	if ( (*pfnProcess32First) (hAllProcesses, &hProcEntry) )
	{
		for ( ; ; )
		{
			if ( hProcEntry.th32ProcessID != 0 )
			{
				if ( ModulesLookup (hProcEntry.th32ProcessID, module_name, 0, modentry) )
				{

					FreeProcessHandle (hAllProcesses);
					return true;
				}
			}
			hProcEntry.dwSize = sizeof(PROCESSENTRY32);
            if ( !(*pfnProcess32Next) (hAllProcesses, &hProcEntry) )
        		break;
		}
	}
	FreeProcessHandle (hAllProcesses);
	return false;
}

//**********************************************************************************************************************************

bool CMemoryPatcher::ModulesLookup (DWORD pid, const char * name, DWORD addr, MODULEENTRY32 * modentry)
{
	char needed_name[256], module_name[256];
	HANDLE hAllModules = INVALID_HANDLE_VALUE;
	bool fFound = false;
	if ( name )
	{
		strcpy (needed_name, name);
		strupr (needed_name);
	}
	if ( (hAllModules = (*pfnCreateToolhelp32Snapshot) (TH32CS_SNAPMODULE, pid)) == INVALID_HANDLE_VALUE )
		return false;
    modentry->dwSize = sizeof(MODULEENTRY32);
	if ( (*pfnModule32First) (hAllModules, modentry) )
	{
		for ( ; fFound == false; )
		{
			modentry->dwSize = sizeof(MODULEENTRY32);
			if ( name )
			{
				strcpy (module_name, modentry->szModule);
				strupr (module_name);
				if ( strstr(module_name, needed_name) )
				{
					FreeProcessHandle (hAllModules);
					return true;
				}
			}
			else
			{
				if ( addr >= (DWORD) modentry->modBaseAddr 
				&&  addr <= ((DWORD) modentry->modBaseAddr + modentry->modBaseSize) )
				{
					FreeProcessHandle (hAllModules);
					return true;
				}
			}
			if ( !(*pfnModule32Next) (hAllModules, modentry) )
	        	break;
		}
	}
	FreeProcessHandle (hAllModules);    
	return false;
}

//**********************************************************************************************************************************

DWORD CMemoryPatcher::FindPattern (DWORD pid, BYTE * pattern, DWORD pattern_length, DWORD start_addr, DWORD process_len)
{
	DWORD found_addr = 0;
	HANDLE hProcess = OpenProcess (PROCESS_VM_OPERATION|PROCESS_VM_READ|PROCESS_VM_WRITE, FALSE, pid);
	BYTE * tempbuf = new BYTE [PAGE_SIZE];
	if ( hProcess )
	{
		for ( DWORD current = 0; current < process_len && found_addr == 0; )
		{
			DWORD amount = process_len - current > PAGE_SIZE ? PAGE_SIZE : process_len - current;
			if ( !ReadFromProcessToBuf(hProcess, (void*) (start_addr + current), tempbuf, amount) )
				break;
			for ( int i = 0; i < amount - pattern_length; i++ )
			{
				if ( !memcmp (tempbuf+i, pattern, pattern_length) )
				{
					found_addr = start_addr + current + i;
					break;
				}
			}
			current += amount;
		}
		CloseHandle (hProcess);
	}
	else
		Error ("OpenProcess error: %s", strerror(errno));
	delete tempbuf;
	return found_addr;
}

//**********************************************************************************************************************************

DWORD CMemoryPatcher::ReadFromProcessToBuf (HANDLE hProcess, void * addr, BYTE * buf, DWORD length)
{
	DWORD returnlen = 0, readlen, old_attributes, old_attributes2;
	if ( VirtualProtectEx(hProcess, addr, length, PAGE_READWRITE, &old_attributes) )
	{
		if ( ReadProcessMemory (hProcess, addr, buf, length, &readlen) )
		{
			if ( VirtualProtectEx(hProcess, addr, length, old_attributes, &old_attributes2) )
			{
				returnlen = readlen;
			}
			else
				Error ("VirtualProtectEx error: %d", GetLastError());
		}
		else
			Error ("ReadProcessMemory error: %d", GetLastError());
	}
	else
		Error ("VirtualProtectEx error: %d", GetLastError());
	return returnlen;
}

//**********************************************************************************************************************************

