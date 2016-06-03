// MaturaZadania.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <direct.h>
using namespace std;

vector<string> splitString(string text, char delimiter) {
	vector<string> result;
	string wordToAdd = "";

	for (int i = 0; i < text.size(); i++) {

		if (text[i] == delimiter) {
			result.push_back(wordToAdd);
			wordToAdd = "";
		}
		else {
			wordToAdd += text[i];
		}

	}

	if (wordToAdd != ""){
		result.push_back(wordToAdd);
	}

	return result;
}

int main()
{
	map<string, int> countries; //panstwo, ilosc zwyciêzców

	string pathToDirectory = _getcwd(NULL, 0);

	string pathToPucharFile = pathToDirectory + "\\Dane\\puchar.txt";
	string pathToZawodnicyFile = pathToDirectory + "\\Dane\\zawodnicy.txt";

	ifstream filePuchar(pathToPucharFile);
	if (!filePuchar) {
		cout << "Problem z odczytaniem pliku";
	}
	else {
		cout << "Ok" << "\n";
		string line;
		bool omitFirstLine = true;

		while (getline(filePuchar, line)) {
			if (omitFirstLine) { 
				omitFirstLine = false;
				continue; 
			}

			vector<string> oneLinePucharData = splitString(line, ';');

			string position = oneLinePucharData[1];
			string winnerId = oneLinePucharData[2];

			if (position == "1") {
				ifstream fileZawodnicy(pathToZawodnicyFile);
				if (fileZawodnicy) {
					string playersLine;
					bool omitFirstLine2 = true;
					while (getline(fileZawodnicy, playersLine)) {
						if (omitFirstLine2) {
							omitFirstLine2 = false;
							continue;
						}

						vector<string> oneLineZawodnicyData = splitString(playersLine, ';');

						string playerId = oneLineZawodnicyData[0];
						string panstwo = oneLineZawodnicyData[2];

						if (winnerId == playerId) {
							countries[panstwo] ++;
							break;
						}
					}
				}
				else {
					cout << "Problem z odczytem zawodnikow";
				}
			}
		}
		filePuchar.close();
	}

	for (map<string, int>::iterator iterator = countries.begin(); iterator != countries.end(); iterator++) {
		cout << iterator->first << ":" << iterator->second << "\n";
	}


	system("pause");
	return 0;
}

