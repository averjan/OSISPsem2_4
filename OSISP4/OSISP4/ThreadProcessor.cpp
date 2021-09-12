#include "ThreadProcessor.h"
#include <thread>
#include <vector>

ThreadProcessor::ThreadProcessor(TaskQueue *queue)
{
	this->tqueue = queue;
}

std::vector<void*> ThreadProcessor::ExecuteQueue(int threadCount)
{
	std::vector<void*> resultParams;
	std::vector<std::thread> threads;
	TaskQueue removeTasks;
	while (threadCount)
	{
		Task* task = this->tqueue->Dequeue();
		if (task != nullptr)
		{
			//std::thread t(task->func, task->params);
			//threads.push_back(move(t));
			task->func(task->params);
			removeTasks.Enqueue(task);
		}

		threadCount--;
	}

	/*
	for (auto &t : threads)
	{
		t.join();
	}
	*/
	while (!removeTasks.Empty())
	{
		Task* task = removeTasks.Dequeue();
		resultParams.push_back(task->params);
		delete(task);
	}

	return resultParams;
}