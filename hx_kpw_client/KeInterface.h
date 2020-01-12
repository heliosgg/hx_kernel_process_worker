#pragma once

#include <Windows.h>
#include <defs.h>
#include <byte_buf.h>


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

	template <typename type>
	type ReadVirtualMemory(ULONG ProcessId, DWORD64 ReadAddress,
		SIZE_T Size)
	{
		if (hDriver == INVALID_HANDLE_VALUE)
			return (type)false;

		DWORD Return, Bytes;
		KERNEL_READ_REQUEST ReadRequest;

		ReadRequest.ProcessId = ProcessId;
		ReadRequest.Address = ReadAddress;
		ReadRequest.Size = Size;

		// send code to our driver with the arguments
		if (DeviceIoControl(hDriver, IO_READ_REQUEST, &ReadRequest,
			sizeof(ReadRequest), &ReadRequest, sizeof(ReadRequest), 0, 0))
			return (type)ReadRequest.Response;
		else
			return (type)false;
	}

	bool WriteVirtualMemory(ULONG ProcessId, DWORD64 WriteAddress,
		PVOID Buffer, ULONG nSize)
	{
		if (hDriver == INVALID_HANDLE_VALUE)
			return false;
		DWORD Bytes;

		ULONG nAllocSize = sizeof(KERNEL_WRITE_REQUEST) + nSize - sizeof(KERNEL_WRITE_REQUEST::Value);

		PKERNEL_WRITE_REQUEST  WriteRequest = (PKERNEL_WRITE_REQUEST)malloc(nAllocSize);
		if (!WriteRequest)
		{
			return false;
		}

		WriteRequest->ProcessId = ProcessId;
		WriteRequest->Address = WriteAddress;
		WriteRequest->Size = nSize;
		memcpy(WriteRequest->Value, Buffer, nSize);

		if (DeviceIoControl(hDriver, IO_WRITE_REQUEST, WriteRequest, nAllocSize,
			0, 0, &Bytes, NULL))
			return true;
		else
			return false;
	}
};
