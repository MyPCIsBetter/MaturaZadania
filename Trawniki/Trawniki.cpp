// Trawniki.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	int objetoscWywozonejTrawy = 15;
	int objetoscKoszonejTrawy = 600;
	float oIleZmiejszaSieObjetoscTrawy = 0.03;
	int iloscDni = 30 + 31 + 30 + 31 + 31 + 30 + 30;
	int iloscWozow = 30;

	float stan9kwietniaPrzedNoca;

	float aktualnaObjetoscTrawy = 10000;
	float objetoscZDniaPoprzedniego = aktualnaObjetoscTrawy;
	bool objetoscSprawdzona1 = false;
	bool objetoscSprawdzona2 = false;

	for (int d = 1; d <= iloscDni; d++) {
		if (aktualnaObjetoscTrawy - objetoscZDniaPoprzedniego > 0 && !objetoscSprawdzona1) {
			cout << "Dzien " << d << ": objetosc trawy przewyzsza objetosc z dnia poprzedniego\n";
			objetoscSprawdzona1 = true;
		}
		if (aktualnaObjetoscTrawy == objetoscZDniaPoprzedniego && objetoscSprawdzona2) {
			cout << "Dzien " << d << ": objetosc z dnia poprzedniego = objetosc dzisiaj";
			objetoscSprawdzona2 = true;
		}
		objetoscZDniaPoprzedniego = aktualnaObjetoscTrawy;

		if (d == 101) {
			cout << "Ilosc trawy w 101 dniu.";
		}

		if (d == 10) {
			cout << "W nocy z 9 na 10 kwietnia zmiana wynosi: " << (aktualnaObjetoscTrawy - stan9kwietniaPrzedNoca) <<endl;
		}

		aktualnaObjetoscTrawy -= iloscWozow * 15;

		aktualnaObjetoscTrawy += 600;

		if (d == 12) {
			cout << "Ilosc wozow potrzebna zeby wywiezc cala trawe ("<< aktualnaObjetoscTrawy <<"m3): " << floor(aktualnaObjetoscTrawy / 15.0) <<endl;
		}

		if (d == 9) {
			stan9kwietniaPrzedNoca = aktualnaObjetoscTrawy;
		}
		aktualnaObjetoscTrawy -= floor(aktualnaObjetoscTrawy * oIleZmiejszaSieObjetoscTrawy);
	}

	system("pause");
	return 0;
}

