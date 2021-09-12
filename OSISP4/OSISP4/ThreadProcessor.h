#pragma once

#include <Windows.h>
#include <vector>

#include "TaskQueue.h"

class ThreadProcessor
{
private:
	TaskQueue *tqueue;

public:
	ThreadProcessor(TaskQueue *queue);
	std::vector<void*> ExecuteQueue(int threadCount);
};

