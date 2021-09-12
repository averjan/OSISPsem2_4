#pragma once

#include <Windows.h>
#include <vector>

#include "TaskQueue.h"

class ThreadProcessor
{
private:
	TaskQueue *tqueue;
	static DWORD WINAPI ProcessTask(void* vqueue);
public:
	ThreadProcessor(TaskQueue *queue);
	void ExecuteQueue(int threadCount);
};

