#pragma once
#include <Windows.h>
#include "Task.h"

class Node
{
public:
	Task* data;
	Node* next;
	Node* prev;
};

class TaskQueue
{
private:
	CRITICAL_SECTION lock;
	Node *first,  *last;
public:
	TaskQueue();
	void Enqueue(Task* task);
	Task* Dequeue();
	bool Empty();
	~TaskQueue();
};

