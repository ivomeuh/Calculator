#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

int verifyCalculusValidity(int argsize, char argv[argsize])
{
	int terminate;

	terminate = 0;
	if (argsize < 3 || argv[argsize - 1] == '+' || argv[argsize - 1] == '-' || argv[argsize - 1] == 'x' || argv[argsize - 1] == '/' || argv[argsize - 1] == ',' || argv[argsize - 1] == '.')
	{
		printf("Invalid calculus. Please try again.\n");
	}
	return(terminate);
}

int obtainOperator(char argv, int argsize, char operators[argsize], int *opID, int *terminate)
{
	if (argv == '+' || argv == '-' || argv == 'x' || argv == '/' || argv == ',' || argv == '.')
	{
		operators[*opID] = argv;
	}
	else if (argv != '\0')
	{
		printf("Invalid operator, please try again.\n");
		*terminate = 1;
	}
	return(invalidOperator);
}

void obtainInteger(char argv, int argsize, int integers[argsize], int *intID)
{
	integers[*intID] = (int) argv - 48;
}

void makeNumber(int argsize, int integers[argsize], int *intID, float *count, double *nb)
{
	*nb += integers[*intID - (int) *count] * pow(10, *count - 1);
	(*count)--;
}

void makeDecimalNumber(int argsize, int integers[argsize], int *intID, float *count, float *decimalCount, double *nb)
{

}

void getOperator(char argv, int argsize, char operators[argsize], char checkDoubleOperator, int *i, int *terminate, float *count, int *opID, int *terminate)
{
	int invalidOperator;

	invalidOperator = 0;
	if (isdigit(argv) == 0)
	{
		if (*i + 1 < argsize && isdigit(checkDoubleOperator) == 0)
		{
			printf("Two consecutive operators: action impossible. Please try again.\n");
			*terminate = 1;
		}
		else
		{
			obtainOperator(argv, argsize, operators, opID, terminate);
			(*i)++;
			*count = 0;
		}
	}
}

void getIntegers(int argsize, char argv[argsize], int integers[argsize], int *intID, int *i, float *count)
{
	while (isdigit(argv[*i]) == 1)
	{
		obtainInteger(argv[*i], argsize, integers, intID);
		(*i)++;
		(*intID)++;
		(*count)++;
	}
}

void getNumber(int argsize, int integers[argsize], int *intID, float *count, double numbers[argsize], int *nbID)
{
	double nb;

	nb = 0;
	while (*count > 0)
	{
		makeNumber(argsize, integers, intID, count, &nb);
	}
		numbers[*nbID] = nb;
		(*nbID)++;
		(*opID)++;
}

void getDecimalNumber(int argsize, int integers[argsize], int *intID, float *count, float *decimalCount, double numbers[argsize], int *nbID)
{
	double nb;

}

void getNumberOfOperators(int argsize,char operators[argsize], int *numberOfOperators)
{
	char operatorsSizeSample[20];

	sscanf(operators, "%[^NULL]", operatorsSizeSample);
	*numberOfOperators = strlen(operatorsSizeSample);
}

void doCalculus(int *numberOfOperators, char operators[*numberOfOperators], int argsize, double numbers[argsize])
{
	int i;

	i = 0;
	while (i<=*numberOfOperators) //- nb de virgules
	{
		if (operators[i] == 'x')
		{
			//multiply(argsize, numbers);
		}
		else if (operators[i] == '/')
		{
			//divide(argsize, numbers);
		}
		i++;
	}
	i = 0;
	while (i <= *numberOfOperators) // - nb de virgules
	{
		if (operators[i] == '+')
		{
			//add(argsize, numbers);
		}
		else if (operators[i] == '-')
		{
			//substract(argsize, numbers);
		}
		i++;
	}
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Invalid input. Please insert your calculus without any whitespace as a command line argument.\n");
		return(0);
	}

	int i;
	int argsize;
	int numberOfOperators;
	int nb;
	int dNb;
	int terminate;
	int intID;
	int nbID;
	int opID;
	float count;
	float decimalCount;
	
	i = 0;
	nb = 0;
	dNb = 0;
	terminate = 0;
	intID = 0;
	nbID = 0;
	opID = 0;
	count = 0;
	argsize = strlen(argv[1]);

	char operators[argsize];
	int integers[argsize];
	double numbers[argsize];
	
	if (verifyCalculusValidity(argsize, argv[1]) == 1)
	{
		return(0);
	}
	while (i < argsize)
	{
		getIntegers(argsize, argv[1], integers, &intID, &i, &count);
		getOperator(argv[1][i], argsize, operators, argv[1][i + 1], &i, &terminate, &count, &opID, &terminate);
		if (terminate == 1)
		{
			return(0);
		}
		else if (operators[*opID] == ',' || operators[*opID] == '.')
		{
			decimalCount = *count;
			*count = 0;
			getIntegers(argsize, argv[1], integers, &intID, &i, &count);
			makeNumber(argsize, integers, &intId, &count, &nb);
			makeDecimalNumber(argsize, integers, &intID, &count, &decimalCount, numbers, &nbID);
		}
		else if (operators[*opID] != ',' && operators[*opID] != '.')
		{
			getNumber(argsize, integers, &intID, &count, numbers, &nbID);
	
		}
	}
	getNumberOfOperators(argsize, operators, &numberOfOperators);
	printf("Operators string is set as: %s\n", operators);
	//printf("Numbers string set as: %f %f %f %f\n", numbers[0], numbers[1], numbers[2], numbers[3]);
	printf("Number of operators: %d\n", numberOfOperators);
	return(0);
}
