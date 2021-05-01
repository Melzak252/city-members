#include<cstdlib>
#include<ctime>
#include<fstream>
#include "../include/Miasto.h"
#include "Kibic.cpp"
#include <thread>
#include <cmath>
#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60
using namespace std;



void printProgress(double percentage) {
    int val = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}

Miasto::Miasto(int N, float xy, float r = 10.)
{
    cout<<"Witaj w naszym miescie!!!"<<endl;
    Miasto::liczba_kibicow = N;
    Miasto::wymiary = xy;
    Miasto::promien_sprawdzania = r;

}

Miasto::~Miasto()
{
    //cout<<"Miasto zostało zniszczone >:D"<<endl;
}

void Miasto::zaludnij(){
    srand(time(NULL));
    for(int index=0; index<liczba_kibicow; index++)
    {
        int k;
        float x, y;
        string nazwa_klubu;
        x = RandomFloat(0, Miasto::wymiary);
        y = RandomFloat(0, Miasto::wymiary);
        switch(index%2){
        case 0:
            nazwa_klubu = "Legia";
        break;
        case 1:
            nazwa_klubu = "Polonia";
        break;
        default:
            cout<<"Ups cos poszlo nie tak z dzieleniem"<<endl;
        }

        kibice.push_back(Kibic(x, y, index, index%2, nazwa_klubu));
        kibice.pop
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

float Miasto::RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return round((a + r*1000.))/1000.;
}
