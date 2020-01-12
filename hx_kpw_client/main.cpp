#include <iostream>
#include "KeInterface.h"


int main()
{
	KeInterface Driver("\\\\.\\hx_kernel_process_worker");
	DWORD ProcessId = 0x3d40; // hardcode

	Driver.WriteVirtualMemory(ProcessId, 0x5630bbfd30 /* hardcode */, 0xDEADBEEF, 4);

	return 0;
}