#pragma once
#include <windows.h>
#include "HookType.h"

struct Hook
{
	int nCode;
	WPARAM wParam;
	LPARAM lParam;
	HookType hookType;
};
