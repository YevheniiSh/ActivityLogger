#include "stdafx.h"
#include <thread>
#include "HookService.cpp"

//void test2()
//{
//	std::future<Hook> future = std::async(std::launch::async, []()
//	{
//		Hook hook;
//		HookQueue::getQueue().wait_dequeue(hook);
//		return hook;
//	});
//
//	std::future_status status;
//	do
//	{
//		status = future.wait_for(std::chrono::seconds(1));
//		if (status == std::future_status::deferred)
//		{
//		}
//		else if (status == std::future_status::timeout)
//		{
//		}
//		else if (status == std::future_status::ready)
//		{
//			//			KBDLLHOOKSTRUCT hooked_key = *reinterpret_cast<KBDLLHOOKSTRUCT*>(future.get().l_param());
//			auto [nCode, wParam, lParam] = future.get();
//			std::cout << static_cast<TCHAR>(wParam);
//		}
//	} while (status != std::future_status::ready);
//}

void test2()
{
	Hook hook;
	while (true)
	{
		HookQueue::getQueue().wait_dequeue(hook);
		const KBDLLHOOKSTRUCT hooked_key = *reinterpret_cast<KBDLLHOOKSTRUCT *>(hook.lParam);
	}
}

int main()
{
	std::thread t(&runActivityLogger);
	std::thread t1(&test2);

	t.join();
	t1.join();

	system("PAUSE");
}
