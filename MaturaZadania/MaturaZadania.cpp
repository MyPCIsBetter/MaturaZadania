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

class Score {
public:
	string idOfPlayer;
	string position;
	string points;
	string idOfCompetition;
	string firstJump;
	string secondJump;
	Score(string, string, string, string, string, string);
};

Score::Score(string playerId, string hisPosition, string numberOfPoints, string competitionid, string fJump, string secJump) {
	idOfPlayer = playerId;
	position = hisPosition;
	points = numberOfPoints;
	idOfCompetition = competitionid;
	firstJump = fJump;
	secondJump = secJump;
}

class Player {
public:
	string id;
	string name;
	string country;
	Player(string, string, string);
};

Player::Player(string playerId, string hisCountry, string hisName) {
	id = playerId;
	country = hisCountry;
	name = hisName;
}

class Competition {
public:
	string id;
	string name_of_place;
	string season;
	Competition(string, string, string);
};

Competition::Competition(string idOfComp, string place, string seasonYears) {
	id = idOfComp;
	name_of_place = place;
	season = seasonYears;
}

int main()
{
	map<string, int> countries; //panstwo, ilosc zwyciêzców
	vector<int> idsOfPlayerWithMoreThan450Points;

	string pathToDirectory = _getcwd(NULL, 0);

	string pathToPucharFile = pathToDirectory + "\\Dane\\puchar.txt";
	string pathToZawodnicyFile = pathToDirectory + "\\Dane\\zawodnicy.txt";
	string pathToZawodyFile = pathToDirectory + "\\Dane\\zawody.txt";

	vector<Score> Scores;

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

			Score c = Score(oneLinePucharData[2], oneLinePucharData[1], oneLinePucharData[5], oneLinePucharData[6], oneLinePucharData[3], oneLinePucharData[4]);

			Scores.push_back(c);

			if (atoi(oneLinePucharData[5].c_str()) > 450) {
				idsOfPlayerWithMoreThan450Points.push_back(atoi(c.idOfPlayer.c_str()));
			}
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

			players.push_back(Player(oneLineZawodnicyData[0], oneLineZawodnicyData[2], oneLineZawodnicyData[1]));
		}
	}
	else {
		cout << "Problem z odczytem zawodnikow";
	}


	vector<Competition> competitions;

	ifstream fileZawody(pathToZawodyFile);
	if (fileZawody) {
		string compLine;
		bool omitFirstLine2 = true;
		while (getline(fileZawody, compLine)) {
			if (omitFirstLine2) {
				omitFirstLine2 = false;
				continue;
			}

			vector<string> oneLineZawodyData = splitString(compLine, ';');

			competitions.push_back(Competition(oneLineZawodyData[0], oneLineZawodyData[2], oneLineZawodyData[3]));
		}
	}
	else {
		cout << "Problem z odczytem zawodnikow";
	}


	for (int i = 0; i < Scores.size(); i++) {
		Score currentScore = Scores[i];

		if (currentScore.position == "1") {
			for (int p = 0; p < players.size(); p++) {
				Player currentPlayer = players[p];

				if (currentScore.idOfPlayer == currentPlayer.id) {
					countries[currentPlayer.country]++;
				}
			}
		}
	}

	cout << "\nWyniki poszczegolnych panstw: \n";
	for (map<string, int>::iterator iterator = countries.begin(); iterator != countries.end(); iterator++) {
		cout << iterator->first << ":" << iterator->second << "\n";
	}

	cout << "\nZawodnicy z wieksza nota niz 450 \n";
	for (int x = 0; x < idsOfPlayerWithMoreThan450Points.size(); x++) {
		for (int p = 0; p < players.size(); p++) {
			if (idsOfPlayerWithMoreThan450Points[x] == atoi(players[p].id.c_str())) {
				cout << players[p].name << "\n";
			}
		}
	}

	cout << "\nIlosc zwyciestw Malysza w Zakopanem: ";
	int idMalysza = 136;
	int iloscZwyciestw = 0;
	map<string, int[2]> analizaSezonow;

	for (int i = 0; i < Scores.size(); i++) {
		if (Scores[i].position == "1") {
			for (int j = 0; j < competitions.size(); j++) {
				if (competitions[j].name_of_place == "Zakopane" && competitions[j].id == Scores[i].idOfCompetition) {
					iloscZwyciestw++;
				}
			}
		}

		/*for (int j = 0; j < competitions.size(); j++) {
			if (Scores[i].idOfCompetition == competitions[j].id) {
				analizaSezonow[competitions[j].season][0] = (analizaSezonow[competitions[j].season][0] + atoi(Scores[i].firstJump.c_str())) / 2;
				analizaSezonow[competitions[j].season][1] = (analizaSezonow[competitions[j].season][1] + atoi(Scores[i].secondJump.c_str())) / 2;
			}
		}*/
	}
	cout << iloscZwyciestw << "\n";

	system("pause");
	return 0;
}

