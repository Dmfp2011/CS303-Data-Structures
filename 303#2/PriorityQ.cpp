#include "PriorityQ.h"

PQ::PQ()
{

}

void PQ::addEmployee(Employee * name)
{
	Queue.push_back(name);
}

Employee * PQ::pop()
{
	Employee *name = *Queue.begin();
	vector<Employee*>::iterator it, deleter;
	it = deleter = Queue.begin();
	it++;
	for (it; it != Queue.end(); it++) {
		if ((name->getWaitTime() - name->getRetainTime()) < ((*it)->getWaitTime() - (*it)->getRetainTime()))
		{
			name = *it;
			deleter = it;
		}
	}
	Queue.erase(deleter);
	return name;
}

Employee * PQ::top()
{
	Employee *name = *Queue.begin();
	for (vector<Employee*>::iterator it = Queue.begin(); it != Queue.end(); it++)
	{
		if ((name->getWaitTime() - name->getRetainTime()) < ((*it)->getWaitTime() - (*it)->getRetainTime()))
		{
			name = *it;
		}
	}
	return name;
}

bool PQ::empty()
{
	return Queue.size() < 1;
}
