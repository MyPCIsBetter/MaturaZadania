// Szyfr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <direct.h>
#include <string>
#include <vector>
using namespace std;

string szyfruj(string input, string key) {
	string output;
	int positionInKey = 0;
	for (int a = 0; a < input.size(); a++) {
		int letterFromInput = int(input[a]);
		int letterFromKey = int(key[positionInKey])-64;
		int newLetter = letterFromInput + letterFromKey;
		if (newLetter > 90) {
			newLetter -= 26;
		}
		char newChar = newLetter;
		output += newChar;

		if (positionInKey < key.size()-1) {
			positionInKey++;
		}
		else {
			positionInKey = 0;
		}
	}

	return output;
}

string deszyfruj(string input, string key) {
	string output;
	int positionInKey = 0;
	for (int a = 0; a < input.size(); a++) {
		int letterFromInput = int(input[a]);
		int letterFromKey = int(key[positionInKey]) - 64;
		int newLetter = letterFromInput - letterFromKey;
		if (newLetter < 65) {
			newLetter += 26;
		}
		char newChar = newLetter;
		output += newChar;

		if (positionInKey < key.size() - 1) {
			positionInKey++;
		}
		else {
			positionInKey = 0;
		}
	}
	return output;
}

int main()
{
	string test = szyfruj("LATO", "WODA");
	string test1 = deszyfruj(test, "WODA");
	string test2 = szyfruj("MARTA", "TOR");

	string scieszkaBezwzgledna = _getcwd(NULL, 0);

	vector<string> tekstJawny;
	ifstream TekstDoZaszyfrowania(scieszkaBezwzgledna + "\\tj.txt");
	if (TekstDoZaszyfrowania) {
		string line;
		while (getline(TekstDoZaszyfrowania, line)) {
			tekstJawny.push_back(line);
		}
	}

	vector<string> klucze;
	ifstream KluczDoOdszyfrowania(scieszkaBezwzgledna + "\\klucze1.txt");
	if (KluczDoOdszyfrowania) {
		string line;
		while (getline(KluczDoOdszyfrowania, line)) {
			klucze.push_back(line);
		}
	}



    return 0;
}

