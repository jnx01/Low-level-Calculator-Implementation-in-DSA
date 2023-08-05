#pragma once
#include <iostream>

//stack implementation left out

using namespace std;

class Calculator
{
public:
	void infixToFile(string exp);
	void postfixToFile(string exp);
	bool infixValidity();
	int precedence(char a, char b);
	void infixToPostfix();
	void evaluatePostfix();
};
