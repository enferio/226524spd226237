#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

struct Zadanie {
	int r;   //termin dostepnosci
	int p;	//czas obslugi zadania
	int q;  //czas dostarczenia
};

int l_zadan;
Zadanie tab_zad[1000];

bool czyt_plik(string naz_pliku, int & l_zadan)
{
	ifstream plik;
	plik.open(naz_pliku.c_str());
	if (!plik.good())
    {
		return false;
	}
    int i=0;
	while (i <= l_zadan)
	{
        if(l_zadan == 0)
        {
			plik >> l_zadan;
		}
		else plik >> tab_zad[i].r >> tab_zad[i].p >>tab_zad[i].q;

		i++;
	}
	plik.close();
	return true;
}

void pokaz_tab()
{
    cout << "r\tp\tq\n";
	for (int i = 1; i <= l_zadan; i++)
    {
		cout << tab_zad[i].r << "\t" << tab_zad[i].p << "\t" << tab_zad[i].q << endl;
    }
}

void sortR()
{
	int tmp = l_zadan;
	Zadanie zad;
	while (tmp > 1)
    {
        for (int i = 1; i < tmp; i++)
        {
			if (tab_zad[i].r > tab_zad[i + 1].r)
            {
                zad = tab_zad[i];
                tab_zad[i] = tab_zad[i + 1];
                tab_zad[i + 1] = zad;
            }
		}
		tmp = tmp -1;
	}
}

int main()
{
    int maxx = 0;
	int Smax[1000];
	int Cmax[1000];

	czyt_plik("JACK1.DAT",l_zadan);
	sortR();
	pokaz_tab();

	for (int i = 1; i <= l_zadan; i++)
    {
		Smax[i] = max(Smax[i - 1], tab_zad[i].r) + tab_zad[i].p; //wyznaczamy odpowiedni termin rozpoczecia
		Cmax[i] = Smax[i] + tab_zad[i].q; //wyznaczamy odpowiedni termin zakonczenia wykonanych zadan
	}

	for (int i = 1; i <= l_zadan; i++)
    {
		int zmienna[7];
		zmienna[i] = Cmax[i];
		if (Cmax[i]>zmienna[i-1])
        {
            zmienna[i] = Cmax[i];
            maxx = zmienna[i];
        }

	}

	cout << "\nCmax = " << maxx << endl; // czas skonczenia ostatniego zadania

    return 0;
}

