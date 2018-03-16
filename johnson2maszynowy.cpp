#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>

using namespace std;

int n,m,j,Cmax;

int main(){

    fstream plik;
    plik.open("JOH2.DAT", ios::in);
    if(plik.good()==false)
    {
        cout<<"Blad otwarcia pliku";
    }
    else
    {
        plik>>n>>m; //wczytanie n i m z pliku
        cout<<"Liczba zadan: "<<n<<endl;
        cout<<"Liczba maszyn: "<<m<<endl<<endl;
        cout<<"Tablica czasow: "<<endl;

		// dynamiczne tworzenie tablic: czasow, rozpoczec i zakonczen
		double **tab_czas = new double *[n]; //alokacja pamieci
		for (int i = 0; i < n; ++i)
		{
			tab_czas[i] = new double[m]; //alokacja pamieci
			for (int j = 0; j < m; ++j) //wpisanie wartosci do tablicy
				tab_czas[i][j] = 0;
		}

		double **tab_rozp = new double *[n]; //alokacja pamieci
		for (int i = 0; i < n; ++i)
		{
			tab_rozp[i] = new double[m]; //alokacja pamieci
			for (int j = 0; j < m; ++j) //wpisanie wartosci do tablicy
				tab_rozp[i][j] = 0;
		}

		double **tab_zak = new double *[n]; //alokacja pamieci
		for (int i = 0; i < n; ++i)
		{
			tab_zak[i] = new double[m]; //alokacja pamieci
			for (int j = 0; j < m; ++j) //wpisanie wartosci do tablicy
				tab_zak[i][j] = 0;
		}

    for(int i=0;i<n;i++)       //petle wczytujace dane z pliku do tablicy dwuwymiarowej
    {
        for(j=0;j<m;j++)
        {
            plik >> tab_czas[i][j];
            cout<<tab_czas[i][j]<<"   "; //wyswietlenie
        }
        cout<<endl;
    }



 int licznik=0;  // zmienna ktora powie nam ile wierszy bedziemy mieli w macierzy N1
    for(int i=0;i<n;i++)
    {
        for(int j=1;j<2;j++)
        {
            if(tab_czas[i][j-1] < tab_czas[i][j])
                licznik+=1;
        }
    }


        double **N1 = new double *[licznik]; //alokacja pamieci. Macierz dobrana na podstawie tab_czas
		for (int i = 0; i < n; ++i)
		{
			N1[i] = new double[m]; //alokacja pamieci
			for (int j = 0; j < m; ++j) //wpisanie wartosci do tablicy
				N1[i][j] = 0;
		}

		double **N2 = new double *[n-licznik]; //alokacja pamieci. Macierz dobrana na podstawie tab_czas
		for (int i = 0; i < n; ++i)
		{
			N2[i] = new double[m]; //alokacja pamieci
			for (int j = 0; j < m; ++j) //wpisanie wartosci do tablicy
				N2[i][j] = 0;
		}

    int temp1=0;
    int temp2=0;

    for (int i = 0; i < n; ++i)
    {
        for(int j=1;j<m;j++)
        {
            if(tab_czas[i][j-1] < tab_czas[i][j])  // jesli czas na drugiej wirtualnej maszynie jest wiekszy dla danego zadania
            {
                N1[temp1][j-1] = tab_czas[i][j-1];
                N1[temp1][j] = tab_czas[i][j];
                temp1+=1;
            }
            else
            {
                N2[temp2][j-1] = tab_czas[i][j-1];
                N2[temp2][j] = tab_czas[i][j];
                temp2+=1;
            }
        }
    }


    for (int i=0; i<temp1-1; i++) // sortowanie macierzy N1
        for (int j=0; j<m-1; j++)
            if (N1[i][j]>N1[i+1][j])
            {
                swap(N1[i][j], N1[i+1][j]);
                swap(N1[i][j+1], N1[i+1][j+1]);
            }

     for (int i=0; i<temp2-1; i++) // sortowanie macierzy N2
        for (int j=0; j<m-1; j++)
            if (N2[i][j+1]<N2[i+1][j+1])
            {
                swap(N2[i][j], N2[i+1][j]);
                swap(N2[i][j+1], N2[i+1][j+1]);
            }


    for(int i=0;i<temp1;i++)
    {
        for(int j=0;j<m;j++)
        {
            tab_czas[i][j]=N1[i][j];
        }
    }
    int k=0;
    for(int i = temp1;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            tab_czas[i][j]=N2[k][j];
        }
        k+=1;
    }

//pierwsza kolumna tablicy rozpoczec

tab_rozp[0][0]=0;

for(int i=1;i<n;i++)
{
    tab_rozp[i][0]=tab_rozp[i-1][0]+tab_czas[i-1][0];
}

//pierwszy wiersz tablicy rozpoczec

for(j=1;j<m;j++)
{
    tab_rozp[0][j]=tab_rozp[0][j-1]+tab_czas[0][j-1];
}

//pozostale elementy tablicy rozpoczec

for(int i=1;i<n;i++)        //rozpoczencie zadania to
{                       //zakonczenie poprzedniego zadania na tej samej maszynie +  czas trwania poprzedniego zadanie na tej samej maszynie
    for(j=1;j<m;j++)    // lub zakonczenia tego samego zadania na poprzedniej maszynie + czas trwania tego samego zadania na poprzedniej maszynie
    {
        tab_rozp[i][j]=max((tab_rozp[i-1][j]+tab_czas[i-1][j]),(tab_rozp[i][j-1]+tab_czas[i][j-1]));
    }
}



cout<<endl<<"Tablica rozpoczec: "<<endl;

for(int i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            cout<<tab_rozp[i][j]<<"   "; //wyswietlenie tablicy rozpoczec
        }
        cout<<endl;
    }

//tablica zakonczen-dodanie tablicy czasow i tablicy rozpoczec

for(int i=0;i<n;i++)
{
    for(j=0;j<m;j++)
    {
        tab_zak[i][j]=tab_czas[i][j]+tab_rozp[i][j];
    }
}

cout<<endl<<"Tablica zakonczen: "<<endl;

for(int i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            cout<<tab_zak[i][j]<<"   "; //wyswietlenie tablicy zakonczen
        }
        cout<<endl;
    }

//Wypisanie Cmax

cout<<endl<<"Cmax: "<<tab_zak[n-1][m-1]<<endl<<endl;
    }


return 0;
}
