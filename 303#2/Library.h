#pragma once
#include<string>
#include"list.h"
#include"Book.h"
using namespace std;

class Library {
public:

	//add employee to queue of book already checked out
	void addEmployee(string name,string b);
	//add book to list of archived books
	void addBook(string name);
	void checkout(string name);
	void checkin(string name);

private:
	list<Book> checkedout;
	list<Book> archived;
};