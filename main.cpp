#include <iostream>
#include "KeInterface.h"


int main()
{
	KeInterface Driver("\\\\.\\hx_kernel_process_worker");
	DWORD ProcessId = 0x31d4; // hardcode

	Driver.WriteVirtualMemory(ProcessId, 0xfcfe88 /* hardcode */, 0xDEADBEEF, 4);

	return 0;
}