// C++ program for the above approach

#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// encdec class with encrypt() and
// decrypt() member functions
class encdec {
	int key = 11212;

	// File name to be encrypt
	string file = "what.txt";
	char c;

public:
	void encrypt();
	void decrypt();
};

// Definition of encryption function
void encdec::encrypt()
{

	// Input stream
	fstream fin, fout;

	// Open input file
	// ios::binary- reading file
	// character by character
	fin.open(file, fstream::in);
	fout.open("encrypt.txt", fstream::out);

	// Reading original file till
	// end of file
	while (fin >> noskipws >> c) {
		int temp = (c + key);

		// Write temp as char in
		// output file
		fout << (char)temp;
	}

	// Closing both files
	fin.close();
	fout.close();
}

// Definition of decryption function
void encdec::decrypt()
{
	fstream fin;
	fstream fout;
	fin.open("encrypt.txt", fstream::in); //encrypt
	fout.open("decrypt.txt", fstream::out); //decrypt

	while (fin >> noskipws >> c) {

		// Remove the key from the
		// character
		int temp = (c - key);
		fout << (char)temp;
	}

	fin.close();
	fout.close();
}

// Driver Code
int main()
{
	encdec enc;
	char c;
	cout << "\n";
	cout << "Enter Your Choice : -> \n";
	cout << "1. encrypt \n";
	cout << "2. decrypt \n"; 
	cin >> c;
	cin.ignore();

	switch (c) {
	case '1': {
		enc.encrypt();
		break;
	}
	case '2': {
		enc.decrypt();
		break;
	}
	}
}
