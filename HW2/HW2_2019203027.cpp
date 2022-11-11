// Name: ¾çÁ¤¿ë
// Student ID: 2019203027

#include <iostream>
#include <stack>
#include <cctype>
#include <cstring>
#include <iomanip>
#include <cmath>

using namespace std;

void calculate(string expression);
void evaluate(stack<double>& numbers, stack<char>& operations) throw (int);
void evaluate(stack<double>& numbers, char op, bool isReverse = false) throw (int);
void finalEvaluate(stack<double>& numbers, stack<char> operations) throw(int);
void makeDecimal(stack<double>& numbers, int& count_integer, int& count_fraction);
char oppositeParenthesis(char parenthesis);
int operationValue(char op);
bool isZero(double x);

template <class Item>
stack<Item> reverse(stack<Item> s);

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
	
	bool isBalanced = true;  //  check parenthesis balance
	bool divideByZero = false;

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
						divideByZero = true;
						break;
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
			}

			if (parenthesis.size() != 0 && oppositeParenthesis(parenthesis.top()) == expression[i])
			{
				try
				{
					parenthesis.pop();
					evaluate(numbers, operations);
					operations.pop();
				}
				catch (int err)
				{
					divideByZero = true;
					break;
				}
			}
			else  //  parenthesis unbalance
			{
				isBalanced = false;
				break;
			}
		}
	}

	if (parenthesis.size() != 0 || !isBalanced)
	{
		cout << "Error!: unbalanced parentheses" << endl;
		return;
	}
	else
	{
		try
		{
			if (count_fraction != -1)
			{
				makeDecimal(numbers, count_integer, count_fraction);
			}

			finalEvaluate(numbers, operations);

			streamsize perc = cout.precision();

			cout << fixed << setprecision(3)
				<< numbers.top() << setprecision(perc) << endl;
		}
		catch (int err)
		{
			divideByZero = true;
		}
	}

	if (divideByZero)
	{
		cout << "Error!: divide by zero" << endl;
	}
}

void evaluate(stack<double>& numbers, stack<char>& operations) throw (int)
{
	while (1)
	{
		if (operations.top() == '/' && isZero(numbers.top()))
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

void evaluate(stack<double>& numbers, char op, bool isReverse) throw (int)
{
	double operand1, operand2;

	if (op == '/' && isZero(numbers.top()))
	{
		throw 0;
	}

	if (!isReverse)
	{
		operand2 = numbers.top();
		numbers.pop();

		operand1 = numbers.top();
		numbers.pop();
	}
	else
	{
		operand1 = numbers.top();
		numbers.pop();

		operand2 = numbers.top();
		numbers.pop();
	}

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

void finalEvaluate(stack<double>& numbers, stack<char> operations) throw(int)
{
	stack <char> operations_R;
	bool isReverse;

	if (operations.size() > 1)
	{
		operations_R = reverse(operations);
		numbers = reverse(numbers);

		isReverse = true;
	}
	else
	{
		operations_R = operations;

		isReverse = false;
	}

	while (1)
	{
		if (operations_R.top() == '/' && isZero(numbers.top()))
		{
			throw 0;
		}

		evaluate(numbers, operations_R.top(), isReverse);
		operations_R.pop();

		if (operations_R.size() == 0)
		{
			break;
		}
	}
}

template <class Item>
stack<Item> reverse(stack<Item> s)
{
	stack<Item> result;

	do
	{
		result.push(s.top());
		s.pop();
	} while (!s.empty());

	return result;
}

char oppositeParenthesis(char parenthesis)
{
	switch (parenthesis)
	{
	case '(':
		return ')';
	case '{':
		return '}';
	case '[':
		return ']';
	default:
		return ' ';
	}
}

void makeDecimal(stack<double>& numbers, int& count_integer, int& count_fraction)
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

	count_integer = 0;
	count_fraction = -1;

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

bool isZero(double x)
{
	double e = 1e-015;

	return fabs(x - 0.0F) <= e;
}