/*
* 현재 괄호 없는 식은 정상 작동되는걸 확인.
* 괄호 불균형 오류 메세지 정상 출력 확인.
* divide by zero 오류 메세지 정상 출력 확인.
* 
* 괄호 있는 식 연산 부분에서 dequeue 오류 발생. 괄호 debug 요망.
*/

#include <iostream>
#include <stack>
#include <cctype>
#include <cstring>

using namespace std;

void calculate(string expression);
void evaluate(stack<double>& numbers, stack<char>& operations) throw (int);
void evaluate(stack<double>& numbers, char op) throw (int);
void makeDecimal(stack<double>& numbers, int count_integer, int count_fraction);
char oppositeParenthesis(char parenthesis);
int operationValue(char op);

int main()
{
	const string EOI = "EOI";
	
	string expression;

	do
	{
		cin >> expression;

		if (expression != EOI)
		{
			calculate(expression);
		}

	} while (expression != EOI);
}

void calculate(string expression)
{
	const char DECIMAL = '.';
	const int ZERO = '0';

	stack<double> numbers;  //  for store numbers
	stack<char> operations;  //  for store operators and parenthesis
	stack<char> parenthesis;  //  for store left parenthesis to check balanece of parenthesis

	int count_integer = 0;  //  count fraction part
	int count_fraction = -1;  //  count fraction part. default is -1 to describe non-decimal

	bool unbalanced = false; //  balance of parenthesis

	for (int i = 0; i != expression.length(); ++i)
	{
		if (isdigit(expression[i]))  //  check number
		{
			if (count_fraction != -1)
			{
				count_fraction++;
			}
			else
			{
				count_integer++;
			}

			numbers.push(expression[i] - ZERO);
		}
		else if (expression[i] == DECIMAL)  //  check decimal
		{
			count_fraction++;
		}
		else if (strchr("+*-/", expression[i]) != NULL)  //  check operator
		{
			//  make numbers and decimal symbol to real decimal
			if (count_fraction != -1)
			{
				makeDecimal(numbers, count_integer, count_fraction);
				
				count_integer = 0;
				count_fraction = -1;
			}

			if (operations.size() == 0 || strchr("({[", operations.top()) != NULL)
			{
				operations.push(expression[i]);
			}
			else  //  operations.size() != 0 && strchr("({[", operations.top()) == NULL
			{
				//  stack's operation value is higher than expression
				if (operationValue(operations.top()) >= operationValue(expression[i]))
				{
					try
					{
						evaluate(numbers, operations.top());
						operations.pop();
						operations.push(expression[i]);
					}
					catch (int err)
					{
						cout << "Error!: divide by zero" << endl;
						return;
					}
				}
				else //  expression's operation value is higher than stack
				{
					operations.push(expression[i]);
				}
			}
		}
		else if (strchr("({[", expression[i]) != NULL)
		{
			operations.push(expression[i]);
			parenthesis.push(expression[i]);
		}
		else if (strchr(")}]", expression[i]) != NULL)
		{
			if (count_fraction != -1)
			{
				makeDecimal(numbers, count_integer, count_fraction);

				count_integer = 0;
				count_fraction = -1;
			}

			if (parenthesis.size() != 0 && oppositeParenthesis(parenthesis.top()) == expression[i])
			{
				try
				{
					parenthesis.pop();
					evaluate(numbers, operations);
				}
				catch (int err)
				{
					cout << "Error!: divide by zero" << endl;
					return;
				}
			}
			else
			{
				unbalanced = true;
				break;
			}
		}
	}

	if (parenthesis.size() != 0 || unbalanced)
	{
		cout << "Error!: unbalanced parentheses" << endl;
	}
	else
	{
		try
		{
			if (count_fraction != -1)
			{
				makeDecimal(numbers, count_integer, count_fraction);
			}

			evaluate(numbers, operations);

			cout << numbers.top() << endl;
		}
		catch (int err)
		{
			cout << "Error!: divide by zero" << endl;
		}
	}
}

void evaluate(stack<double>& numbers, stack<char>& operations) throw (int)
{
	while (1)
	{
		if (operations.top() == '/' && numbers.top() == 0)
		{
			throw 0;
		}

		evaluate(numbers, operations.top());
		operations.pop();

		if (operations.size() == 0 || strchr("({[", operations.top()) != NULL)
		{
			break;
		}
	}
}

void evaluate(stack<double>& numbers, char op) throw (int)
{
	double operand1, operand2;
	
	if (op == '/' && numbers.top() == 0)
	{
		throw 0;
	}

	operand2 = numbers.top();
	numbers.pop();

	operand1 = numbers.top();
	numbers.pop();

	switch (op)
	{
	case '+':
		numbers.push(operand1 + operand2);
		break;
	case '-':
		numbers.push(operand1 - operand2);
		break;
	case '*':
		numbers.push(operand1 * operand2);
		break;
	case '/':
		numbers.push(operand1 / operand2);
		break;
	}
}

char oppositeParenthesis(char parenthesis)
{
	switch (parenthesis)
	{
	case '(':
		return ')';
	case '{':
		return '}';
	case ']':
		return ']';
	}
}

void makeDecimal(stack<double>& numbers, int count_integer, int count_fraction)
{
	double result = 0;
	double powerOfTen = 1;

	for (int i = count_fraction; i != 0; --i)
	{
		powerOfTen /= 10;
		result += numbers.top() * powerOfTen;
		numbers.pop();
	}

	powerOfTen = 1;

	for (int i = count_integer; i != 0; --i)
	{
		result += numbers.top() * powerOfTen;
		numbers.pop();

		powerOfTen *= 10;
	}

	numbers.push(result);
}

int operationValue(char op)
{
	switch (op)
	{
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	}
}