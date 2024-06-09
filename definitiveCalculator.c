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
	return(terminate);
}

void getIntegers(int argsize, char argv[argsize], int integers[argsize], int *intID,  int *i, float *count)
{
	while (isdigit(argv[*i]) == 1)
	{
		integers[*intID] = (int) argv[*i] - 48;
		//printf("integer[%d] = %d\n", *intID, integers[*intID]);
		(*intID)++;
		(*i)++;
		//printf("i = %d\n", *i);
		(*count)++;
		//printf("count = %f\n", *count);
	}
}

void makeNumber(int argsize, int integers[argsize], int *intID, float *count, double *nb)
{
	while (*count > 0)
	{
		*nb += integers[*intID - (int) *count] * pow(10, *count - 1);
		//printf("nb = %f\n", *nb);
		(*count)--;
		//printf("count = %f\n", *count);
	}
}

void makeDecimal(int argsize, int integers[argsize], int *intID, float *count, double *nb)
{
	int negPow;

	negPow = -1;
	while (*count > 0)
	{
		*nb += integers[*intID - (int) *count] * pow(10, negPow);
		//printf("nb = %f\n", *nb);
		negPow--;
		(*count)--;
		//printf("count = %f\n", *count);
	}
}

int getOperator(char currentChar, char nextChar, int argsize, char operators[argsize], int *opID, int *i, float *count, int *comma)
{
	int terminate;

	terminate = 0;
	*comma = 0;
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
			}
			else if (currentChar == ',' || currentChar == '.')
			{
				*comma = 1;
			}
 			else if (currentChar != '\0')
			{
				printf("Invalid operator, please try again. To multiply, use 'x' instead of '*'.\n");
				terminate = 1;
			}
		}
		(*i)++;
		//printf("i = %d\n", *i);
	}
	return(terminate);
}

void getNumber(int argsize, double numbers[argsize], int *nbID, double *nb)
{
	numbers[*nbID] = *nb;
	//printf("numbers[%d] = %f\n", *nbID, numbers[*nbID]);
	(*nbID)++;
	*nb = 0;
}

void getNumberOfOperators(int argsize, char operators[argsize], int *nbOfOperators)
{
	char operatorsSizeSample[10];

	sscanf(operators, "%[^NULL]", operatorsSizeSample);
	*nbOfOperators = strlen(operatorsSizeSample);
}

void add(int argsize, double numbers[argsize], int nbOfOperators, double priorityResults[nbOfOperators + 1], double finalResult[nbOfOperators + 1], int *j)
{
	//printf("numbers[%d] = %f\n", *j, numbers [*j]);
	if (priorityResults[*j] != 0)
	{
		numbers[*j] = priorityResults[*j];
		printf("numbers[%d] = priorityResults[%d] = %f\n", *j, *j, numbers[*j]);
	}
	if (priorityResults[*j + 1] != 0 && priorityResults[*j + 1] != '\0')
	{
		numbers[*j + 1] = priorityResults[*j + 1];
		printf("numbers[%d] = priorityResults[%d] = %f\n", *j + 1, *j + 1, numbers[*j + 1]);
	}
	if (finalResult[*j] != 0)
	{
		numbers [*j] = finalResult[*j];
		printf("numbers[%d] = finalResult[%d] = %f\n", *j, *j, numbers[*j]);
	}
	printf("numbers[%d] + numbers[%d] = %f + %f\n", *j, *j + 1, numbers[*j], numbers [*j + 1]);
	finalResult[*j + 1] = numbers[*j] + numbers[*j + 1];
}

void doCalculus(int argsize, char operators[argsize], double numbers[argsize], int nbOfOperators, double priorityResults[nbOfOperators + 1], double finalResult[nbOfOperators + 1])
{
	int j;

	//printf("numbers[0] = %f\n", numbers[0]);
	j = 0;
	while (j <= nbOfOperators)
	{
		if (operators[j] == '+')
		{
			add(argsize, numbers, nbOfOperators, priorityResults, finalResult, &j);
			printf("finalResult[%d] = %f\n", j + 1, finalResult[j + 1]);
			//j++;
		}
		j++;
	}
}

int main(int argc, char *argv[])
{
	int argsize;
	
	argsize = strlen(argv[1]);
	
	int terminate;
	int i;
	int j;
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
	j = 0;
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
		//printf("comma = %d\n", comma);
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
		//printf("numbers[%d] = %f\n", nbID - 1, numbers[nbID - 1]);
	}
	getNumberOfOperators(argsize, operators, &nbOfOperators);
	printf("Operators string is set as: %s\n", operators);
	printf("numbers[0] = %f\n", numbers[0]);
	double priorityResults[nbOfOperators + 1];
	//while (j <= nbOfOperators + 1)
	{
		priorityResults[j] = 0;
		j++;
	}
	printf("numbers[0] = %f\n", numbers[0]);
	j = 0;	
	double finalResult[nbOfOperators + 1];
	//while (j <= nbOfOperators + 1)
	{
		finalResult[j] = 0;
		j++;
	}
	//printf("numbers[0] = %f\n", numbers[0]);
	doCalculus(argsize, operators, numbers, nbOfOperators, priorityResults, finalResult);
	return(0);
}
