#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Node.h"
#include "Stack.h"
#include "intNode.h"
#include "intStack.h"
#include "Calculator.h"
//stack implementation left out


using namespace std;

string infix = "infix.txt";
string postfix = "postfix.txt";

void Calculator::infixToFile(string exp)
{
	ofstream out(::infix, ios::trunc);					//trunc mode because we want to ensure there's only one expression in file at all times

	if (!out)
	{
		cout << "\nError opening file.";
		exit(1);
	}
	else
	{
		out << exp;
		out.close();
	}
}

void Calculator::postfixToFile(string exp)
{
	ofstream out(::postfix, ios::trunc);					//trunc mode because we want to ensure there's only one expression in file at all times

	if (!out)
	{
		cout << "\nError opening file.";
		exit(1);
	}
	else
	{
		out << exp;
		out.close();
	}
}

bool Calculator::infixValidity()
{
	string exp;
	Stack temp;
	char oprtr;

	ifstream in(::infix, ios::in);					//reading infix expression from file

	if (!in)
	{
		cout << "\nError opening file.";
		exit(1);
	}
	else
	{
		getline(in, exp);
		in.close();
	}

	for (int i = 0; i < exp.length(); ++i)
	{
		if (exp[i] == '(')							//if character is opening bracket, push it
		{
			temp.push(exp[i]);
		}
		else if (exp[i] == ')')							//if character is closing bracket...
		{
			if (temp.emptyStack())					//if stack is empty, expression is imbalanced
			{
				return false;
			}
			else									//if stack isnt empty, pop an opening bracket
			{
				oprtr = temp.pop();
			}
		}
	}

	if (temp.emptyStack())					//if stack is empty, expression is balanced
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Calculator::precedence(char a, char b)
{
	char one = a;
	char two = b;
	int onesPrec, twosPrec;

	if (one == '(' || one == ')')			//setting first character's precedence
	{
		onesPrec = 5;
	}
	else if (one == '^')
	{
		onesPrec = 4;
	}
	else if (one == '%')
	{
		onesPrec = 3;
	}
	else if (one == '/' || one == '*')
	{
		onesPrec = 2;
	}
	else if (one == '+' || one == '-')
	{
		onesPrec = 1;
	}
	else
	{
		onesPrec = 0;
	}


	if (two == '(' || two == ')')			//setting second character's precedence
	{
		twosPrec = 5;
	}
	else if (two == '^')
	{
		twosPrec = 4;
	}
	else if (two == '%')
	{
		twosPrec = 3;
	}
	else if (two == '*' || two == '/')
	{
		twosPrec = 2;
	}
	else if(two == '+' || two == '-')
	{
		twosPrec = 1;
	}
	else
	{
		twosPrec = 0;
	}


	if (onesPrec == twosPrec)						//comparing precedence
	{
		return 0;
	}
	else if (onesPrec > twosPrec)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

void Calculator::infixToPostfix()
{
	string exp, postfixExp;
	Stack temp;

	ifstream in(::infix, ios::in);										//read infix expression from file

	if (!in)
	{
		cout << "\nError opening file.";
		exit(1);
	}
	else
	{
		getline(in, exp);
		in.close();
	}

	for (int i = 0; i < exp.length(); ++i)
	{
		if (exp[i] >= '0' && exp[i] <= '9')								//if the character is a digit
		{
			postfixExp += exp[i];
		}
		else if (exp[i] == '(')											//if the character is an opening bracket
		{
			temp.push(exp[i]);
		}
		else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' || exp[i] == '%' || exp[i] == '^')				//if the character is an operator
		{
			int check = precedence(exp[i], temp.retTop());

			if (check == 1 || temp.emptyStack() || temp.retTop() == '(')			//if character has higher precedence than top, or if the stack is empty or if the character is an opening bracket
			{
				temp.push(exp[i]);
			}
			else																	//character has equal or lower precedence than top
			{
				int check2 = precedence(temp.retTop(), exp[i]);

				while (check2 > -1 && !temp.emptyStack())							//while top's precendence is higher or equal and stack isnt empty
				{
					if (temp.retTop() == '(')										//if top is an opening bracket, pop it and end loop
					{
						char character = temp.pop();
						break;
					}
					else
					{
						char character = temp.pop();								//pop characters and add to postfix expression
						postfixExp += character;
						check2 = precedence(temp.retTop(), exp[i]);
					}
				}

				temp.push(exp[i]);										//push character
			}
		}
		else														//character is closing bracket
		{
			while (1)
			{
				if (temp.retTop() == '(')							//if top is an opening bracket pop it and end loop else keep popping and adding to postfix expression
				{
					char character = temp.pop();
					break;
				}
				else
				{
					char character = temp.pop();
					postfixExp += character;
				}
			}
		}
	}
	while (!temp.emptyStack())							//empty stack and add characters to postfix expression
	{
		char character = temp.pop();
		postfixExp += character;
	}

	postfixToFile(postfixExp);
}

void Calculator::evaluatePostfix()
{
	intStack temp;										//I've used char type stack as well as int type stack in this program. Making two stacks made writing programs convenient
	string exp;

	ifstream in(::postfix, ios::in);					//read postfix expression from file

	if (!in)
	{
		cout << "\nError opening file.";
		exit(1);
	}
	else
	{
		getline(in, exp);
		in.close();
	}

	for (int i = 0; i < exp.length(); ++i)
	{
		if (exp[i] >= '0' && exp[i] <= '9')
		{
			int a = (int)(exp[i] - '0');			//converting character to same digit in integer datatype
			temp.push(a);
		}
		else									//the character is an operator
		{
			int b = temp.pop();					//pop top 2 integers and apply the operator on them
			int a = temp.pop();

			if (exp[i] == '+')
			{
				a = a + b;
			}
			else if (exp[i] == '-')
			{
				a = a - b;
			}
			else if (exp[i] == '*')
			{
				a = a * b;
			}
			else if (exp[i] == '/')
			{
				a = a / b;
			}
			else if(exp[i] == '%')
			{
				a = a % b;
			}
			else										//character is exponent ^
			{
				int result = a;

				for (int i = 0; i < b - 1; ++i)
				{
					result *= a;
				}

				a = result;
			}

			temp.push(a);							//push result on to the stack
		}
	}

	int result = temp.pop();						//pop final value and display
	cout << "\n\nFinal result: " << result;
}
