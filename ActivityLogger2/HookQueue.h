#pragma once
#include "blockingconcurrentqueue.h"
#include "Hook.h"

class HookQueue
{
public:
	void add(Hook& hook);
	static void static_add(Hook& hook);
	static moodycamel::BlockingConcurrentQueue<Hook>& getQueue();
private:
	moodycamel::BlockingConcurrentQueue<Hook> queue;
	HookQueue() = default;
};
