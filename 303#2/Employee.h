#pragma once
#include <string>
class Employee
{
public:
	//Constructors
	Employee() { name = ""; wait_time = 0; retain_time = 0; }
	Employee(string n,int retain) { name = n; retain_time = retain; wait_time = 0; }
	//getters
	string getName() { return name; }
	int getWaitTime() { return wait_time; }
	int getRetainTime() { return retain_time; }
	//setters
	void setName(string s) { name = s; }
	void setWaitTime(int w) { wait_time = w; }
	void setRetainTime(int r) { retain_time = r; }
private:
	string name; //name of employee
	int wait_time; //amount of days waiting for book
	int retain_time; //number of days with book checked out
};