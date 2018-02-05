#pragma once
#include <iostream>
#include <string>
using namespace std;


class Term
{
//Private variables for the sign, coefficient, variable, exponent, and expression
private:
	int coef = NULL;
	int expo = NULL;
	string sub_expression;
	string varcar;

public:
	//Default constructor
	Term() { sub_expression = ""; }
	//Constructor
	Term(string s) { sub_expression = s; }
	//Getter and setters
	string GetExpression() { return sub_expression; }
	int getexp() { return expo; }
	int getcoef() { return coef; }
	string GetVarcar() { return varcar; }
	void SetVarcar(string g) { varcar = g; }
	void SetCoef(int c) { coef = c; }
	void SetExpo(int d) { expo = d; }
	void SetExpression(string s) { sub_expression = s; }
	int length() {return sub_expression.length(); }
	//Template function to convert a string to either a character or an integer
	void converter();
	//Prints out the term
	void print();
	//Overloaded comparison operators
	int operator>(Term t2);
};