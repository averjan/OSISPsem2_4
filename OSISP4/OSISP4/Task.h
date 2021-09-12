#pragma once
class Task
{
public:
	void* params;
	void (*func)(void*);

	Task(void(*func)(void*), void* params);
};

