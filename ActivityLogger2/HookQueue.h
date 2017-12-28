#pragma once
#include "blockingconcurrentqueue.h"
#include "Hook.h"

class HookQueue
{
public:
	static void add(Hook& hook);
	static moodycamel::BlockingConcurrentQueue<Hook>& getQueue();
private:
	inline static moodycamel::BlockingConcurrentQueue<Hook> queue;
	HookQueue() = default;
};
