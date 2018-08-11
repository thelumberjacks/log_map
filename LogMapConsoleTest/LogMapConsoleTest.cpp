// LogMapConsoleTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../LogMapCore/LogMapCore.h"


int _tmain(int argc, _TCHAR* argv[])
{
	LogMapCore::Reader r;
	r.AddLog(L"..\\log\\test1.log");
	r.AddLog(L"..\\log\\test2.log");
	r.AddRegex(L"");
	r.ScanAll();

	return 0;
}

