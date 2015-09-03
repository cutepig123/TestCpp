// testVMSz.cpp : Defines the entry point for the console application.
//
// Psapi.lib
#include "stdafx.h"
#include "windows.h"
#include "Psapi.h"

int _tmain(int argc, _TCHAR* argv[])
{
	while(1)
	{
		PROCESS_MEMORY_COUNTERS_EX pmcx = {};
		pmcx.cb = sizeof(pmcx);
		GetProcessMemoryInfo(GetCurrentProcess(),
			reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&pmcx), pmcx.cb);

		printf("\r%d bytes, %d k",pmcx.PrivateUsage, (int)(pmcx.PrivateUsage/1024));
		Sleep(1000);
	}
	return 0;
}

