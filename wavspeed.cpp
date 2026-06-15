#include "client.h"

SpeedBot Speedbot;

//***************************************************************************
DWORD HwBase, HwSize, HwEnd;
DWORD SpeedPtr;
DWORD dwSpeedptr = 0;
DWORD GetModuleSize(const DWORD Address){return PIMAGE_NT_HEADERS(Address + (DWORD)PIMAGE_DOS_HEADER(Address)->e_lfanew)->OptionalHeader.SizeOfImage;}
DWORD FarProc(const DWORD Address, DWORD LB, DWORD HB){return ( (Address < LB) || (Address > HB) );}

#define RENDERTYPE_UNDEFINED	0
#define RENDERTYPE_SOFTWARE		1
#define RENDERTYPE_HARDWARE		2

#define CompareMemory2(Buff1, Buff2, Size) __comparemem((const UCHAR *)Buff1, (const UCHAR *)Buff2, (UINT)Size)
#define FindMemoryClone2(Start, End, Clone, Size) __findmemoryclone((const ULONG)Start, (const ULONG)End, (const ULONG)Clone, (UINT)Size)
#define FindReference2(Start, End, Address) __findreference((const ULONG)Start, (const ULONG)End, (const ULONG)Address)

//***************************************************************************

void SpeedBot::AdjustSpeed( double x )
{
	if(dwSpeedptr == 0)
	{
		dwSpeedptr = SpeedPtr;
	}
	static double LastSpeed=1;
	if(x!=LastSpeed)
	{
		*(double*)dwSpeedptr = (x * 1000);
		LastSpeed=x;
	}
}

//***************************************************************************

BOOL __comparemem(const UCHAR *buff1, const UCHAR *buff2, UINT size)
{
	for (UINT i = 0; i < size; i++, buff1++, buff2++)
	{
		if ((*buff1 != *buff2) && (*buff2 != 0xFF))
			return FALSE;
	}
	return TRUE;
}

//***************************************************************************

ULONG __findmemoryclone(const ULONG start, const ULONG end, const ULONG clone, UINT size)
{
	for (ULONG ul = start; (ul + size) < end; ul++)
	{
		if (CompareMemory2(ul, clone, size))
			return ul;
	}
	return NULL;
}

//***************************************************************************

ULONG __findreference(const ULONG start, const ULONG end, const ULONG address)
{
	UCHAR Pattern[5];
	Pattern[0] = 0x68;
	*(ULONG*)&Pattern[1] = address;
	return FindMemoryClone2(start, end, Pattern, sizeof(Pattern)-1);
}

//***************************************************************************

void *SpeedBot::SpeedHackPtr(void)
{
	DWORD Old = NULL;
	PCHAR String = "Texture load: %6.1fms";
	DWORD Address = (DWORD)FindMemoryClone2(HwBase, HwBase+HwSize, String, strlen(String));
	void* SpeedPtr = (void*)*(DWORD*)(FindReference2(HwBase, HwBase+HwSize, Address) - 7);
	if ( FarProc((DWORD)SpeedPtr,HwBase,HwEnd) )
	{
	//	MessageBox("Couldn't find SpeedPtr pointer.");
	}
	else
		VirtualProtect(SpeedPtr,sizeof(double),PAGE_READWRITE,&Old);
	return SpeedPtr;
}

//***************************************************************************

/*void *SpeedBot::SpeedHackPtr(void) //if use this then not need Initialize
{
	unsigned long HwBase = (unsigned long)GetModuleHandle(NULL);
	unsigned long HwSize = (unsigned long)0x2116000;
	unsigned long HwEnd = HwBase + HwSize - 1;

	DWORD Old = NULL;
	PCHAR String = "Texture load: %6.1fms";

	DWORD Address = (DWORD)FindMemoryClone2(HwBase, HwBase+HwSize, String, strlen(String));
	void* SpeedPtr = (void*)*(DWORD*)(FindReference2(HwBase, HwBase+HwSize, Address) - 7);

	if ( FarProc((DWORD)SpeedPtr,HwBase,HwEnd) )
	{
	//	MessageBox("Couldn't find SpeedPtr pointer.");
	}
	else
		VirtualProtect(SpeedPtr,sizeof(double),PAGE_READWRITE,&Old);
	return SpeedPtr;
}*/

//***************************************************************************

bool SpeedBot::Initialize(void) //then not need this..............
{

	BYTE HLType = RENDERTYPE_UNDEFINED;

	HwBase = (DWORD)GetModuleHandle("hw.dll"); // Hardware
	if ( HwBase == NULL )
	{
		HwBase = (DWORD)GetModuleHandle("sw.dll"); // Software
		if ( HwBase == NULL )
		{
			HwBase = (DWORD)GetModuleHandle(NULL); // Non-Steam?
			if ( HwBase == NULL ) // Unknown client type
			{
				//MessageBox("Unknown client type.");
			}
			else
				HLType = RENDERTYPE_UNDEFINED;
		}
		else
			HLType = RENDERTYPE_SOFTWARE;
	}
	else
		HLType = RENDERTYPE_HARDWARE;

	HwSize = (DWORD)GetModuleSize(HwBase);
	if ( HwSize == NULL )
	{
		switch(HwSize)
		{
		case RENDERTYPE_HARDWARE:  {HwSize = 0x122A000;}break;
		case RENDERTYPE_UNDEFINED: {HwSize = 0x2116000;}break;
		case RENDERTYPE_SOFTWARE:  {HwSize = 0xB53000;}break;
		default:                   {/*MessageBox("Couldn't find module size.");*/}break;
		}
	}
	HwEnd = HwBase + HwSize - 1;

	return (HwBase);
}

//***************************************************************************

