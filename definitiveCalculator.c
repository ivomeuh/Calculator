#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

int verifyInputValidity(int argsize, char argv[argsize])
{
	int terminate;

	terminate = 0;
	if (argv[argsize - 1] == '+' || argv[argsize - 1] == '-' || argv[argsize - 1] == 'x' || argv[argsize - 1] == '/' || argv[argsize - 1] == ',' || argv[argsize - 1] == '.')
	{
		printf("Calculus ending with an operator or comma, please try again.\n");
		terminate = 1;
	}
	else if (argv[0] == '+' || argv[0] == '-' || argv[0] == 'x' || argv[0] == '/' || argv[0] == ',' || argv[0] == '.')
	{
		printf("Calculus starts with an operator or comma, please try again.\n");
		terminate = 1;
	}
	return(terminate);
}

void getIntegers(int argsize, char argv[argsize], int integers[argsize], int *intID,  int *i, float *count)
{
	while (isdigit(argv[*i]) == 1)
	{
		integers[*intID] = (int) argv[*i] - 48;
		(*intID)++;
		(*i)++;
		(*count)++;
	}
}

void makeNumber(int argsize, int integers[argsize], int *intID, float *count, double *nb)
{
	while (*count > 0)
	{
		*nb += integers[*intID - (int) *count] * pow(10, *count - 1);
		(*count)--;
	}
}

void makeDecimal(int argsize, int integers[argsize], int *intID, float *count, double *nb)
{
	int negPow;

	negPow = -1;
	while (*count > 0)
	{
		*nb += integers[*intID - (int) *count] * pow(10, negPow);
		negPow--;
		(*count)--;
	}
}

int getOperator(char currentChar, char nextChar, int argsize, char operators[argsize], int *opID, int *i, float *count, int *comma)
{
	int terminate;

	terminate = 0;
	if (isdigit(currentChar) == 0)
	{
		if (*i + 1 < argsize && isdigit(nextChar) == 0)
		{
			printf("Two consecutive operators, please try again.\n");
			terminate = 1;
		}
		else
		{
			if (currentChar == '+' || currentChar == '-' || currentChar == 'x' || currentChar == '/')
			{
				operators[*opID] = currentChar;
				(*opID)++;
				*comma = 0;
			}
			else if (currentChar == ',' && *comma != 1 || currentChar == '.' && *comma != 1)
			{
				*comma = 1;
			}
			else if (currentChar == ',' && *comma == 1 || currentChar == '.' && *comma == 1)
			{
				printf("Two consecutive commas, please try again.\n");
				terminate = 1;
			}
 			else if (currentChar != '\0')
			{
				printf("Invalid operator, please try again. To multiply, use 'x' instead of '*'.\n");
				terminate = 1;
			}
			else
			{
				printf("No operator detected, please enter your calculus without any whitespace\n");
				terminate = 1;
			}
		}
		(*i)++;
	}
	return(terminate);
}

void getNumber(int argsize, double numbers[argsize], int *nbID, double *nb)
{
	numbers[*nbID] = *nb;
	(*nbID)++;
	*nb = 0;
}

void getNumberOfOperators(int argsize, char operators[argsize], int *nbOfOperators)
{
	char operatorsSizeSample[10];

	sscanf(operators, "%[^NULL]", operatorsSizeSample);
	*nbOfOperators = strlen(operatorsSizeSample);
}

void add(int argsize, double numbers[argsize], int nbOfOperators, double priorityResults[2][nbOfOperators + 1], double finalResult[2][nbOfOperators + 1], int *j)
{
	if (priorityResults[0][*j] == 1)
	{
		numbers[*j] = priorityResults[1][*j];
	}
	if (priorityResults[0][*j + 1] == 1 && *j <= nbOfOperators)
	{
		numbers[*j + 1] = priorityResults[1][*j + 1];
	}
	if (finalResult[0][*j] == 1)
	{
		numbers[*j] = finalResult[1][*j];
	}
	finalResult[1][*j + 1] = numbers[*j] + numbers[*j + 1];
	finalResult[0][*j + 1] = 1;
	printf("%f + %f = %f\n", numbers[*j], numbers[*j + 1], finalResult[1][*j + 1]);
}

void subtract(int argsize, double numbers[argsize], int nbOfOperators, double priorityResults[2][nbOfOperators + 1], double finalResult[2][nbOfOperators + 1], int *j)
{
	if (priorityResults[0][*j] == 1)
	{
		numbers[*j] = priorityResults[1][*j];
	}
	if (priorityResults[0][*j + 1] == 1 && *j <= nbOfOperators)
	{
		numbers[*j + 1] = priorityResults[1][*j + 1];
	}
	if (finalResult[0][*j] == 1)
	{
		numbers[*j] = finalResult[1][*j];
	}
	finalResult[1][*j + 1] = numbers[*j] - numbers[*j + 1];
	finalResult[0][*j + 1] = 1;
	printf("%f - %f = %f\n", numbers[*j], numbers[*j + 1], finalResult[1][*j + 1]);
}

void multiply(int argsize, double numbers[argsize], int nbOfOperators, double priorityResults[2][nbOfOperators + 1], int *j)
{
	if (priorityResults[0][*j] == 1)
	{
		numbers[*j] = priorityResults[1][*j];
	}
	if (priorityResults[0][*j + 1] == 1 && *j <= nbOfOperators)
	{
		numbers[*j + 1] = priorityResults[1][*j + 1];
	}
	priorityResults[1][*j] = numbers[*j] * numbers[*j + 1];
	priorityResults[0][*j] = 1;
	printf("%f x %f = %f\n", numbers[*j], numbers[*j + 1], priorityResults[1][*j]);
	if (*j <= nbOfOperators)
	{
		priorityResults[1][*j + 1] = priorityResults[1][*j];
		priorityResults[0][*j + 1] = 1;
	}
}

void divide(int argsize, double numbers[argsize], int nbOfOperators, double priorityResults[2][nbOfOperators + 1], int *j)
{
	if (priorityResults[0][*j] == 1)
	{
		numbers[*j] = priorityResults[1][*j];
	}
	if (priorityResults[0][*j + 1] == 1 && *j <= nbOfOperators)
	{
		numbers[*j + 1] = priorityResults[1][*j + 1];
	}
	priorityResults[1][*j] = numbers[*j] / numbers[*j + 1];
	priorityResults[0][*j] = 1;
	printf("%f / %f = %f\n", numbers[*j], numbers[*j + 1], priorityResults[1][*j]);
	if (*j <= nbOfOperators)
	{
		priorityResults[1][*j + 1] = priorityResults[1][*j];
		priorityResults[0][*j + 1] = 1;
	}
}

void doCalculus(int argsize, char operators[argsize], double numbers[argsize], int nbOfOperators, double priorityResults[2][nbOfOperators + 1], double finalResult[2][nbOfOperators + 1])
{
	int j;

	j = 0;
	while (j <= nbOfOperators)
	{
		if (operators[j] == 'x')
		{
			multiply(argsize, numbers, nbOfOperators, priorityResults, &j);
		}
		else if (operators[j] == '/')
		{
			divide(argsize, numbers, nbOfOperators, priorityResults, &j);
		}
		j++;
	}
	j = 0;
	while (j <= nbOfOperators)
	{
		if (operators[j] == '+')
		{
			add(argsize, numbers, nbOfOperators, priorityResults, finalResult, &j);
		}
		else if (operators[j] == '-')
		{
			subtract(argsize, numbers, nbOfOperators, priorityResults, finalResult, &j);
		}
		j++;
	}
}

void initializePriorityResults(int nbOfOperators, double priorityResults[2][nbOfOperators + 1])
{
	int j;

	j = 0;
	while (j <= nbOfOperators)
	{
		priorityResults[0][j] = 0;
		priorityResults[1][j] = 0;
		j++;
	}
}

void initializeFinalResult(int nbOfOperators, double finalResult[2][nbOfOperators + 1])
{
	int j;

	j = 0;
	while (j <= nbOfOperators)
	{
		finalResult[0][j] = 0;
		finalResult[1][j] = 0;
		j++;
	}
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Invalid input, please enter your calculus as a comand line argument without any whitespace.\n");
		return(0);
	}

	int argsize;
	
	argsize = strlen(argv[1]);
	
	int terminate;
	int i;
	float count;
	double nb;
	int comma;
	int nbOfOperators;
	int integers[argsize];
	int intID;
	char operators[argsize];
	int opID;
	double numbers[argsize];
	int nbID;

	terminate = 0;
	i = 0;
	count = 0;
	nb = 0;
	comma = 0;
	nbOfOperators = 0;
	intID = 0;
	opID = 0;
	nbID = 0;
	
	terminate = verifyInputValidity(argsize, argv[1]);
	if (terminate == 1)
	{
		return(0);
	}
	while (i < argsize)
	{
		getIntegers(argsize, argv[1], integers, &intID, &i, &count);
		makeNumber(argsize, integers, &intID, &count, &nb);
		terminate = getOperator(argv[1][i], argv[1][i + 1], argsize, operators, &opID, &i, &count, &comma);
		if (terminate == 1)
		{
			return(0);
		}
		else if (comma == 0 && nb != 0)
		{
			getNumber(argsize, numbers, &nbID, &nb);
		}
		else if (comma == 1)
		{
			getIntegers(argsize, argv[1], integers, &intID, &i, &count);
			makeDecimal(argsize, integers, &intID, &count, &nb);
			getNumber(argsize, numbers, &nbID, &nb);
		}
	}
	getNumberOfOperators(argsize, operators, &nbOfOperators);

	double priorityResults[2][nbOfOperators + 1];
	initializePriorityResults(nbOfOperators, priorityResults);
	double finalResult[2][nbOfOperators + 1];
	initializeFinalResult(nbOfOperators, finalResult);

	doCalculus(argsize, operators, numbers, nbOfOperators, priorityResults, finalResult);
	return(0);
}
