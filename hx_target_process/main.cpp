#include <string.h>
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

using namespace std;

void PrintBytesHex(BYTE* arr, UINT size);

int main(int argc, char* argv[])
{
   BYTE a[30];

   for (UINT i = 0; i < sizeof(a); i++)
   {
      a[i] = (BYTE)i;
   }

   printf("Pid: %8x\n", GetCurrentProcessId());
   printf("Address of \"a\" is 0x%llx\n", (DWORD64)a);

   while (true)
   {
      printf("Value of \"a\" is ");
      PrintBytesHex(a, sizeof(a));
      printf("\n");

      Sleep(1000);
   }
   
   return 0;
}

void PrintBytesHex(BYTE* arr, UINT size)
{
   for (UINT i = 0; i < size; i++)
   {
      printf("%02x ", arr[i]);
   }
}