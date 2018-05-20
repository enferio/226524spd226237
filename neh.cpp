#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <vector>


using namespace std;

int n,m;
int i,j,Cmax;
int tab_cmax[100];

int NEH(int **tab_czas, int **tab_czas_, vector <int> dane)
{

		for (int a = 0; a < dane.size(); a++) {
			for (int b = 0; b < m; b++) {
				tab_czas_[a][b] = tab_czas[dane[a]][b];
			}
		}
		int **tab_rozp = new int *[dane.size()]; //alokacja pamieci
		for (i = 0; i < dane.size(); ++i)
		{
			tab_rozp[i] = new int[m]; //alokacja pamieci
			for (j = 0; j < m; ++j) //wpisanie wartosci do tablicy
				tab_rozp[i][j] = 0;
		}

		int **tab_zak = new int *[dane.size()]; //alokacja pamieci
		for (i = 0; i < dane.size(); ++i)
		{
			tab_zak[i] = new int[m]; //alokacja pamieci
			for (j = 0; j < m; ++j) //wpisanie wartosci do tablicy
				tab_zak[i][j] = 0;
		}

		//pierwsza kolumna tablicy rozpoczec

		tab_rozp[0][0] = 0; // w sumie zbedne bo tworzac tablice dynamicznie przypisuje im zera

		for (i = 1; i < dane.size(); i++)
		{
			tab_rozp[i][0] = tab_rozp[i - 1][0] + tab_czas_[i - 1][0];
		}

		//pierwszy wiersz tablicy rozpoczec

		for (j = 1; j < m; j++)
		{
			tab_rozp[0][j] = tab_rozp[0][j - 1] + tab_czas_[0][j - 1];
		}

		//pozostale elementy tablicy rozpoczec

		for (i = 1; i < dane.size(); i++)    //rozpoczencie zadania to max z zakonczenia poprzedniego zadania na tej samej maszynie
		{                                   // i zakonczenia tego samego zadania na poprzedniej maszynie
			for (j = 1; j < m; j++)
			{
				tab_rozp[i][j] = max((tab_rozp[i - 1][j] + tab_czas_[i - 1][j]), (tab_rozp[i][j - 1] + tab_czas_[i][j - 1]));
			}
		}

		//tablica zakonczen-dodanie tablicy czasow i tablicy rozpoczec

		for (i = 0; i < dane.size(); i++)
		{
			for (j = 0; j < m; j++)
			{
				tab_zak[i][j] = tab_czas_[i][j] + tab_rozp[i][j];
			}
		}

		//Wypisanie Cmax

		cout << endl << "Cmax: " << tab_zak[dane.size() - 1][m - 1] << endl << endl;

		delete[] tab_rozp;

		return tab_zak[dane.size() - 1][m - 1];

}

int main(){

    fstream plik;
    plik.open("NEH1.DAT", ios::in);
    if(plik.good()==false)
    {
        cout<<"Blad otwarcia pliku";
    }
	else
	{
		int najmn_cmax = 0;
		plik >> n >> m; //wczytanie n i m z pliku
		cout << "Liczba zadan: " << n << endl;
		cout << "Liczba maszyn: " << m << endl << endl;
		cout << "Tablica czasow: " << endl;

		// dynamiczne tworzenie tablic: czasow, ozpoczec i zakonczen
		int **tab_czas = new int *[n]; //alokacja pamieci
		for (i = 0; i < n; ++i)
		{
			tab_czas[i] = new int[m]; //alokacja pamieci
			for (j = 0; j < m; ++j) //wpisanie wartosci do tablicy
				tab_czas[i][j] = 0;
		}

	for (i = 0; i < n; i++)       //petle wczytujace dane z pliku do tablicy dwuwymiarowej
		{
			for (j = 0; j < m; j++)
			{
				plik >> tab_czas[i][j];
				//cout << tab_czas[i][j] << "   "; //wyswietlenie
			}
			//cout << endl;
		}

		//sumy i indeksy
		int * tab_sum = new int[n];
		int * tab_index = new int[n];

		int **tab_czas2 = new int *[n]; //tablica potrzebna nizej do przypisywania jej tych wierszy tab_czas
		for (i = 0; i < n; ++i)         //ktore wskazuje wektor
		{
			tab_czas2[i] = new int[m]; //alokacja pamieci
			for (j = 0; j < m; ++j) //wpisanie wartosci do tablicy
				tab_czas2[i][j] = 0;
		}

		int suma = 0;
		int index = 0;

		for (i = 0; i < n; i++) //Obliczenie sum
		{
			for (j = 0; j < m; j++)
			{
				suma += tab_czas[i][j];
			}
			tab_sum[i] = suma;
			suma = 0;
		}

		//wyswietenie tablicy sum
/*
		for (i = 0; i < n; i++)
		{
			cout << tab_sum[i] << endl;
		}

*/
		for (int k = 0; k < n; k++) //tworzenie tablicy z indeksami
		{
			for (i = 1; i < n; i++)
			{
				if (tab_sum[i - 1] < tab_sum[i])
				{
					index = i;
				}
			}
/*
			cout << endl << "INDEX: " << index << endl;

*/			tab_index[k] = index;
			tab_sum[index] = 0;
			index = 0;
		} //koniec

/*		cout << endl << "TABLICA INDEXOW: " << endl;
		for (i = 0; i < n; i++)
		{
			cout << tab_index[i] << endl;
		}
*/
		vector <int> dane;

		dane.push_back(tab_index[0]);
		dane.push_back(tab_index[1]);


//NEH


		tab_cmax[0] = NEH(tab_czas, tab_czas2, dane);
		if (dane.size() == 2) {
			swap(dane[0], dane[1]);
		}
		else { cout << "Blad" << endl; }

		tab_cmax[1] = NEH(tab_czas, tab_czas2, dane);

		if (dane.size() == 2) {
			if (tab_cmax[1] < tab_cmax[0]) { //ustawienie kolejnosci w wektorze tak jak wskazuja wyliczone cmaxy
				swap(dane[0], dane[1]);
			}
		}

		for (int i = 2; i < n; i++) {
			for (int j = 0; j <= i; j++) {
				dane.insert(dane.begin() + j, tab_index[i]);
				tab_cmax[j]=NEH(tab_czas, tab_czas2, dane);
				dane.erase(dane.begin() + j);
			}
			for (int c = 0; c <= dane.size(); c++) { cout << "tab_cmax: " << tab_cmax[c] << " "; } cout << endl;
		         najmn_cmax = 0;
			for (int a = 1; a <= dane.size(); a++) {
				//najmn_cmax = 0;
				if (tab_cmax[a] < tab_cmax[a - 1])
					najmn_cmax = a;
				if (a == dane.size())
					cout << "Najmn cmax: " << tab_cmax[najmn_cmax] << endl;
			}
			dane.insert(dane.begin() + najmn_cmax, tab_index[i]);

		}

//		cout << "Najmn cmax: " << tab_cmax[najmn_cmax] << endl;
//		cout << "Wektor wynikowy" << endl;
//		for (size_t i = 0; i < dane.size(); i++)
//			cout << endl << dane[i];


    cout << endl <<endl << "Ostateczne Cmax: " << tab_cmax[najmn_cmax] << endl<<endl;

	}
	system("PAUSE");
return 0;
}
