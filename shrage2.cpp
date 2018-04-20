#include <iostream>
#include <cstdlib>
#include <fstream>
#include <queue>



using namespace std;
struct zadanie{
	int r;
	int p;
	int q;
	int nr;
	void czytaj(int t1,int t2,int t3, int _nr){r = t1, p = t2, q = t3, nr=_nr;};
};

struct porownaj_q{
	bool operator()(const zadanie& el1, const zadanie& el2){				// < od najwiekszego do najmniejszego
		return el1.q < el2.q;												// > od najmniejszego do najwiekszego
	}
};
struct porownaj_r{
	bool operator()(const zadanie& el1, const zadanie& el2){				// < od najwiekszego do najmniejszego
		return el1.r > el2.r;												// > od najmniejszego do najwiekszego
	}
};

 int main()
 {
    int t = 0;
    int Cmax = 0;

 	priority_queue <zadanie, vector<zadanie>, porownaj_q> gotowy;
 	priority_queue <zadanie, vector<zadanie>, porownaj_r> nieuporzadkowany;
 	 zadanie test;

 	 fstream plik;
	 plik.open( "SCHRAGE2.DAT", ios::in );
 	 int n;
     plik >> n;
     int czas_1, czas_2, czas_3, nr;

	 for (int i=0; i<n; ++i)
     {
        plik >> czas_1;
        plik >> czas_2;
        plik >> czas_3;
        nr=i+1;
        test.czytaj(czas_1, czas_2, czas_3, nr);
        nieuporzadkowany.push(test);
	 }
     plik.close();

	 int tab[n];
     int tmp=0;


	 zadanie e;
	 zadanie l;
	 while (!gotowy.empty() || !nieuporzadkowany.empty())
     {
         if(!nieuporzadkowany.empty()) //zabezpieczenie przed brakiem top z pustej kolejki
         {
            while(!nieuporzadkowany.empty() && nieuporzadkowany.top().r <= t)
            {
                e = nieuporzadkowany.top();
                gotowy.push(e);
                nieuporzadkowany.pop();
                if (e.q > l.q)
                {                   //e.q pierwsze zadanie z uszeregowanej kolejki    l.q czas dostarczenia zadania ktore jest na maszynie
                    l.p = t - e.r;      // czas zadania jaki pozostal jak przerwalismy
                    t = e.r;            // t jest terminem dostepnosci zadania
                    if (l.p > 0)
                    {
                        gotowy.push(l);
                    }
                }
            }
         }
		 if (gotowy.empty() && !nieuporzadkowany.empty())
		 {
            t = nieuporzadkowany.top().r;
		 }
		 	else
            {
                e = gotowy.top();
                l = e;                 //naszym aktualnym zadaniem jest to co bylo pierwszym elmentem uszeregowanym na kolejce gotowe
                t = t + e.p;
               // tab[tmp]=e.nr;
                //tmp=tmp+1;
                Cmax = max(Cmax, t + e.q);
                gotowy.pop();
			 }
	 }
	 cout<<"Cmax: "<<Cmax<<endl;
   //  for(int i=0;i<n;i++)
    // {
    //     cout<<"Nr:"<<tab[i]<<" ";
     //}

   	return(0);
 }
