#include <string>
#include <stdio.h>
#include <iostream>
#include <stdlib.h> 
#include <ctime> 
using namespace std;


int p, q, n, null_n, e, d;


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

//returns prime number greater than int given to it
int primeNumber(int min, int max)
{
	int num = -1;
	
	while(!(min <=num && num < max))
	{
		do
		{
			num = rand() % 45000+1;
		}while(!isPrime(num));
	}
	
	return num;
}

int calculate_e(int n, int null_n)
{
	int num = 0;
	
	while(true)
	{
		num = primeNumber(1, null_n);
		if(!(n % num == 0 || null_n % num == 0))
			return num;
	}
}

int calculate_d(int e, int null_n)
{
	int i = null_n;
	while(true)
	{
		int num = e * i;
		
		num = num % null_n;
		if(num == 1)
			return i;
		i++;
	}
}

void encryption()
{
	p = 2;
	q = 7;
	
	n = p * q;
	null_n = (p-1)*(q-1);
	
	e = calculate_e(n, null_n);
	d = calculate_d(e,null_n);
	
	cout << "\np -- > " << p << endl;
	cout << "q -- > " << q << endl;
	cout << "n -- > " << n << endl;
	cout << "null_n -- > " << null_n << endl;
	cout << "e -- > " << e << endl;
	cout << "d -- > " << d << endl;
	
	string message = "B";
	
	int char_dex = 'b' - 'a';
	cout << char_dex << endl;

}


//46340^2 is the highest number with no overflow with int
int main()
{
	srand(time(0)); //srand() needs to be called here so primeNumber() work properly 
	
	for(int i = 1; i<5; i++)
	{
		encryption();
	}
	
	
	
	
}