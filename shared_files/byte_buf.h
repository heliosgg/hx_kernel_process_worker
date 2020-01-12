//#ifndef  _BYTE_BUF_H
//#define _BYTE_BUF_H
//
//#ifdef DEF_DRIVER
//#else
//#include <Windows.h>
//#endif
//
//struct _BYTE_BUFFER
//{
//	ULONG uBufSize;
//	ULONG pBuf[1];
//
//	ULONG(*GetFullSize)(struct _BYTE_BUFFER* self);
//};
//
//typedef struct _BYTE_BUFFER BYTE_BUFFER, * PBYTE_BUFFER;
//
//ULONG BYTE_BUFFER_GetFullSize(PBYTE_BUFFER self)
//{
//	if (self)
//	{
//		return sizeof(BYTE_BUFFER) + self->uBufSize;
//	}
//
//	return 0;
//}
//
//
//PBYTE_BUFFER BYTE_BUFFER_new(ULONG buf_size)
//{
//	PBYTE_BUFFER p = NULL;
//
//#ifdef DEF_DRIVER
//	// TODO: implement allocation (this is not necessary now)
//#else
//	p = (PBYTE_BUFFER)malloc(sizeof(BYTE_BUFFER) + buf_size);
//#endif
//
//	if (p)
//	{
//		p->uBufSize = buf_size;
//	}
//
//	return p;
//}
//
//#endif