#include "stdafx.h"

void HookQueue::add(Hook& hook)
{
	queue.enqueue(std::move(hook));
}

moodycamel::BlockingConcurrentQueue<Hook>& HookQueue::getQueue()
{
	return queue;
}
