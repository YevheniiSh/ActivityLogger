#include "stdafx.h"
#include <thread>
#include "HookService.h"
#include <iostream>

void test2()
{
	Hook hook;
	while (true)
	{
		HookQueue::getQueue().wait_dequeue(hook);
//	const KBDLLHOOKSTRUCT hooked_key = *reinterpret_cast<KBDLLHOOKSTRUCT *>(hook.lParam);
		switch (hook.hookType)
		{
		case Mouse:
			std::cout << "mouse\n";
			break;
		case Keyboard:
			std::cout << "keyboard\n";
			break;
		case Activate:
			std::cout << "Activate\n";
			break;
		}
	}
}

int main()
{
	std::thread keyLogger(&runKeyLogger);
	std::thread mouseLogger(&runMouseLogger);
	std::thread t1(&test2);
	keyLogger.join();
	mouseLogger.join();
	t1.join();
	system("PAUSE");
}