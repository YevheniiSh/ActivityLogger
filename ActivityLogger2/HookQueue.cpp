#include "stdafx.h"

moodycamel::BlockingConcurrentQueue<Hook> staticQueue;

void HookQueue::add(Hook& hook)
{
	queue.enqueue(hook);
	//	boost::thread* thr = new boost::thread(boost::bind(&HookQueue::test, this));
	//	thr->join();
}

void HookQueue::static_add(Hook& hook)
{
	staticQueue.enqueue(std::move(hook));
}

//void HookQueue::

moodycamel::BlockingConcurrentQueue<Hook>& HookQueue::getQueue()
{
	return staticQueue;
}