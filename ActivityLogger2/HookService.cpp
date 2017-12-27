#include "stdafx.h"
#include "HookService.h"
#include <windows.h>

HHOOK hKeyboardHook;
HHOOK hMouseHook;

LRESULT WINAPI keyLogger(int nCode, WPARAM wParam, LPARAM lParam)
{
	if ((nCode == HC_ACTION) && ((wParam == WM_SYSKEYDOWN) || (wParam == WM_KEYDOWN)))
	{
		Hook hook{ nCode, wParam, lParam, Keyboard};
		HookQueue::static_add(hook);
		//		KBDLLHOOKSTRUCT hooked_key = *((KBDLLHOOKSTRUCT *)lParam);
	}
	return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}

LRESULT WINAPI mouseLogger(int nCode, WPARAM wParam, LPARAM lParam)
{
	Hook hook{nCode, wParam, lParam, Mouse};

	switch (wParam)
	{
	case WM_LBUTTONDOWN:
		HookQueue::static_add(hook);
		break;

	case WM_RBUTTONDOWN:
		HookQueue::static_add(hook);
		break;

	case WM_MOUSEWHEEL:
		HookQueue::static_add(hook);
		break;
	}

	return CallNextHookEx(hMouseHook, nCode, wParam, lParam);
}

void msgLoop()
{
	MSG message;
	while (GetMessage(&message, nullptr, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

void WINAPI runActivityLogger()
{
	const HINSTANCE hins = GetModuleHandle(nullptr);
	hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, HOOKPROC(keyLogger), hins, 0);
	hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, HOOKPROC(mouseLogger), hins, 0);

	msgLoop();

	UnhookWindowsHookEx(hKeyboardHook);
	UnhookWindowsHookEx(hMouseHook);
}
