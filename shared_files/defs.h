#pragma once

#ifdef DEF_DRIVER
#else
#include <Windows.h>
#endif

#define DEVICE_NAME		"hx_kernel_process_worker"
#define DEVICE_NAME_W	L"hx_kernel_process_worker"

#define IO_READ_REQUEST       CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0701 /* Our Custom Code */, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define IO_WRITE_REQUEST      CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0702 /* Our Custom Code */, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)


typedef struct _KERNEL_READ_REQUEST
{
	ULONG ProcessId;

	PVOID Address;
	ULONG Size;
	ULONG Response[1];

};
typedef struct _KERNEL_READ_REQUEST KERNEL_READ_REQUEST, * PKERNEL_READ_REQUEST;

struct _KERNEL_WRITE_REQUEST
{
	ULONG ProcessId;

	PVOID Address;
	ULONG Size;
	ULONG Value[1];

};
typedef struct _KERNEL_WRITE_REQUEST KERNEL_WRITE_REQUEST, * PKERNEL_WRITE_REQUEST;