#include "../include/Kibic.h"
#include <iostream>
#include<cmath>
#include "math.h"

using namespace std;

class Miasto;


Kibic::Kibic(float x, float y, int klub, string nazwa_klubu): KibicBaza(x, y, klub)
{
    Kibic::x = x;
    Kibic::y = y;
    Kibic::klub = klub;
    Kibic::nazwa_klubu = nazwa_klubu;
    Kibic::kolumna = floor(x);
    Kibic::wiersz = floor(y);
}

Kibic::~Kibic()
{
    //cout<<"Kibic o indeksie: "<<Kibic::index<<" zniknal w nie zbadanych okolicznosciach!!!"<<endl;
}

bool Kibic::czy_sasiaduja(Kibic drugi, float promien, float wymiar, float odleglosc)
{
    if(Kibic::czy_w_promieniu(Kibic::x, Kibic::y, drugi.x, drugi.y, promien)) return true;
    else if(Kibic::czy_w_promieniu(Kibic::x-wymiar, Kibic::y-wymiar, drugi.x, drugi.y, promien)) return true;
    else if(Kibic::czy_w_promieniu(Kibic::x-wymiar, Kibic::y+wymiar, drugi.x, drugi.y, promien)) return true;
    else if(Kibic::czy_w_promieniu(Kibic::x+wymiar, Kibic::y+wymiar, drugi.x, drugi.y, promien)) return true;
    else if(Kibic::czy_w_promieniu(Kibic::x+wymiar, Kibic::y-wymiar, drugi.x, drugi.y, promien)) return true;
    else return false;

}


int Kibic::zadowolenie(Miasto miasto, int &przeciwny_klub)
{
    int przyjazny_klub = 0;

    przeciwny_klub = 0;

    for(int index_kibica=0; index_kibica<miasto.liczba_kibicow; index_kibica++){


          float x_drugiego, y_drugiego, odleglosc;
          x_drugiego = miasto.kibice[index_kibica].x;
          y_drugiego = miasto.kibice[index_kibica].y;

          if(Kibic::czy_sasiaduja(miasto.kibice[index_kibica], miasto.promien_sprawdzania, miasto.wymiary, odleglosc)){
                  if(miasto.kibice[index_kibica].klub==Kibic::klub) przyjazny_klub++;
                  else przeciwny_klub++;


        }
    }
    return przyjazny_klub;
}

bool Kibic::czy_w_promieniu(float x_1, float y_1, float x_2, float y_2, float promien)
{
    return sqrt((x_1 - x_2)*(x_1 - x_2) + (y_1 - y_2)*(y_1 - y_2))<promien;
}

void Kibic::przeprowadzka(float &wymiary, float promien_przeprowadzki=1.){

    float kat = RandomFloat(0, 2*M_PI);
    float dx = promien_przeprowadzki*cos(kat), dy = promien_przeprowadzki*sin(kat);
    Kibic::x += dx;
    Kibic::y += dy;

    if(Kibic::x>wymiary) Kibic::x -= wymiary;
    else if(Kibic::x<0) Kibic::x += wymiary;

    if(Kibic::y>wymiary) Kibic::y -= wymiary;
    else if(Kibic::y<0) Kibic::y += wymiary;
}
