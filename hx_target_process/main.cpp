#include <string.h>
#include <stdio.h>
#include <iostream>
#include <Windows.h>

using namespace std;

int main(int argc, char* argv[])
{
   DWORD a = 0xaabbccdd;

   printf("Pid: %08x\n", GetCurrentProcessId());
   printf("Address of \"a\" is %016llx\n", (DWORD64)&a);

   while (true)
   {
      printf("Value of \"a\" is %08x\n", a);
      Sleep(1000);
   }

   return 0;
}