#include "../include/KibicBaza.h"
#include <iostream>
#include<cmath>
#include <thread>

using namespace std;

class Miasto;

ostream& operator<< (ostream& out, KibicBaza* k)
{
  float x = k->getX();
  float y = k->getY();
  string nazwa = k->getNazwa();
  out<<x<<" "<<y<<" "<<nazwa<<endl;
  return out;
}

KibicBaza::KibicBaza(string nazwa_klubu, float wymiary)
{
    if(nazwa_klubu=="Legia") KibicBaza::klub = 0;
    else if(nazwa_klubu=="Polonia")  KibicBaza::klub = 1;
    else{
      cout<<"Nie ma takiego klubu jak "<<nazwa_klubu<<", w obslugiwanych!"<<endl;
      exit(-1);
    }

    KibicBaza::x = RandomFloat(0, wymiary);
    KibicBaza::y = RandomFloat(0, wymiary);
    KibicBaza::nazwa_klubu = nazwa_klubu;
}

KibicBaza::KibicBaza(float x, float y, string nazwa_klubu)
{
    KibicBaza::x = x;
    KibicBaza::y = y;
    KibicBaza::nazwa_klubu = nazwa_klubu;
    if(nazwa_klubu=="Legia") KibicBaza::klub = 0;
    else if(nazwa_klubu=="Polonia")  KibicBaza::klub = 1;
    else{
      cout<<"Nie ma takiego klubu jak "<<nazwa_klubu<<", w obslugiwanych!"<<endl;
      exit(-1);
    }
}

KibicBaza::~KibicBaza()
{
  
    //cout<<"Kibic o indeksie: "<<KibicBaza::index<<" zniknal w nie zbadanych okolicznosciach!!!"<<endl;
}

int KibicBaza::zadowolenie(Miasto miasto)
{
    int zadowolenie = 0;

    for(int index_kibica=0; index_kibica<miasto.getLiczbaKibicow(); index_kibica++){
          KibicBaza* kibic = miasto.getKibic(index_kibica);
          if(this->czy_sasiaduja(kibic, miasto.getPromienSprawdzania(), miasto.getWymiary()))
          {
            if(KibicBaza::klub ==kibic->getKlub()) zadowolenie++;
            else zadowolenie--;
          }
    }
    return zadowolenie;
}

void KibicBaza::przeprowadzka(float &wymiary, float promien_przeprowadzki=1.){

    float kat = RandomFloat(0, 2*M_PI);
    float dx = promien_przeprowadzki*cos(kat), dy = promien_przeprowadzki*sin(kat);
    KibicBaza::x += dx;
    KibicBaza::y += dy;

    if(KibicBaza::x>wymiary) KibicBaza::x -= wymiary;
    else if(KibicBaza::x<0) KibicBaza::x += wymiary;

    if(KibicBaza::y>wymiary) KibicBaza::y -= wymiary;
    else if(KibicBaza::y<0) KibicBaza::y += wymiary;
}

int KibicBaza::getKlub(){
  return KibicBaza::klub;
}
float KibicBaza::getX(){
  return KibicBaza::x;
}
float KibicBaza::getY(){
  return KibicBaza::y;
}
void KibicBaza::setY(float y){
  KibicBaza::y = y;
}
void KibicBaza::setX(float x){
  KibicBaza::x = x;
}
string KibicBaza::getNazwa(){
  return KibicBaza::nazwa_klubu;
}
