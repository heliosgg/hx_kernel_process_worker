#include <iostream>
#include <defs.h>

#include "KeInterface.h"

void PrintBytesHex(BYTE* arr, UINT size);

int main()
{
	KeInterface Driver("\\\\.\\" DEVICE_NAME);
	DWORD ProcessId = 0x21dc; // hardcode
	
	BYTE a[30];

	Driver.ReadVirtualMemory(ProcessId, (PVOID)0xc6c2b4f850 /* hardcode */, a, sizeof(a));
	PrintBytesHex(a, sizeof(a));

	return 0;
}

void PrintBytesHex(BYTE* arr, UINT size)
{
	for (UINT i = 0; i < size; i++)
	{
		printf("%02x ", arr[i]);
	}
}