#include "../include/Kibic.h"
#include "KibicBaza.cpp"
#include <iostream>
#include<cmath>
#include <thread>

using namespace std;

class Miasto;

ostream& operator<< (ostream& out, Kibic* k)
{
    float x = k->getX();
    float y = k->getY();
    string nazwa = k->getNazwa();
    out<<x<<" "<<y<<" "<<nazwa<<endl;
    return out;
}

Kibic::Kibic(string nazwa_klubu, float wymiary): KibicBaza(nazwa_klubu, wymiary)
{
}

Kibic::Kibic(float x, float y, string nazwa_klubu): KibicBaza(x, y, nazwa_klubu)
{


}

Kibic::~Kibic()
{
    //cout<<"Kibic o indeksie: "<<Kibic::index<<" zniknal w nie zbadanych okolicznosciach!!!"<<endl;
}

bool Kibic::czy_sasiaduja(KibicBaza* drugi, float promien, float wymiar)
{
    if(Kibic::czy_w_promieniu(Kibic::x, Kibic::y, drugi->getX(), drugi->getY(), promien)) return true;
    else if(Kibic::czy_w_promieniu(Kibic::x-wymiar, Kibic::y-wymiar, drugi->getX(), drugi->getY(), promien)) return true;
    else if(Kibic::czy_w_promieniu(Kibic::x-wymiar, Kibic::y+wymiar, drugi->getX(), drugi->getY(), promien)) return true;
    else if(Kibic::czy_w_promieniu(Kibic::x+wymiar, Kibic::y+wymiar, drugi->getX(), drugi->getY(), promien)) return true;
    else if(Kibic::czy_w_promieniu(Kibic::x+wymiar, Kibic::y-wymiar, drugi->getX(), drugi->getY(), promien)) return true;
    else return false;

}

bool Kibic::czy_w_promieniu(float x_1, float y_1, float x_2, float y_2, float promien)
{
    return sqrt((x_1 - x_2)*(x_1 - x_2) + (y_1 - y_2)*(y_1 - y_2))<promien;
}
