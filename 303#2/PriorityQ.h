#pragma once

#include <vector>
#include <list>
#include <iostream>
#include "Employee.h"


using namespace std;

class PQ 
{
private:
	vector <Employee*> Queue;

public:
	PQ();
	void addEmployee(Employee* name);
	Employee* pop();
	Employee* top();
	bool empty();
};