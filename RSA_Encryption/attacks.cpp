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

int gcd ( int a, int b )
{
  int c;
  while ( a != 0 ) {
     c = a; a = b%a;  b = c;
  }
  return b;
}

//Factoring attack
void attack1(int given_e, int given_n)
{
	int found_p;
	double found_q;
	double found_d;
	int null_n;
	
	cout << "Factoring attack:...\n";
	
	found_p = floor(sqrt(given_n));
	while(given_n % found_p != 0) {
		found_p = found_p - 2; //checks all odd numbers just below sqrt(n)
	}
	
	found_q = given_n / found_p;
	null_n = (found_p - 1) * (found_q - 1);
	found_d = calculate_d(given_e, null_n);
	
	cout << "\np -- > " << found_p << endl;
	cout << "q -- > " << found_q << endl;
	cout << "n -- > " << given_n << endl;
	cout << "null_n -- > " << null_n << endl;
	cout << "e -- > " << given_e << endl;
	cout << "d -- > " << found_d << endl;
	

}

//Fermat's factorization
void attack2(int given_e, int given_n)
{
	int found_p;
	double found_q;
	double found_d;
	int null_n;
	
	cout << "Fermat's factorization attack:...\n";
	
	int a;
	int b;
	
	a = ceil(sqrt(given_n));
	while (sqrt((a*a) - given_n) != floor(sqrt((a*a) - given_n))) {
		a += 1;
	}
	b = sqrt((a*a) - given_n);
	
	found_p = a - b;
	found_q = a + b;
	null_n = (found_p - 1) * (found_q - 1);
	found_d = calculate_d(given_e, null_n);
	
	cout << "\np -- > " << found_p << endl;
	cout << "q -- > " << found_q << endl;
	cout << "n -- > " << given_n << endl;
	cout << "null_n -- > " << null_n << endl;
	cout << "e -- > " << given_e << endl;
	cout << "d -- > " << found_d << endl;
}

//Pollard's p-1 algorithm
void attack3(int given_e, int given_n)
{
	int found_p;
	double found_q;
	double found_d;
	int null_n;
	int max;
	int a;
	int b;
	int r = 1;
	int g;
	
	cout << "Pollard's p-1 algorithm attack:...\n";
	cout << "Enter the max: ";
	cin >> max;
	
	while (r <= max) {
		a = (a*a) + 5 % given_n;
		b = ((b*b*b*b) + 2*(b*b) + (b*b) + b) % given_n;
		g = gcd(a-b, given_n);
		r = r + 1;
		
		if (g > 1) {
			found_q = g;
			break;
		}
	}
	
	if (g <= 1) {
		cout << "Unable to solve with the given max.\n";
		return;
	}
	
	found_p = given_n / found_q;
	null_n = (found_p - 1) * (found_q - 1);
	found_d = calculate_d(given_e, null_n);
	
	cout << "\np -- > " << found_p << endl;
	cout << "q -- > " << found_q << endl;
	cout << "n -- > " << given_n << endl;
	cout << "null_n -- > " << null_n << endl;
	cout << "e -- > " << given_e << endl;
	cout << "d -- > " << found_d << endl;
}
	
int main()
{
	string e_message;
	int given_e;
	int given_n;
	
	
	cout << "Reading encrypted message...\n";
	ifstream myfile ("e_message.txt");
	getline(myfile, e_message);
	
	cout << "Encrypted message: " << e_message << endl;
	cout << "Enter the public keys: \n";
	cout << "First (e): ";
	cin >> given_e;
	cout << "Second (n): ";
	cin >> given_n;
	cout << "Public keys: (" << given_e << ", " << given_n << ")\n\n";
	
	attack1(given_e, given_n);
	cout << endl;
	attack2(given_e, given_n);
	cout << endl;
	attack3(given_e, given_n);
	
	return 0;
}