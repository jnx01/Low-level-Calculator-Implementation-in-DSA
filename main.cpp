#include <iostream>
#include <string>
#include "Calculator.h"


using namespace std;

int main()
{
	int option = 0;
	Calculator obj;

	cout << "\n\n\t\t\t\t\t\tWelcome to Calculator Program\n";

	while (1)
	{
		cout << "\n\nEnter 1 to write and save an infix expression, "
			<< "\n2 to check the validity of saved infix expression, "
			<< "\n3 to convert saved infix expression to postfix,"
			<< "\n4 to evaluate result of saved postfix expression, or"
			<< "\n5 to exit.\n\n";

		cin >> option;

		if (option == 1)
		{
			string exp;
			cout << "\nEnter expression: ";
			cin >> exp;												//intentionally not using getline
			obj.infixToFile(exp);
			cout << "\n\nExpression saved in file.";
		}
		else if (option == 2)
		{
			bool check = obj.infixValidity();
			if (check == true)
			{
				cout << "\n\nExpression valid.";
			}
			else
			{
				cout << "\n\nExpression invalid.";
			}
		}
		else if (option == 3)
		{
			bool check = obj.infixValidity();
			if (check == true)
			{
				obj.infixToPostfix();
				cout << "\n\nPostfix expression generated and saved in file.";
			}
			else
			{
				cout << "\n\nConversion not possible. Infix expression invalid.";
			}
		}
		else if (option == 4)
		{
			obj.evaluatePostfix();				//postfix file holds only valid expressions hence we dont need to check validity before postfix evaluation
		}
		else
		{
			cout << "\n\nGoodbye!\n";
			break;
		}

	}

}
