#include <iostream>
#include <defs.h>

#include "KeInterface.h"

void PrintBytesHex(BYTE* arr, UINT size);

int main()
{
	KeInterface Driver("\\\\.\\" DEVICE_NAME);
	DWORD ProcessId = 0x589c; // hardcode
	
	BYTE a[30];

	for (UINT i = 0, j = sizeof(a); i < sizeof(a); i++, j--)
	{
		a[i] = (BYTE)j;
	}
	PrintBytesHex(a, sizeof(a));
	Driver.WriteVirtualMemory(ProcessId, 0x68feaff8e0 /* hardcode */, a, sizeof(a));

	return 0;
}

void PrintBytesHex(BYTE* arr, UINT size)
{
	for (UINT i = 0; i < size; i++)
	{
		printf("%02x ", arr[i]);
	}
}