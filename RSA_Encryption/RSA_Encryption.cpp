#include <string>
#include <stdio.h>
#include <iostream>
#include <stdlib.h> 
#include <ctime> 
#include <math.h>
#include <fstream>
#include <vector>
#include <unistd.h>

using namespace std;


long long int p, q, n, null_n, e, d, ran= 128;
string message, en_message, de_message;
vector<long long int> temp;

bool isPrime(int num)
{
	if(num%2 == 0)
		return false;
	for (int i=3; i < num; i=i+2)
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

int primeNumber(int min, int max)
{
	int num = -1;
	
	while(!(min <=num && num < max))
	{
		do
		{
			num = rand() % 70000+1;
		}while(!isPrime(num));
	}
	
	return num;
}

int calculate_e(int n, int null_n)
{
	int num = 0;
	
	while(true)
	{
		num = primeNumber(1, null_n/2);		
		if(!(n % num == 0 || null_n % num == 0))	
			return num;
	}
}

int calculate_d(int e, int null_n)
{
	long long int i = 1;
	while(true)
	{
		if((e * i)%null_n == 1)
			return i;
		i = i + 2;
	}
}

void encryption()
{
	temp.clear();
	p = primeNumber(35000,40000);
	q = primeNumber(35000,40000);
	
	while(p == q)
		q = primeNumber(100,190);
	
	n = p * q;
	null_n = (p-1)*(q-1);
	
	e = calculate_e(n, null_n);
	d = calculate_d(e,null_n);	
	
	ofstream write_file("e_message.txt");
	
	cout << "\np -- > " << p << endl;
	cout << "q -- > " << q << endl;
	cout << "n -- > " << n << endl;
	cout << "null_n -- > " << null_n << endl;
	cout << "e -- > " << e << endl;
	cout << "d -- > " << d << endl;
	
	
	
	for(int j = 0;j < message.length(); j++)
	{	
		int percent = 0;
		cout << "\r" << ((j)*100)/message.length() << "% completed: ";
		cout << string(((j)*10)/message.length(), '|');
		cout.flush();
		
		char letter = message[j];
		
		
		long long int k = 1;
		for(int j = 0; j<e; j++)
		{
			k = k*letter;
			k = k%n;
		}
		
		k = k*ran;
		
		char encrypted_letter = (k%94 + 33);
		en_message = en_message + encrypted_letter;
		temp.push_back(k / 94);
		
		cout << "\r" << ((j+1)*100)/message.length() << "% completed: ";
		cout << string(((j+1)*10)/message.length(), '|');
		cout.flush();
		
		write_file << encrypted_letter;
		
		//cout << "inputed letter: " << letter ;
		//cout << " --> "<< encrypted_letter << " --> " << (long long int)encrypted_letter;
		//cout << " --> "<< k  << " --> "<< (k-33)/94  << endl;
	}
	cout << "\nEncrypted message: " << en_message << endl;
	cout << endl;
	write_file.close();
}

void decryption()
{
	long long int encrypted_letter;
	
	char x;
	ifstream myfile ("message.txt");
	ofstream write_file("d_message.txt");

	
	for (int i = 0; i < en_message.length(); ++i) {
		int percent = 0;
		cout << "\r" << ((i)*100)/message.length() << "% completed: ";
		cout << string(((i)*10)/message.length(), '|');
		cout.flush();
		
		encrypted_letter = en_message[i];
		
		unsigned long long int enc_num = (encrypted_letter-33)+ (94 * temp[i]);
		
		enc_num = enc_num/ran;
		
		unsigned long long int k = 1;
		for(int j = 0; j<d; j++)
		{
			k = k*enc_num;
			k = k%n;
		}
		
		
		char d_letter = (k%128);
		
		cout << "\r" << ((i+1)*100)/message.length() << "% completed: ";
		cout << string(((i+1)*10)/message.length(), '|');
		cout.flush();
		
		write_file << d_letter;
		de_message = de_message + d_letter;
	}
	
	cout << "\nDecrypted message: " << de_message << endl;
	myfile.close();
	write_file.close();
}




//46340^2 is the highest number with no overflow with int
int main()
{
	srand(time(0)); //srand() needs to be called here so primeNumber() work properly 
	ran = 128;
	for(int i = 1; i<2; i++)
	{
		message = "";
		cout << "Enter message: ";
		getline(cin, message);
		
		encryption();
		decryption();		
		
		if(message == de_message) {
			cout << "Decryption success.\n" << endl;
		}
		else {
			cout << "Decryption incorrect.\n";
		}
		ifstream file ("d_message.txt");
		string test = "";
		getline(file,test);
				
		file.close();
	}
	

	
}
