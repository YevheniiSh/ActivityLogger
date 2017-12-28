#include "stdafx.h"
#include "HookService.h"
#include <windows.h>

HHOOK hKeyboardHook;
HHOOK hMouseHook;

LRESULT WINAPI keyLogger(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0) return CallNextHookEx(hMouseHook, nCode, wParam, lParam);

	if (wParam == WM_KEYUP)
	{
		Hook hook{nCode, wParam, lParam, Keyboard};
		HookQueue::add(hook);
	}
	return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}

LRESULT WINAPI mouseLogger(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0) return CallNextHookEx(hMouseHook, nCode, wParam, lParam);

	if ((wParam == WM_LBUTTONUP || wParam == WM_LBUTTONDOWN) && GetAsyncKeyState(VK_CONTROL) & 0x8000)
	{
		Hook hook{nCode, wParam, lParam, Activate};
		HookQueue::add(hook);
		return CallNextHookEx(hMouseHook, nCode, wParam, lParam);
	}

	Hook hook{nCode, wParam, lParam, Mouse};
	switch (wParam)
	{
	case WM_LBUTTONDOWN:
		HookQueue::add(hook);
		break;

	case WM_RBUTTONDOWN:
		HookQueue::add(hook);
		break;

	case WM_MOUSEWHEEL:
		HookQueue::add(hook);
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

void WINAPI runKeyLogger()
{
	const HINSTANCE hins = GetModuleHandle(nullptr);
	hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, HOOKPROC(keyLogger), hins, 0);
	msgLoop();
	UnhookWindowsHookEx(hKeyboardHook);
}

void WINAPI runMouseLogger()
{
	const HINSTANCE hins = GetModuleHandle(nullptr);
	hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, HOOKPROC(mouseLogger), hins, 0);
	msgLoop();
	UnhookWindowsHookEx(hMouseHook);
}
