#include "../include/KibicKwadrat.h"
#include <iostream>
#include<cmath>
#include <thread>

using namespace std;

class Miasto;

ostream& operator<< (ostream& out, KibicKwadrat* k)
{
  float x = k->getX();
  float y = k->getY();
  string nazwa = k->getNazwa();
  out<<x<<" "<<y<<" "<<nazwa<<endl;
  return out;
}

KibicKwadrat::KibicKwadrat(string nazwa_klubu, float wymiary): KibicBaza(nazwa_klubu, wymiary)
{
}

KibicKwadrat::KibicKwadrat(float x, float y, string nazwa_klubu): KibicBaza(x, y, nazwa_klubu)
{


}

KibicKwadrat::~KibicKwadrat()
{
    //cout<<"Kibic o indeksie: "<<KibicKwadrat::index<<" zniknal w nie zbadanych okolicznosciach!!!"<<endl;
}

bool KibicKwadrat::czy_sasiaduja(KibicBaza* drugi, float promien, float wymiar)
{
  if(KibicKwadrat::czy_w_promieniu(KibicKwadrat::x, KibicKwadrat::y, drugi->getX(), drugi->getY(), promien)) return true;
  else if(KibicKwadrat::czy_w_promieniu(KibicKwadrat::x-wymiar, KibicKwadrat::y-wymiar, drugi->getX(), drugi->getY(), promien)) return true;
  else if(KibicKwadrat::czy_w_promieniu(KibicKwadrat::x-wymiar, KibicKwadrat::y+wymiar, drugi->getX(), drugi->getY(), promien)) return true;
  else if(KibicKwadrat::czy_w_promieniu(KibicKwadrat::x+wymiar, KibicKwadrat::y+wymiar, drugi->getX(), drugi->getY(), promien)) return true;
  else if(KibicKwadrat::czy_w_promieniu(KibicKwadrat::x+wymiar, KibicKwadrat::y-wymiar, drugi->getX(), drugi->getY(), promien)) return true;
  else return false;

}

bool KibicKwadrat::czy_w_promieniu(float x_1, float y_1, float x_2, float y_2, float promien)
{
    return abs(x_1 - x_2)<promien && abs(y_1 - y_2)<promien;
}
