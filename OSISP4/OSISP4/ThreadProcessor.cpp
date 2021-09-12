#include "ThreadProcessor.h"
#include <thread>
#include <vector>

ThreadProcessor::ThreadProcessor(TaskQueue *queue)
{
	this->tqueue = queue;
}

void ThreadProcessor::ExecuteQueue(int threadCount)
{
	HANDLE* threads = (HANDLE*)malloc(sizeof(HANDLE) * threadCount);
	TaskQueue removeTasks;
	for (int i = 0; i < threadCount; i++)
	{
		HANDLE t = CreateThread(NULL, 0, &ThreadProcessor::ProcessTask, (LPVOID)(this->tqueue), CREATE_SUSPENDED, NULL);
		threads[i] = t;
	}

	for (int i = 0; i < threadCount; i++)
	{
		ResumeThread(threads[i]);
	}
	
	WaitForMultipleObjects(threadCount, threads, TRUE, INFINITE);
}

DWORD WINAPI ThreadProcessor::ProcessTask(void* vqueue)
{
	TaskQueue* queue = (TaskQueue*)vqueue;
	if (!queue->Empty())
	{
		Task* task = queue->Dequeue();
		task->func(task->params);
	}

	return 0;
}