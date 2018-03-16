#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

struct Zadanie {
	int r;   //termin dostepnosci
	int p;	//czas obslugi zadania
	int q;  //czas dostarczenia
	int nr; // nr zadania
};

int l_zadan;
Zadanie tab_zad[1000];
int maxx = 0;
int Smax[1000]; // tablica momentow rozpoczec zadan
int Cmax[1000]; // tablica momentow zakonczen zadan

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
		else {plik >> tab_zad[i].r >> tab_zad[i].p >>tab_zad[i].q; tab_zad[i].nr=i;}

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

int licz_cmax()
{
    for (int i = 1; i <= l_zadan; i++)
    {
		Smax[i] = max(Smax[i - 1], tab_zad[i].r) + tab_zad[i].p; //wyznaczamy odpowiedni termin rozpoczecia
		Cmax[i] = Smax[i] + tab_zad[i].q; //wyznaczamy odpowiedni zakonczenia wykonanych zadan
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
	return maxx;
}

void zapisz(Zadanie *tab)
{
    fstream plik;

     for(int i=1; i<=l_zadan;i++)
     {
        tab_zad[i].r=tab[i].r;
        tab_zad[i].p=tab[i].p;
        tab_zad[i].q=tab[i].q;
     }

    plik.open("wyniki.txt", ios::out | ios::app);
    if(plik.good() == true)
    {
        for(int i=1; i<=l_zadan;i++)
        {
            plik<<tab[i].nr<<" ";
        }
        plik<<"Cmax="<<licz_cmax();
        plik<<endl;
        plik.close();
    }
};

void permutacja(Zadanie *tab, int l)
{

    int i,j=0;
    if (l == l_zadan){
        zapisz(tab);
     }
    else
    {
       for (i = l; i <= l_zadan; i++)
       {
          swap(tab[l],tab[i]);
          permutacja(tab, l+1);
          swap(tab[l],tab[i]);
       }
   }
}

int main()
{
	czyt_plik("JACK1.DAT",l_zadan);
	pokaz_tab();
	permutacja(tab_zad, 1);

    return 0;
}

