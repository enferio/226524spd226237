#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct zadanie
{
	int r;
	int p;
	int q;
	int nr;

	zadanie(int t1, int t2, int t3, int _nr)
	{
		r=t1;
		p=t2;
		q=t3;
		nr=_nr;
	}
};

int main()
{
	int cmax=0;
	int t=1; //czas poczatkowy
	// Tworzymy wyrazenie lambda zeby porównaæ elementy
	auto porownaj = [](zadanie left, zadanie right) { return (left.r) > (right.r);}; //wyrazenie lambda, funktor
	priority_queue<zadanie, vector<zadanie>, decltype(porownaj)> nieuporzadkowany(porownaj); //adapter kolejki priorytetowej

	fstream plik;
	plik.open( "SCHRAGE1.DAT", ios::in );
	if( plik.good() )
	{
		int n;
		plik >> n;
		int czas_1, czas_2, czas_3, nr;
		for (int i=0; i<n; ++i)
		{
			plik >> czas_1;
			plik >> czas_2;
			plik >> czas_3;
			nr=i+1;
			nieuporzadkowany.push(zadanie(czas_1, czas_2, czas_3, nr));
		}

		plik.close();

        int tab[n];
        int tmp=0;

		auto porownaj = [](zadanie left, zadanie right) { return (left.q) < (right.q);}; //wyrazenie lambda, funktor
		priority_queue<zadanie, vector<zadanie>, decltype(porownaj)> gotowe(porownaj); //adapter kolejki priorytetowej

		while(!nieuporzadkowany.empty() || !gotowe.empty())
		{
			if(!nieuporzadkowany.empty()) //zabezpieczenie przed braniem top z pustej kolejki
			{
				zadanie q=nieuporzadkowany.top();
				while(!nieuporzadkowany.empty() && q.r<=t) // budowanie zbioru uszeregowanego
				{                                     //czas przygotowania r pozwala na rozpoczêcie wykonywania zadania do czasu t
					zadanie e=nieuporzadkowany.top();
					gotowe.push(e);
					nieuporzadkowany.pop();
					q=nieuporzadkowany.top();
				}
			}
			if(gotowe.empty() && !nieuporzadkowany.empty()) // nie ma zadañ gotowych do uszeregowania
			{
				t=nieuporzadkowany.top().r;
			}
			else
			{
				zadanie najdluzsze=gotowe.top();
				t=t+najdluzsze.p;
                tab[tmp]=najdluzsze.nr;
                tmp=tmp+1;
				cmax=max(cmax,t+najdluzsze.q);
				gotowe.pop();
			}
		}
		cout<<"Cmax: "<<cmax<<endl;
		for(int i=0;i<n;i++)
        {
            cout<<"Nr:"<<tab[i]<<" ";
        }
	}
	else
	{
		cout << "Error! Nie udalo otworzyc sie pliku!" << endl;
	}

	return(0);
}
