#pragma once
#include <iostream>
#include <string>
#include "term.h"
using namespace std;

void Term::converter() //converts string to ints
{
	//variables for the coefficient, exponent, and whether or not the term has a variable
	string coefkeeper = "";
	string expkeeper = "";
	string varcar="";
	//For loop that goes to the end of the sub expression
	for (int i = 0; i < sub_expression.length(); i++)
	{
		//Automatically adds the first index to the coefficient variable
		if (i == 0)
			coefkeeper += sub_expression[i];
		//if the index before the one at i is a carrot (to the power of)...
		else if (sub_expression[i - 1] == '^')
		{
			//Adding each didgit for the exponent, while the pointer is not at NULL
			while (sub_expression[i] != NULL)
			{
				expkeeper += sub_expression[i];
				++i;
			}
			//Breaks the loop, we are at the end of the term anyways
			break;
	}
		//If the expression at i is not an upper or lowercase X, not a negative. not a positive, and not a carrot
		else if (sub_expression[i] != 'x' && sub_expression[i] != 'X'
			&& sub_expression[i] != '-' && sub_expression[i] != '+' && sub_expression[i] != '^')
		{
			//Add the expression at i to the coefficient
			coefkeeper += sub_expression[i];
		}
		//If the expression at i is a variable, load varcar with an x and if theres a carrot(else statement)
		else if (sub_expression[i] == 'x' || sub_expression[i] == 'X')
			if (sub_expression[i + 1] == '^')
			{
				varcar = sub_expression[i];
				varcar += sub_expression[i + 1];
			}
			else
				varcar = sub_expression[i];
	}
	//If the variable has no coefficient, but is negative, makes the coefficient a negative 1 and set it
	if (coefkeeper == "-")
	{
		coefkeeper += '1';
		SetCoef(atoi(coefkeeper.c_str()));
	}
	//If the variable has no coefficient, but is positive, default a '1' to the begining of the x, and set coefficient
	else if (coefkeeper == "+")
	{
		coefkeeper = '1';
		SetCoef(atoi(coefkeeper.c_str()));
	}
	//If the variable has a coefficient
	else
		SetCoef(atoi(coefkeeper.c_str()));
	
	//Set each of the variables we just loaded up
	SetExpo(atoi(expkeeper.c_str()));
	SetVarcar(varcar);
}


void Term::print() //prints term to screen for user
{
	cout << getcoef() << GetVarcar() << getexp();
}

int Term::operator>(Term t2) //compares exponents so we can sort the list
{
	//if the lhs exponent is greater than the rhs exponent, return zero
	if (getexp() > t2.getexp())
		return 0;
	//If both exponents are equal, return 1
	else if (getexp() == t2.getexp())
		return 1;
	//If lhs exponent is less than rhs exponent, return 2
	else
		return 2;
}