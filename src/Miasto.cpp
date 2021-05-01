#include<cstdlib>
#include<ctime>
#include<fstream>
#include <cmath>
#include <vector>

#include "KibicBaza.cpp"
#include "../include/Miasto.h"
#include "../helper.cpp"
#include "Kibic.cpp"


using namespace std;

Miasto::Miasto(int N, float stosunek, float wymiary, float promien_sprawdzania = 10., float promien_przeprowadzki = 1.)
{
    cout<<"Witaj w naszym miescie!!!"<<endl;
    Miasto::liczba_kibicow = N;
    Miasto::stosunek = stosunek;
    Miasto::wymiary = wymiary;
    Miasto::promien_sprawdzania = promien_sprawdzania;
    Miasto::promien_przeprowadzki = promien_przeprowadzki;

}

Miasto::~Miasto()
{
    //cout<<"Miasto zostało zniszczone >:D"<<endl;
}

void Miasto::zaludnij(){
    int kibice_legii = (int)(Miasto::stosunek*Miasto::liczba_kibicow);
    int kibice_poloni = Miasto::liczba_kibicow - kibice_legii;

    cout<<"Liczba kibicow Legii: "<<kibice_legii<<endl;
    cout<<"Liczba kibicow Polonii: "<<kibice_poloni<<endl;
    for(int i=0; i<kibice_legii; i++){
        float x = RandomFloat(0, Miasto::wymiary);
        float y = RandomFloat(0, Miasto::wymiary);
        Miasto::pola_miasta[floor(x)][floor(y)].push_back(KibicBaza(x, y, 0));
        Miasto::kibice.push_back(Kibic(x, y, 0, "Legia"));
    }
    for(int i=0; i<kibice_poloni; i++){
        float x = RandomFloat(0, Miasto::wymiary);
        float y = RandomFloat(0, Miasto::wymiary);
        Miasto::pola_miasta[floor(x)][floor(y)].push_back(KibicBaza(x, y, 1));
        Miasto::kibice.push_back(Kibic(x, y, 1, "Polonia"));
    }
}



void Miasto::zapisz_i_narysuj(){
    ofstream polonia, legia, gnuplot;
    polonia.open("polonia.txt");
    legia.open("legia.txt");
    for(int index=0; index<Miasto::liczba_kibicow; index++)
    {
        switch(index%2){
        case 0:
            legia<<Miasto::kibice[index].x<<" "<<Miasto::kibice[index].y<<endl;
        break;
        case 1:
            polonia<<Miasto::kibice[index].x<<" "<<Miasto::kibice[index].y<<endl;
        break;
        default:
            cout<<"Ups cos poszlo nie tak z dzieleniem"<<endl;
        }

    }
    polonia.close();
    legia.close();

    gnuplot.open("skrypt.gp");

    gnuplot<<"plot \"polonia.txt\" with points pointtype 7,\"legia.txt\" with points pointtype 7"<<endl;
    gnuplot<<"pause -1 \"Wciśnij ENTER\""<<endl;

    gnuplot.close();

    system("gnuplot skrypt.gp");
}

void Miasto::ewoluuj(){
    int zadowolenie_kibicow[Miasto::liczba_kibicow][2];
    for(int index = 0; index<Miasto::liczba_kibicow; index++)
    {
        zadowolenie_kibicow[index][0] = Miasto::kibice[index].zadowolenie(*this, zadowolenie_kibicow[index][1]);
        printProgress((double)index/Miasto::liczba_kibicow);

    }
    printProgress(1.);
    cout<<endl;
    int licznik = 0;
    for(int index = 0; index<Miasto::liczba_kibicow; index++) {


        if(zadowolenie_kibicow[index][0]-zadowolenie_kibicow[index][1]<0) {

            Miasto::kibice[index].przeprowadzka(Miasto::wymiary, 10.);
            licznik ++;
        }
    }
    cout<<licznik<<" przemieszczono!!!"<<endl;
}
