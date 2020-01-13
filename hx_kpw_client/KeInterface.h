#pragma once

#include <Windows.h>
#include <defs.h>


class KeInterface
{
public:
	HANDLE hDriver;

	KeInterface(LPCSTR RegistryPath)
	{
		hDriver = CreateFileA(RegistryPath, GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	}

	~KeInterface()
	{
		if (hDriver)
		{
			CloseHandle(hDriver);
		}
	}

	bool ReadVirtualMemory(ULONG ProcessId, PVOID lpBaseAddress, PVOID lpBuffer, SIZE_T nSize)
	{
		if (hDriver == INVALID_HANDLE_VALUE)
		{
			return false;
		}

		DWORD Return, Bytes;
		ULONG nAllocSize = sizeof(KERNEL_READ_REQUEST) + nSize - sizeof(KERNEL_READ_REQUEST::Response);
		PKERNEL_READ_REQUEST pReadRequest = (PKERNEL_READ_REQUEST)malloc(nAllocSize);

		if (!pReadRequest)
		{
			return false;
		}

		pReadRequest->ProcessId = ProcessId;
		pReadRequest->Address = lpBaseAddress;
		pReadRequest->Size = nSize;

		BOOL result = DeviceIoControl(hDriver, IO_READ_REQUEST, pReadRequest, nAllocSize, pReadRequest, nAllocSize, 0, 0);
		printf("%16llx\n", *(PDWORD64)pReadRequest->Response);
		memcpy(lpBuffer, pReadRequest->Response, nSize);
		free(pReadRequest);

		return result;
	}

	bool WriteVirtualMemory(ULONG ProcessId, PVOID lpBaseAddress, PVOID lpBuffer, ULONG nSize)
	{
		if (hDriver == INVALID_HANDLE_VALUE)
		{
			return false;
		}

		DWORD Bytes;
		ULONG nAllocSize = sizeof(KERNEL_WRITE_REQUEST) + nSize - sizeof(KERNEL_WRITE_REQUEST::Value);
		PKERNEL_WRITE_REQUEST  pWriteRequest = (PKERNEL_WRITE_REQUEST)malloc(nAllocSize);

		if (!pWriteRequest)
		{
			return false;
		}

		pWriteRequest->ProcessId = ProcessId;
		pWriteRequest->Address = lpBaseAddress;
		pWriteRequest->Size = nSize;
		memcpy(pWriteRequest->Value, lpBuffer, nSize);

		BOOL result = DeviceIoControl(hDriver, IO_WRITE_REQUEST, pWriteRequest, nAllocSize, 0, 0, &Bytes, NULL);

		free(pWriteRequest);

		return result;
	}
};
