#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <string>
#include <iomanip>
using namespace std;

struct Zadanie
{
	int t1;
	int t2;
	int t3;
	int sum_t;
	int nr;

	void New(int a,int s,int d,int f, int g)
    {
        t1=a; t2=b; t3=c; sum_t=d;nr=e;
    }
};


int licz_cmax(vector <Zadanie> &tab,int l_zad, int l_masz)
{
    int tab_rozp[l_zad][l_masz];
    int tab_zak[l_zad][l_masz];
    int tab_czas[l_zad][l_masz];

     for(int i=0;i<l_zad;i++)
     {
        for(int j=0;j<l_masz;j++)
        {
            if(j==0)
                tab_czas[i][j]=tab[i].t1;
            if(j==1)
                tab_czas[i][j]=tab[i].t2;
            if(j==2)
                tab_czas[i][j]=tab[i].t3;
        }
     }

    for(int i=0;i<l_zad;i++)
    {
        for(int j=0;j<l_masz;j++)
        {
            if(j==0&&i==0)
                tab_rozp[i][j]=0;
            if(j==0&&i>0)
                tab_rozp[i][j]=tab_czas[i-1][j]+tab_rozp[i-1][j];
            if(j>0&&i>0)
                if((tab_czas[i-1][j]+tab_rozp[i-1][j])>(tab_rozp[i][j-1]+tab_czas[i][j-1]))
                    tab_rozp[i][j]=tab_czas[i-1][j]+tab_rozp[i-1][j];
                else
                    tab_rozp[i][j]=tab_rozp[i][j-1]+tab_czas[i][j-1];

            if(j>0&&i==0)
                tab_rozp[i][j]=tab_czas[i][j-1]+tab_rozp[i][j-1];
        }
     }


     for(int i=0;i<l_zad;i++)
     {
        for(int j=0;j<l_masz;j++)
        {
                tab_zak[i][j]=tab_czas[i][j]+tab_rozp[i][j];
        }
     }

return tab_zak[l_zad-1][l_masz-1];
}


int tabu_search(vector<Zadanie>&tab,int l_zad, int l_masz)
{
    int C_max;
    int czas;
    int l1 ;
    int l2 ;

    vector<Zadanie> pomocniczy;
    pomocniczy=tab;
    C_max=licz_cmax(tab,l_zad,l_masz);
    vector <vector< Zadanie>> lista_tabu;

    lista_tabu.push_back(tab);
    cout<<tab[0].nr<<endl;
    long int strong=1;
    for(int i=l_zad;i>1;i--)
		strong*=i;

/**********************************************************************************************************************************
Generowanie sasiedztwa odbywa siê za pomoca zmiany dwóch elementów w tablicy od tego rozwiazania poczatkowego,
a w nastêpnych ruchach od poprzedniego.
**********************************************************************************************************************************/

    int x=0;
    int temp=0;
    int temp1=0;
    for (int j = 0; j < 1000; j++) //petla czasowa
    {
        for (int i = 1; i < tab.size(); i++) //petla generujaca i permutacji w danym sasiedztwie
        {

            if (x == strong)
				break;
            l1 = rand()%l_zad;
            l2 = rand()%l_zad;
            while (l1 == l2)
				l2 = std::rand()%l_zad;
            swap(tab[l1], tab[l2]);

/*************************************************************************************************************************
pod swapem tworzymy mechanizm sprawdzania czy dana kolejnosc juz jest w wektorze zabronien.
**************************************************************************************************************************************/
            temp=0;
            temp1=0;
            for(int k=0;k<lista_tabu.size();k++)
            {
                for(int w=0;w<l_zad;w++)
                {
                    if(lista_tabu[k][w].nr==tab[w].nr)
                        temp=temp+1;
                }
            if(temp==l_zad)
                temp1=1;
            }

            if (temp1==0)
            {
                lista_tabu.push_back(tab);         // £adujemy ta kolejnoœæ do wektora zabronien.
                x++;                               // Inkrementujemy licznik z, poniewa¿ nowa kolejnoœæ zosta³¹ znaleziona (z++;)
                czas=licz_cmax(tab,l_zad,l_masz);
/************************************************************************************************************
Obliczamy Cmaxa i sprawdzamy czy jego wartoœæ jest mniejsza od poprzedniej. If tak to zapamietujemy go
**************************************************************************************************************/
                if(czas<C_max)
                    C_max=czas;

            pomocniczy=tab;

            }
		}
    }

return C_max;
}

int main()
{
    int n=0,m=0,cmaxx=0;
    int czas1, czas2, czas3;

    fstream plik;
	plik.open("NEH1.DAT", ios::in);
	if(plik.good()==false)
    {
        cout<<"Blad otwarcia pliku";
    }
    else
    {
        int suma;
        plik>>n;
        plik>>m;

        vector<Zadanie>zadaniaa;
        for (int i=0;i<n;++i)
        {
            plik>>czas1;
            plik>>czas2;
            plik>>czas3;
            suma=czas1+czas2+czas3;
            Zadanie zadd;
            zadd.New(czas1,czas2,czas3,suma,i+1);

            zadaniaa.push_back(zadd);
        }

        plik.close();

        cmaxx=tabu_search(zadaniaa,n,m);
        cout<<"Cmax:   "<<cmaxx<<endl;
    }
};
