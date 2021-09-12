#include <Windows.h>
#include "TaskQueue.h"

#define SPINS 0x00000400

TaskQueue::TaskQueue()
{
	InitializeCriticalSectionAndSpinCount(&(this->lock), SPINS);
	this->first = NULL;
	this->last = NULL;
}

void TaskQueue::Enqueue(Task* task)
{
	EnterCriticalSection(&lock);
	Node* qnode = new Node();
	qnode->data = task;
	qnode->next = nullptr;
	qnode->prev = nullptr;
	if (this->Empty())
	{
		this->first = qnode;
		this->last = qnode;
	}
	else
	{
		this->last->next = qnode;
		qnode->prev = this->last;
		this->last = qnode;
	}

	LeaveCriticalSection(&lock);
}

Task* TaskQueue::Dequeue()
{
	if (this->Empty())
	{
		return nullptr;
	}

	Node* pop = this->first;
	this->first = this->first->next;
	if (this->first == nullptr)
	{
		this->last = nullptr;
	}
	else
	{
		this->first->prev = nullptr;
	}

	Task* task = pop->data;
	delete pop;
	return task;
}

bool TaskQueue::Empty()
{
	return (this->first == nullptr);
}

TaskQueue::~TaskQueue()
{
	while (!this->Empty())
	{
		this->Dequeue();
	}

	DeleteCriticalSection(&(this->lock));
}