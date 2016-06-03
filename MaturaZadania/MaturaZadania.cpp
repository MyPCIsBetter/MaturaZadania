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

	if (wordToAdd != "") {
		result.push_back(wordToAdd);
	}

	return result;
}

class Competition {
public:
	string idOfPlayer;
	string position;
	Competition(string, string);
};

Competition::Competition(string playerId, string hisPosition) {
	idOfPlayer = playerId;
	position = hisPosition;
}

class Player {
public:
	string id;
	string country;
	Player(string, string);
};

Player::Player(string playerId, string hisCountry) {
	id = playerId;
	country = hisCountry;
}

int main()
{
	map<string, int> countries; //panstwo, ilosc zwyciêzców
	

	string pathToDirectory = _getcwd(NULL, 0);

	string pathToPucharFile = pathToDirectory + "\\Dane\\puchar.txt";
	string pathToZawodnicyFile = pathToDirectory + "\\Dane\\zawodnicy.txt";

	vector<Competition> competitions;

	ifstream filePuchar(pathToPucharFile);
	if (!filePuchar) {
		cout << "Problem z odczytaniem pliku";
	}
	else {
		string line;
		bool omitFirstLine = true;

		while (getline(filePuchar, line)) {
			if (omitFirstLine) {
				omitFirstLine = false;
				continue;
			}

			vector<string> oneLinePucharData = splitString(line, ';');

			competitions.push_back(Competition(oneLinePucharData[2], oneLinePucharData[1]));
		}
	}

	vector<Player> players;

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

			players.push_back(Player(oneLineZawodnicyData[0], oneLineZawodnicyData[2]));
		}
	}
	else {
		cout << "Problem z odczytem zawodnikow";
	}


	for (int i = 0; i < competitions.size(); i++) {
		Competition currentCompetition = competitions[i];

		if (currentCompetition.position == "1") {
			for (int p = 0; p < players.size(); p++) {
				Player currentPlayer = players[p];

				if (currentCompetition.idOfPlayer == currentPlayer.id) {
					countries[currentPlayer.country]++;
				}
			}
		}
	}

	for (map<string, int>::iterator iterator = countries.begin(); iterator != countries.end(); iterator++) {
		cout << iterator->first << ":" << iterator->second << "\n";
	}


	system("pause");
	return 0;
}

