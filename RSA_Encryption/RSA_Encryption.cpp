#include <string>
#include <stdio.h>
#include <iostream>
#include <stdlib.h> 
#include <ctime> 
#include <math.h>
#include <fstream>
#include <vector>
using namespace std;


long long int p, q, n, null_n, e, d;
string message, en_message, de_message;
vector<long long int> temp;

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
		num = primeNumber(1, null_n);		//probably wrong. Shouldnt return a random prime
		if(!(n % num == 0 || null_n % num == 0))	//changed || to &&
			return num;
	}
}

int calculate_d(int e, int null_n)
{
	long long int i = null_n;
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
	temp.clear();
	p = primeNumber(10000,10190);
	q = primeNumber(10000,10190);
	
	while(p == q)
		q = primeNumber(100,190);
	
	n = p * q;
	null_n = (p-1)*(q-1);
	
	e = calculate_e(n, null_n);
	d = calculate_d(e,null_n);	
	
	/*cout << "\np -- > " << p << endl;
	cout << "q -- > " << q << endl;
	cout << "n -- > " << n << endl;
	cout << "null_n -- > " << null_n << endl;
	cout << "e -- > " << e << endl;
	cout << "d -- > " << d << endl;*/
	
	
	
	for(int j = 0;j < message.length(); j++)
	{	
		char letter = message[j];
		long long int k = 1;
		for(int j = 0; j<e; j++)
		{
			k = k*letter;
			k = k%n;
		}
		
		//char encrypted_letter = (fmod(pow(i, e), n))+64;
		char encrypted_letter = (k%94 + 33);
		en_message = en_message + encrypted_letter;
		temp.push_back(k / 94);
		
		
		/*cout << "inputed letter: " << letter ;
		cout << " --> "<< encrypted_letter << " --> " << (long long int)encrypted_letter;
		cout << " --> "<< k  << " --> "<< (k-33)/94  << endl;*/
	}
	cout << "\nEncrypted message: " << en_message << endl;
	cout << endl;
	
}


/*int find_decrypted_code(int encrypted_letter)
{
	int decrypted_number = 1;


	//not currently in use
	long long int k = 1;
	for(int j = 0; j<e; j++)
	{
		k = k*encrypted_letter;
		k = k%n;
	}


	//cout << "fmod(pow): " <<  fmod(pow(encrypted_letter, d), n) << "\t";
	return fmod(pow(encrypted_letter, d), n); //fmod(pow(encrypted_letter, d), n);
			//math is correct think problem is in the encryption, repeats at 14
}

void decryption()
{
	vector<char> encrypted_v;
	int encrypted_letter;
	int decrypted_number;
	char decrypted_letter;
	
	
	//takes d and n from the globals
	//make sure everything is as it is supposed to be
	cout << "\np -- > " << p << endl;
	cout << "q -- > " << q << endl;
	cout << "n -- > " << n << endl;
	cout << "null_n -- > " << null_n << endl;
	cout << "e -- > " << e << endl;
	cout << "d -- > " << d << endl;
	
	char x;
	ifstream myfile ("message.txt");
	ofstream write_file("d_message.txt");
	while(myfile >> x) {
		cout << x << "\tcode: " << (int)x <<  endl;
		encrypted_v.push_back(x);
	}
	
	for (int i = 0; i < encrypted_v.size(); ++i) {
		encrypted_letter = encrypted_v[i];
		cout << "encrypted_letter: " << encrypted_letter << endl;
		decrypted_number = find_decrypted_code(encrypted_letter);	//-64);
		decrypted_letter = decrypted_number%127;		//+64;
	//	cout << "dl: " << decrypted_number << endl;
		write_file << decrypted_letter;		
	}
	
	myfile.close();
	write_file.close();
}
*/

void decryption()
{
	vector<char> encrypted_v;
	long long int encrypted_letter;
	long long int decrypted_number;
	char decrypted_letter;
	
	char x;
	ifstream myfile ("message.txt");
	ofstream write_file("d_message.txt");
	while(myfile >> x) {
		encrypted_v.push_back(x);
	}
	
	for (int i = 0; i < en_message.length(); ++i) {
		encrypted_letter = en_message[i];
		//cout << "encrypted_letter:     " << (char)encrypted_letter << " --> " << encrypted_letter;
		
		unsigned long long int enc_num = (encrypted_letter-33)+ (94 * temp[i]);
		
		
		unsigned long long int k = 1;
		for(int j = 0; j<d; j++)
		{
			k = k*enc_num;
			k = k%n;
		}
		
		char d_letter = k;
		//cout << d_letter <<endl;
		//cout << " --> " << enc_num << " --> " << k << " --> " << d_letter << endl;
		
		write_file << d_letter;
		de_message = de_message + d_letter;
	}
	
	cout << "Decrypted message: " << de_message << endl;
	myfile.close();
	write_file.close();
}




//46340^2 is the highest number with no overflow with int
int main()
{
	srand(time(0)); //srand() needs to be called here so primeNumber() work properly 
	
	for(int i = 1; i<2; i++)
	{
		message = "";
		cout << "Enter message: ";
		
		getline(cin, message);
		
		encryption();
		decryption();
		
		ifstream file ("d_message.txt");
		string test = "";
		getline(file,test);
				
		file.close();
	}
	

	
	
	
}