#include "client.h"

StudioOffsets Studiooffsets;

//***************************************************************************

char* ModelrString = "cl_himodels";

//***************************************************************************

#define CompareMemory(Buff1, Buff2, Size) __comparemem ((const unsigned char*) Buff1, (const unsigned char*) Buff2, (unsigned int) Size)
#define FindMemoryClone(start, end, clone, clonesize) __findmemoryclone((const unsigned long) start, (const unsigned long) end, (const unsigned long) clone, (unsigned int) clonesize)
#define FindReference(start, end, address, type) __findreference((const unsigned long) start, (const unsigned long) end, (const unsigned long) address, (const unsigned char) type)
#define REFERENCE_ABSOLUTE_PUSH 1

//***************************************************************************

bool __comparemem (const unsigned char* Buff1, const unsigned char* Buff2, unsigned int Size)
{
	for( unsigned int i=0; i < Size; i++, Buff2++, Buff1++ )
	{
		if((*Buff1 != *Buff2) && (*Buff2 != 0xFF))
			return false;
	}
	return true;
}

//**********************************************************************************************************************************

void* __findmemoryclone(const unsigned long start, const unsigned long end, const unsigned long clone, unsigned int clonesize)
{
	for( unsigned long ul = (unsigned long)start; (ul + clonesize) < end; ul++)
	{
		if(CompareMemory(ul, clone, clonesize))
			return (void*)ul;
	}
	return NULL;
}

//**********************************************************************************************************************************

void* __findreference(const unsigned long start, const unsigned long end, const unsigned long address, const unsigned char type)
{
	unsigned char Pattern[5];

	if ( type == REFERENCE_ABSOLUTE_PUSH )
	{
		Pattern[0] = 0x68;
		*(unsigned long*)&Pattern[1] = address;
	}

	return FindMemoryClone(start, end, Pattern, sizeof(Pattern)-1);
}

//***************************************************************************

void* StudioOffsets::OffsetCStudioModelRenderer(void)
{
	unsigned long hlBase = (unsigned long)GetModuleHandle(NULL);
	unsigned long hlSize = (unsigned long)0x2116000;

	ModelrString = (char*)FindMemoryClone(hlBase, hlBase+hlSize, ModelrString, strlen(ModelrString));
	if(ModelrString == NULL)
		return NULL;

	void* pInit = (void*)FindReference(hlBase, hlBase+hlSize, ModelrString, REFERENCE_ABSOLUTE_PUSH);
	if(pInit == NULL)
		return NULL;

	for(unsigned char* b = (unsigned char*)pInit; (DWORD)b > ((DWORD)pInit-0x10); b--)
	{
		if(*(b-1) == 0x90 && *(b-2) == 0x90 )
			return (void*)((DWORD)FindMemoryClone(hlBase, hlBase+hlSize, &b, sizeof(DWORD)) - sizeof(DWORD));
	}

	return NULL;
}

//***************************************************************************
