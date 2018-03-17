#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>

using namespace std;


struct Zadanie {
	int t1;
	int t2;
	int nr;
    friend ostream & operator<< (ostream &wyjscie, const Zadanie &z);
    };

int i,j,Cmaxx;
int l_zadan;
int l_maszyn;
Zadanie tab_czas[50];
Zadanie tab_rozp[50];
Zadanie tab_zak[50];

ostream & operator<< (ostream &wyjscie, const Zadanie &z) {
   return wyjscie <<z.t1 << "\t"<<z.t2<<endl;
 }

 bool czyt_plik(string naz_pliku, int & l_zadan, int & l_maszyn)
{
	ifstream plik;
	plik.open(naz_pliku.c_str());
	if (!plik.good())
    {
		return false;
	}
    plik>>l_zadan>>l_maszyn;
    for(int i=1;i<=l_zadan;i++)
    {
        plik>>tab_czas[i].t1>>tab_czas[i].t2;
        tab_czas[i].nr=i;
    }
	plik.close();
	return true;
}

void wyswietl()
{
    for(i=1;i<=l_zadan;i++)       //petle wczytujace dane z pliku do tablicy dwuwymiarowej
    {
        cout<<tab_czas[i]; //wyswietlenie
    }
}
int licz_cmax()
{
    tab_rozp[0].t1=0;

//pierwsza kolumna tablicy rozpoczec
for(i=1;i<l_zadan;i++)
{
    tab_rozp[i].t1=tab_rozp[i-1].t1+tab_czas[i].t1;
}


//pierwszy wiersz tablicy rozpoczec

for(j=0;j<l_maszyn;j++)
{
    tab_rozp[j].t2=tab_rozp[j].t1+tab_czas[j+1].t1;
}

//pozostale elementy tablicy rozpoczec

for(i=1;i<l_zadan;i++)        //rozpoczencie zadania to max z zakonczenia poprzedniego zadania na tej samej maszynie
{                       // i zakonczenia tego samego zadania na poprzedniej maszynie
        tab_rozp[i].t2=max((tab_rozp[i].t1+tab_czas[i+1].t1),(tab_rozp[i-1].t2+tab_czas[i].t2));
}

//tablica zakonczen-dodanie tablicy czasow i tablicy rozpoczec

for(i=0;i<l_zadan;i++)
{
    tab_zak[i].t1=tab_czas[i+1].t1+tab_rozp[i].t1;
    tab_zak[i].t2=tab_czas[i+1].t2+tab_rozp[i].t2;
}
 return tab_zak[l_zadan-1].t2;
}
 void zapisz(Zadanie *tab)
{
    fstream plik;
     for(int i=1; i<=l_zadan;i++)
     {
        tab_czas[i].t1=tab[i].t1;
        tab_czas[i].t2=tab[i].t2;
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
}

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

void johnson()
{
    int licznik=0;
    for(int i=1;i<=l_zadan;i++)
    {
        if(tab_czas[i].t1 < tab_czas[i].t2)
            licznik+=1;
    }

    Zadanie *N1 = new Zadanie [licznik]; //alokacja pamieci
    Zadanie *N2 = new Zadanie [l_zadan-licznik]; //alokacja pamieci
    int temp1=0;
    int temp2=0;

    for (int i = 1; i <= l_zadan; ++i)
    {
        if(tab_czas[i].t1 < tab_czas[i].t2)
        {
            N1[temp1] = tab_czas[i]; temp1+=1;
        }
        else {N2[temp2] = tab_czas[i]; temp2+=1; }
    }


    for (int i=0; i<temp1-1; i++)
        for (int j=0; j<temp1-1; j++)
            if (N1[j].t1>N1[j+1].t1)
                swap(N1[j], N1[j+1]);


     for (int i=0; i<temp2-1; i++)
        for (int j=0; j<temp2-1; j++)
            if (N2[j].t2>N2[j+1].t2)
                swap(N2[j], N2[j+1]);


    int tmp1 = temp1;
    int bb=0;
    while(tmp1>0)
    {
        tab_czas[bb]=N1[bb];
        ++bb;
        --tmp1;
    }

    int tmp2 = temp2;
    int cc=0;
    int i=temp1;

    while(tmp2>0)
    {
        tab_czas[i]=N2[cc];
        ++i;
        ++cc;
        --tmp2;
    }
 cout<<"Cmax: "<<licz_cmax();
}

int main()
{
    czyt_plik("JOH2.DAT",l_zadan, l_maszyn);
    wyswietl();
    //permutacja(tab_czas, 1);
    johnson();

return 0;
}

