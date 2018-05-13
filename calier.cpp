#include <iostream>
#include <cmath>
#include <queue>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <climits>

using namespace std;
bool flaga = false;
vector<int> program;

void WczytajDane (vector<vector<int>> &nieuporzadkowany)
{
    int n; //liczba zadań
    fstream plik;
    plik.open("SCHRAGE10.DAT", ios_base::in);
    plik>>n;
    vector<int> RPG[n];

    int czas_1, czas_2, czas_3;
    for (int i=0; i<n; ++i)
    {
        plik >> czas_1;
        plik >> czas_2;
        plik >> czas_3;
        RPG[i].push_back(czas_1);
        RPG[i].push_back(czas_2);
        RPG[i].push_back(czas_3);
        nieuporzadkowany.push_back(RPG[i]);
    }
}


int max_rpg(const vector<vector<int>> &nieuporzadkowany, int n) // zwraca indeks najwiekszego R P lub Q
{
    vector<int> R;

    for(int i=0; i<nieuporzadkowany.size(); ++i)
    {
        R.push_back(nieuporzadkowany[i][n]); // pierwsze to numer RPG drugie to R P lub Q
        //cout<<R[i]<<" "<<endl; // wyswietla po kolei
    }
    return distance(R.begin(), max_element(R.begin(), R.end()));

}

int min_rpg(const vector<vector<int>> &nieuporzadkowany, int n) // zwraca indeks najmniejszgo R P lub Q
{
    vector<int> R;
    for(int i=0; i<nieuporzadkowany.size(); ++i)
    {
        R.push_back(nieuporzadkowany[i][n]); // pierwsze to numer RPG drugie to R P lub Q
        //cout<<R[i]<<" "<<endl; // wyswietla po kolei
    }
    return distance(begin(R),(min_element(begin(R),end(R))));
}

int min_wartosc(const vector<vector<int>> &nieuporzadkowany, int n)
{
    return nieuporzadkowany[min_rpg(nieuporzadkowany,n)][n];

}

int max_wartosc(const vector<vector<int>> &nieuporzadkowany, int n)
{
    return nieuporzadkowany[max_rpg(nieuporzadkowany,n)][n];
}

int Schrage(vector<vector<int>>nieuporzadkowany)
{
    vector<vector<int>> gotowy;
    vector<int> RPG;
    vector<vector<int>>pi;
    int t=0,k=0,Cmax=0,e=0;
    while (!gotowy.empty() || !nieuporzadkowany.empty())
    {
        while(!nieuporzadkowany.empty() && min_wartosc(nieuporzadkowany,0)<=t)
        {
            e=min_rpg(nieuporzadkowany,0);
            gotowy.push_back(nieuporzadkowany[e]);
            nieuporzadkowany.erase(nieuporzadkowany.begin()+e);
        }

        if(gotowy.empty())
        {
            t=min_wartosc(nieuporzadkowany,0);
            continue;
        }

        e=max_rpg(gotowy,2);
        RPG=gotowy[e];

        gotowy.erase(gotowy.begin()+e);

        ++k;
        t=t+RPG[1];
        Cmax=max(Cmax,t+RPG[2]);
        pi.push_back(RPG);
    }
    return Cmax;
}

int SchrageZPodzialem(vector<vector<int>>nieuporzadkowany) // Alg Schrage, zwraca Cmax
{
    vector<vector<int>> gotowy;
    vector<int> RPG,akt_zad;
    vector<vector<int>>pi;
    int t=0,k=0,Cmax=0,e=0,q0;
    akt_zad.push_back(0);
    akt_zad.push_back(0);
    akt_zad.push_back(q0);

    while (!gotowy.empty() || !nieuporzadkowany.empty())
    {
        while(!nieuporzadkowany.empty() && min_wartosc(nieuporzadkowany,0)<=t)
        {
            e=min_rpg(nieuporzadkowany,0);
            RPG=nieuporzadkowany[e];
            gotowy.push_back(nieuporzadkowany[e]);
            nieuporzadkowany.erase(nieuporzadkowany.begin()+e);

            if(RPG[2]>akt_zad[2])
            {
                akt_zad[1]=t-RPG[0];
                t=RPG[0];
                if(akt_zad[1]>0)
                    gotowy.push_back(akt_zad);
            }
        }

        if(gotowy.empty())
        {
            t=min_wartosc(nieuporzadkowany,0);
            continue;
        }

        RPG=gotowy[max_rpg(gotowy,2)];

        gotowy.erase(gotowy.begin()+max_rpg(gotowy,2));

        akt_zad=RPG;
        t=t+RPG[1];
        Cmax=max(Cmax,t+RPG[2]);
    }
    return Cmax;
}
vector<vector<int>> schrage_perm(vector<vector<int>>nieuporzadkowany) // Zwraca permutacje z alg Schrage
{
    vector<vector<int>>pi;
    vector<vector<int>> gotowy;
    vector<int> RPG;
    int t=0,k=0,Cmax=0,e=0;
    while (!gotowy.empty() || !nieuporzadkowany.empty())
    {
        while(!nieuporzadkowany.empty() && min_wartosc(nieuporzadkowany,0)<=t)
        {
            e=min_rpg(nieuporzadkowany,0);
            gotowy.push_back(nieuporzadkowany[e]);
            nieuporzadkowany.erase(nieuporzadkowany.begin()+e);
        }

        if(gotowy.empty())
        {
            t=min_wartosc(nieuporzadkowany,0);
            continue;
        }

        e=max_rpg(gotowy,2);
        RPG=gotowy[e];

        gotowy.erase(gotowy.begin()+e);

        ++k;
        t=t+RPG[1];
        Cmax=max(Cmax,t+RPG[2]);
        pi.push_back(RPG);
    }
    return pi;
}

int Cmax_pi(vector<vector<int>>pi) // Funkcja zwraca wartosc Cmax dla danej permutacji
{
    vector<int> RPG;
    int t=pi[0][0];
    int Cmax=0;
    for(int i=0; i<pi.size(); i++)
    {
        RPG=pi[i];
        t=max(t,RPG[0]);
        t+=RPG[1];
        Cmax=max(Cmax,t+RPG[2]);
    }

    return Cmax;

}

int alg_carlier(vector<vector<int>>nieuporzadkowany, int UB)
{
    /*n – liczba zada
    ri – termin dostępnoci zadania i
    pi – czas wykonania zadania i
    qi – czas dostarczenia zadania i
    UB – górne oszacowanie wartoci funkcji celu ( warto funkcji celu dla najlepszego dotychczas najlepszego rozwiązania)


    π - permutacja wykonania zadana maszynie,
    U – warto funkcji celu,
    LB – dolne oszacowanie wartosci funkcji c
    */


    vector<vector<int>> opt_pi,pi;
    vector<int> RPG;

    pi=schrage_perm(nieuporzadkowany); //wyznaczenie permutacji wykonywania zadañ algorytmem SHRAGE

    // **********PKT nr 2************
    //uaktualniane jest najlepsze do tej pory znalezione rozwiazanie
    int U=Schrage(nieuporzadkowany);
    if (U<UB)
    {
        UB=U;
        opt_pi=pi;
    }

    // **********PKT nr 3************
    //tu wyznaczany jest blok (a,b) oraz pozycja zadania interferencyjnego
    int a;
    int b=-1;
    int c=-1;
    int t=pi[0][0];

    // Wyznaczenie b
    for(int i=0; i<pi.size(); i++)
    {
        //int suma=0;
        int Cmax_PI=Cmax_pi(pi); // przypisanie Cmax dla danego pi
        RPG=pi[i];
        t=max(t,RPG[0]);
        t+=RPG[1];
        if(t+RPG[2]==Cmax_PI)
        {
            if(i>b)     // wybieramy tylko najwieksze b, pierwszy zawsze spelniony bo wyzej b=-1
                b=i;
        }
        // wyznaczenie sumy do a
    }

    for(int i=0; i<pi.size(); i++)
    {
        int suma=0;
        int Cmax_PI=Cmax_pi(pi); // przypisanie Cmax dla danego pi
        RPG=pi[i];
        t=max(t,RPG[0]);
        t+=RPG[1];
        for(int s=i; s<=b; s++)
        {
            suma+=pi[s][1];
            //suma+=pi[b][2];
        }
        suma+=pi[b][2];
        if((RPG[0]+suma)==Cmax_PI)
        {
            if(i<a)
                a=i;  // wybieramy tylko najmniejsze a, pierwszy zawsze spelniony, bo wyzej a
        }
    }

    // wyznaczenie c
    for(int i=a; i<=b; i++)
    {
        if(pi[i][2]<pi[b][2])
        {
            if(i>c)
                c=i;
        }
    }

    if(c==-1)
    {
        flaga = true;
    }

    //****** PKT nr 4*******
    if(flaga==true)
    {
        program.push_back(UB);

        return UB;
    }

    // ******PKT nr 5*********
    /*wyznaczany jest najmniejszy z terminów dostępnosci oraz największy z termidostarczenia zadan stojacych na
    pozycjach od c+1 do b, dodatkowo wyznaczana jest suma czasów wykonania zadan*/
    int r_prim,g_prim,p_prim=0;
    for(int i=c+1; i<=b; i++)
    {
        if(pi[i][0]<r_prim)
            r_prim=pi[i][0];

        if(pi[i][2]<g_prim)
            g_prim=pi[i][2];

        p_prim+=pi[i][1];
    }

    // ********PKT 6-10***********
    int r_pom=pi[c][0];
    pi[c][0]=max(pi[c][0],r_prim+p_prim);   /*modyfikowany jest termin dostepno ci zadania referencyjnego
                                             (wymuszane jest aby zadanie referencyjne wykonywane było za wszystkimi zadaniami na tych pozycjach)*/
    int LB=SchrageZPodzialem(pi); //wyznaczane jest dolne ograniczenie dla wszystkich permutacji spełniajacych to wymaganie
    if(LB<UB)   //jeśli dolne oszacowanie wartosci celu jest mneijsze od gornego oszacowania funkcji celu
        alg_carlier(pi,UB);
    pi[c][0]=r_pom; //odtwarzany jest termin dostepnoci rozwiazania referencyjnego

    // *********PKT 11-15*************
    int q_pom=pi[c][2];
    pi[c][2]=max(pi[c][2],g_prim+p_prim);
    LB=SchrageZPodzialem(pi);
    if(LB<UB)
        alg_carlier(pi,UB);
    pi[c][2]=q_pom; /*modyfikowany jest termin dostarczenia zadania referencyjnego
                    (wymuszane jest aby zadanie referencyjne wykonywane było przed wszystkimi zadaniami na pozycjach od c+1 do b).*/
    return UB;
}

int main()
{
    vector<vector<int>>nieuporzadkowany;
    WczytajDane(nieuporzadkowany);
    alg_carlier(nieuporzadkowany,INT_MAX);
    cout<<"Cmax to: "<<program.at(0)<<endl;
    return 0;
}
