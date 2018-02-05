#pragma once
#include<string>
#include"Date.h"
#include "Employee.h"
#include <queue>
class Book:public Employee {
public:
	//Constructor
	Book() { name = ""; }
	Book(string n) { name = n; }
	Book(string n, Date start) { name = n; circulation_start_date = start; }
	//getters
	string getName() { return name; }
	Date getCirculationStartDate() { return circulation_start_date; }
	Date getCirculationEndDate() { return circulation_end_date; }
	//setters
	void setName(string s) { name = s; }
	void setCirculationStartDate(Date d) { circulation_start_date = d; }
	void setCirculationEndDate(Date d) { circulation_end_date = d; }
	void setArchived(bool b) { archived = b; }
	//Functions
	bool is_archived() { return archived; }
	void nextPerson() { employees.pop(); }
	queue<Employee> employees; //queue of employees that want to check out the book

private:
	string name; //name of the book
	Date circulation_start_date; //date circulation began
	Date circulation_end_date; //date circulation ends
	bool archived; //is the book in the archived list or the other list?
	
};