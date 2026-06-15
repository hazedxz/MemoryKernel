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

#ifndef MEMPATCHER_H
#define MEMPATCHER_H

//**********************************************************************************************************************************

class CMemoryPatcher
{
	public:
    	CMemoryPatcher();
        ~CMemoryPatcher();
		bool	Init();
		bool	FindModuleInProcess (const char * module_name, DWORD pid, MODULEENTRY32 * modentry);
		DWORD	FindPattern (DWORD pid, BYTE * pattern, DWORD pattern_length, DWORD start_addr, DWORD process_len);
	private:
		void		Error (const char * fmt, ...);
		void		FreeProcessHandle(HANDLE hSnapShot);
		bool		ModulesLookup (DWORD pid, const char * name, DWORD addr, MODULEENTRY32 * modentry);
		DWORD		ReadFromProcessToBuf (HANDLE hProcess, void * addr, BYTE * buf, DWORD length);
		std::string	szErrorMsg;
        HMODULE		hKernel32;
		HANDLE		(WINAPI *pfnCreateToolhelp32Snapshot) (DWORD, DWORD);
		BOOL		(WINAPI *pfnProcess32First) (HANDLE, LPPROCESSENTRY32);
		BOOL		(WINAPI *pfnProcess32Next) 	(HANDLE, LPPROCESSENTRY32);
		BOOL 		(WINAPI *pfnModule32First)  (HANDLE, LPMODULEENTRY32);
		BOOL 		(WINAPI *pfnModule32Next)   (HANDLE, LPMODULEENTRY32);
		void 		(WINAPI *pfnCloseToolhelp32Snapshot) (HANDLE);
		LPVOID 		(WINAPI *pfnVirtualAllocEx) (HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect);
};

//**********************************************************************************************************************************

#endif

//**********************************************************************************************************************************
