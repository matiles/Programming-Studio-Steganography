#include <string>
#include <stdio.h>
#include <iostream>
#include <stdlib.h> 
#include <ctime> 
using namespace std;


int p;
int q;
int n;

bool isPrime(int num)
{
	for (int i=2; i < num; i++)
	{
		if (num % i == 0)
		{
			return false;
		}
	}
	
	return true;	
}

int primeNumber()
{
	int num = 0;
	do
	{
		num = rand() % 45000+1;
	}while(!isPrime(num));
	
	return num;
}


//returns prime number greater than int given to it
int primeNumber(int min)
{
	int num = 0;
	
	while(num < min)
	{
		do
		{
			num = rand() % 45000+1;
		}while(!isPrime(num));
	}
	
	return num;
}

void encryption()
{
	int p = primeNumber(20000);
	int q = primeNumber(20000);
	
	int n = p * q;
	
	cout << "p -- > " << p << endl;
	cout << "q -- > " << q << endl;
	cout << "n -- > " << n << endl;
}


//46340^2 is the highest number with no overflow with int
int main()
{
	srand(time(0)); //srand() needs to be called here so primeNumber() work properly 
	
	for(int i = 1; i<100; i++)
	{
		encryption();
	}
	
	
	
	
}