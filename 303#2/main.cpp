#include<iostream>
#include<string>
#include "list.h"
#include <queue>
#include"Date.h"
#include"Book.h"
#include"Employee.h"
#include"StringTokenizer.h"
#include "omp.h"
using namespace std;

//moves book from archived to checkedout
void checkout(Book book, list<Book> &archived, list<Book> &out);
//no employees want the book anymore, return it to the archived list
void checkin(string name, list<Book> &archived, list<Book> &out);
//add book to list of archived books
void addBook(string name, list<Book> &archived, Date date);
//Adds an employee to the books Queue, if first person in queue the employee has the book
void addEmployee(string name, string desire,int retain, list<Book> &archived, list<Book> &out);

void main()
{
	//Creating the number of threads
	omp_set_num_threads(3);
	//Creating two lists for books
	list<Book> archived;
	list<Book> out;
	//Adding four books to the library
	addBook("Hitchhikers Guide", archived, Date(2017, 3, 20));
	addBook("Harry Potter", archived, Date(2017,3,21));
	addBook("Of Mice and Men", archived, Date(2017,3,22));
	addBook("Potato Famine", archived,Date(2017,3,23));
	//Dylan checking out Harry Potter
	addEmployee("Dylan", "Harry Potter",6, archived, out);
	//Gabby getting in line for Harry Potter
	addEmployee("Gabby", "Harry Potter",7, archived, out);
	//Matt checking out the book from the library
	addEmployee("Matt", "Harry Potter", 22, archived, out);
	//Dylan Passing the book on to Gabby
	checkin("Harry Potter", archived, out);
	//Gabby checking in the book to the library
	checkin("Harry Potter", archived, out);

}

//moves book from archived to checkedout
void checkout(Book book, list<Book> &archived, list<Book> &out)
{
#pragma omp parallel
	//Iterator going through the archived list
	for (list<Book>::iterator it = archived.begin(); it != archived.end(); it++)
	{
	#pragma omp critical
		{
			//If the iterator is pointing to the book we desire
		if (it->getName() == book.getName())
			{
			//The book is added to the out list and removed from the archived list
				out.push_back(*it);
				archived.erase(it);
				return;
			}
		}
	}
}

//no employees want the book anymore, return it to the archived list or passing the book onto the next person
void checkin(string name, list<Book> &archived, list<Book> &out)
{
	#pragma omp parallel
	//Iterator going from the begining to the end of the out list
	for (list<Book>::iterator itr = out.begin(); itr != out.end(); itr++)
	{
		#pragma omp critical
		{
			//If the iterator is pointing to the book desired
			if (itr->getName() == name)
			{
				//If the queue only has one person in it, thus the book is being archived
				if (itr->employees.front().getName() == itr->employees.back().getName())
				{
					itr->employees.pop();
					//Adding the book to archived and deleting it from the out list
					archived.push_back(*itr);
					out.erase(itr);
					return;
				}
				//More than one person in the queue
				else
				{
					//Holder is a sumation of the first person in the queue's wait and retain time
					int holder = itr->employees.front().getRetainTime() + itr->employees.front().getWaitTime();
					//Removing the first person in the queue (Passing on the book)
					itr->employees.pop();
					//Updating the new book holders wait time based on their predecessor
					itr->employees.front().setWaitTime(holder);
					//Updating the predicted circulation end date
					Date date = itr->getCirculationStartDate();
					//Adding the number of days equal to the retain time + the wait time
					date.add_days(itr->employees.front().getRetainTime() + itr->employees.front().getWaitTime());
					itr->setCirculationEndDate(date);
				}
			}
		}
	}
}

//add book to list of archived books
void addBook(string name, list<Book> &archived,Date date)
{
	archived.push_back(Book(name,date));
}

//Adding an employee to the waiting list for a book
void addEmployee(string name, string desire, int retain, list<Book> &archived, list<Book> &out)
{
	#pragma omp parallel
		//Iterator going through the archived list
	for (list<Book>::iterator it = archived.begin(); it != archived.end(); it++)
	{
#pragma omp critical
		{
			//If the desired book is at the point of the iterator
			if (desire == it->getName())
			{
				//creating an employee and placing it in the queue for the book
				it->employees.push(Employee(name, retain));
				Date date = it->getCirculationStartDate();
				date.add_days(retain);
				it->setCirculationEndDate(date);
				//Checks out the book from archived to the out list
				it->setArchived(false);
				checkout(*it, archived, out);
				//Exits the loop
				return;
			}
			if (out.size() != 0)
			{
				//Iterator looking through the out list
				for (list<Book>::iterator itr = out.begin(); itr != out.end(); itr++)
				{
					//If the desired book is at the iterator
					if (desire == itr->getName())
					{
						//Creates an employee and places it in the books queue
						itr->employees.push(Employee(name, retain));
						//Exits loop

						return;
					}
				}
			}
		}
	}
}