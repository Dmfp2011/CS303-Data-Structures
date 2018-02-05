#include <iostream>
#include <string>
#include "term.h"
#include "list.h"
using namespace std;

//A function to print out each of the variables in the list
void printer(list<Term> li);
//A bubble sort function to make the list ordered
void sort(list<Term> &li);
//Function asking the user to enter the first polynomial
string main_menu();
//Function asking the user to enter the second polynomial
string main_menu2();
//Function to seperate the expression into individual terms
string seperate(string express);
//Function to simplify like terms in an Ordered List
void simplify(list<Term> &li);

//The linked list we are loading up with all the terms
list<Term> polnom;
//Variables to be loaded up in the program
string poly, poly2, expression1, expression2 = "";
Term terms;

void main()
{
	//Loads up variable expression with the user input from main menu
	expression1 = main_menu();
	expression2 = main_menu2();
	//If the first character of the expression is NOT a minus sign, it adds an addition sign to the beginning of the term
	if (expression1[0] != '-')
	{
		expression1 = "+" + expression1;
	}
	//terms is loaded with the seperated expression (the term)
	terms = seperate(expression1);
	//The expression erases from index zero until the length of the term (deleting the term from the expression)
	expression1.erase(0, terms.length());
	//Converting the expression's coefficients into numbers and loading up the coef and expo variables
	//Then adding that term to the linked list
	terms.converter();
	polnom.push_back(terms);


	//While the expression has stuff in it
	while (!expression1.empty())
	{
		//terms is loaded with the seperated expression (the term)
		terms = seperate(expression1);
		//The expression erases from index zero until the length of the term (deleting the term from the expression)
		expression1.erase(0,terms.length());
		//Converting the expression's coefficients into numbers and loading up the coef and expo variables
		terms.converter();
		//Adding the new node to the end of the linked list and incrementing the current to point to that node
		polnom.push_back(terms);
	}

	//Adding expression 2 to the previously created linked list
	while (!expression2.empty())
	{
		//terms at index i is loaded with the seperated expression (the term)
		terms = seperate(expression2);
		//The expression erases from index zero until the length of the term (deleting the term from the expression)
		expression2.erase(0, terms.length());
		//Converting the expression's coefficients into numbers and loading up the coef and expo variables
		terms.converter();
		//Adding the new node to the end of the linked list and incrementing the current to point to that node
		polnom.push_back(terms);
	}
	//Sorting the polynomial
	sort(polnom);
	//Simplifying like terms
	simplify(polnom);
	//Printing out the entire polynomial
	printer(polnom);
};

//Prints out each node by calling a class function of print
void printer(list<Term> li)
{
	cout << endl << "Your new polynomial is: \n";
	//Sets an iterator at the begining of the list and goes until it reaches the end
	for (list<Term>::iterator it = li.begin(); it != li.end(); it++)
	{
		//If the term isnt blank
		if (it->getcoef() != 0 || it->getexp() != 0)
		{
			//If the iterator is the first node, print out the variables as normal
			if (it == li.begin())
			{
				//If the first thing printed has no exponent, print out just the coefficient and the variable
				if (it->getexp() == 0)
				{
					cout << it->getcoef() << it->GetVarcar();
				}
				//Otherwise print out the whole term
				else
					cout << it->getcoef() << it->GetVarcar() << it->getexp();
			}
			//If the iterator is not the first node
			else
			{
				//If the term is at exponent 1 (ex:8x) and is positive
				if (it->getexp() == 0 && it->getcoef() > 0)
				{
					cout << "+" << it->getcoef() << it->GetVarcar();
				}
				//If the term is at exponent 1 (ex:-8x) and is negitive
				else if (it->getexp() == 0 && it->getcoef() > !0)
				{
					cout << it->getcoef() << it->GetVarcar();
				}
				//If the coefficient is positive, print out but with a '+' symbol up front
				else if (it->getcoef() > 0)
				{
					cout << "+" << it->getcoef() << it->GetVarcar() << it->getexp();
				}
				//If the coefficient is not positive, print out as normal
				else
					cout << it->getcoef() << it->GetVarcar() << it->getexp();
			}
		}
	}

	cout << "\nPress enter";
	system("Pause");

}

void sort(list<Term> &li)//Bubble sort
{
	//variable for if there was and changes in the list
	bool exchanges = false;
	//Iterator set to the first node of the list
	list<Term>::iterator& itr = li.begin();
	//For loop that goes to the end of the list
	for (int i = 1; i <= li.size(); i++)
	{
		exchanges = false;
		//Sets a second iterator for the begining of the list as well
		itr = li.begin();
		for (int j = 0; j < li.size()-1; j++)
		{
			//Sets an iterator that equals wherever the itr is at
			list<Term>::iterator current = itr;
			//Increments the irt and compares it to the current (so the current and the current->next)
			if ((++itr)->getexp()>current->getexp())
			{
				//Swaps the nodes if needed and sets exchanges to true
				swap(*current, *itr);
				exchanges = true;
			}
		}
		//If there was no exchanges, break the loop. theres no need to continue
		if (!exchanges)
			break;
	}
};

string main_menu()//Function to get the first polynomial to be worked with
{
	cout << "Enter your first polynomial (with the '^' symbol used to signify the following number is an exponent)\n";
	cout << "For example: -4x^-23" << endl;
	cin >> poly;
	return poly;
};
string main_menu2()//Function to get the second polynomial to be worked with
{
	cout << "Enter the second polynomial to be added to the first (With the '^' symbol being used again)";
	cout << "For example: 3x^2" << endl;
	cin >> poly2;
	return poly2;
}

//Seperating the user inputed string into seperate terms (still in string form)
string seperate(string express)
{
	//Variable for the return (aka the term)
	string keeper = "";
	//If the first thing in the "term" is a negative sign, its added to keeper
	if (express[0] == '-')
	{
		keeper = '-';
	}
	//If the first entered term has no coeffieient
	else if(express[0] == 'x' || express[0] == 'X')
	{
		keeper += '1';
		keeper += 'x';
	}
	//If the first term is not a negative, the first term (presumed a number) is added to keeper
	else
		keeper += express[0];
	//For loop that goes from the first index until the end of the length of the string
	for (int i = 1; i < express.length(); i++)
	{
		//If the character at index is not addition AND not subtraction AND the character before is NOT a carrot, add to keeper
		if (express[i] != '+' && express[i] != '-'&& express[i - 1] != '^')
		{
			keeper += express[i];
		}
		//If the character at index is not addition AND not subtraction AND the character before IS a carrot, add to keeper
		else if (express[i] != '+' && express[i] != '-'&& express[i - 1] == '^')
		{
			keeper += express[i];
		}
		//If the exponent is negative
		else if (express[i] == '-' && express[i - 1] == '^')
		{
			keeper += express[i];
		}
		//If the character at index is a plus sign OR subtraction OR the one before is a carrot, break the for loop
		else if (express[i] == '+' || express[i] == '-'|| express[i - 1] == '^')
		{
			break;
		}
		//If youre adding a double didget number to keeper
		else if (express[i + 1] != NULL)
		{
			keeper += express[i];
		}
	}
	//Return the keeper
	return keeper;
}

//Takes the sorted linked list (with both polynomiels) and simplifies like terms (if the exponent is equal)
void simplify(list<Term> &li)
{
	//Sets an iterator at the begining of the list
	list<Term>::iterator it = li.begin();
	//Sets a variables to the size of the list (because the size of the list is changing)
	int num_of_items = li.size();
	//For loop that will go to the number of items -1
	for (int i = 0; i < num_of_items-1;i++)
	{
		//Sets an iterator to the position of the curent iterator
		list<Term>::iterator current = it;
		//Increments the first iterator and checks if the exponents are equal (like terms)
		if ((++it)->getexp() == current->getexp() && it->GetVarcar() == current->GetVarcar())
		{
			//Dummy variable that will get loaded up with the previously mentioned two's coeffieients, and sets that new number
			//as the second nodes coeffieient and deletes the first node.
			int dummy = (it)->getcoef() + current->getcoef();
			it->SetCoef(dummy);
			li.erase(current);
		}
	}
}
