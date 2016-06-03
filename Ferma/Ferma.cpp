// Ferma.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include <math.h>
#include <string>
using namespace std;


int main()
{
	int liczbaKur = 200;
	float cenaPaszy = 1.9;
	float iloscPaszyZjadanaPrzezJednaKure = 0.2;
	int okresHodowli = 180;
	float cenaJajka = 0.9;
	//int odliczanieDoNiedzieli = 1; //poniedzialek
	//float budzetPaniBinarnej = 0;
	float wydanePieniedze = 0;
	float realnyZysk = 0;
	int iloscSprawdzenLiczbyKur = 0;
	bool pierwszePrzekroczenie1500RealnegoZysku = true;
	float kwotaWydanaNaPasze = 0;

	for (int dzien = 1; dzien <= 180; dzien++) {
		//dzien 7 = niedziela

		if (dzien % 30 == 0) {
			int kupioneKury = floor(liczbaKur * 0.2);
			liczbaKur += kupioneKury;
			realnyZysk -= kupioneKury * 18;
			wydanePieniedze += kupioneKury * 18;
		}

		if (liczbaKur == 200 && dzien != 1) {
			if (iloscSprawdzenLiczbyKur == 1) {
				cout << "200 sztuk. Dzien " << dzien << ", RANO" << endl;
			}
			iloscSprawdzenLiczbyKur++;
		}

		if(dzien % 7 != 0){ // z wyjatkiem niedziel
			realnyZysk += liczbaKur * cenaJajka;
		}

		if (liczbaKur == 200) {
			if (iloscSprawdzenLiczbyKur == 1) {
				cout << "200 sztuk. Dzien " << dzien << ", poludnie" << endl;
			}
			iloscSprawdzenLiczbyKur++;
		}

		if (dzien % 2 != 0) {
			liczbaKur -= 2;
		}

		if (liczbaKur == 200) {
			if (iloscSprawdzenLiczbyKur == 1) {
				cout << "200 sztuk. Dzien " << dzien << ", wieczor" << endl;
			}
			iloscSprawdzenLiczbyKur++;
		}

		wydanePieniedze += cenaPaszy * liczbaKur * iloscPaszyZjadanaPrzezJednaKure;
		kwotaWydanaNaPasze += cenaPaszy * liczbaKur * iloscPaszyZjadanaPrzezJednaKure;
		realnyZysk -= cenaPaszy * liczbaKur * iloscPaszyZjadanaPrzezJednaKure;

		cout << "dzien: " << dzien << " kury: " << liczbaKur << " realnyZysk: " << realnyZysk << endl;

		if (pierwszePrzekroczenie1500RealnegoZysku && realnyZysk > 1500) {
			cout << "realny zysk w dniu " << dzien << " przekracza 1500. Wynosi: " <<realnyZysk << " \n";
			pierwszePrzekroczenie1500RealnegoZysku = false;
		}
	}
	cout << "Laczna wydana kwota: " << kwotaWydanaNaPasze << endl;

	cout << "Realny zysk po 180: " << realnyZysk << endl;

	system("pause");
    return 0;
}

