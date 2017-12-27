#pragma once
#include <windows.h>

struct Hook
{
	int nCode;
	WPARAM wParam;
	LPARAM lParam;
};
