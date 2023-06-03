#include<cstdlib>
#include<ctime>
#include<fstream>
#include "../helper.cpp"
#include "../include/Miasto.h"
#include "Kibic.cpp"
#include "KibicKwadrat.cpp"
#include <thread>
#include <cmath>

using namespace std;


Miasto::Miasto()
{
    cout<<"Witaj w naszym miescie!!!"<<endl;
    Miasto::liczba_kibicow = 0;

}

Miasto::~Miasto()
{
  
    //cout<<"Miasto zostało zniszczone >:D"<<endl;
}

void Miasto::zaludnij(int liczba_kibicow, float stosunek){
    Miasto::stosunek = stosunek;
    Miasto::liczba_kibicow = liczba_kibicow;

    int kibice_legii = (int)(Miasto::stosunek * Miasto::liczba_kibicow);
    int kibice_polonii = Miasto::liczba_kibicow - kibice_legii;

    for(int index=0; index<kibice_legii; index++) {
      string nazwa = "Legia";
      KibicBaza *wsk;
      if(Miasto::kwadraty) wsk =  new KibicKwadrat(nazwa, Miasto::wymiary);
      else wsk =  new Kibic(nazwa, Miasto::wymiary);
      Miasto::kibice.push_back(wsk);
    }

    for(int index=0; index<kibice_polonii; index++) {
      string nazwa = "Polonia";
      KibicBaza *wsk;
      if(Miasto::kwadraty) wsk =  new KibicKwadrat(nazwa, Miasto::wymiary);
      else wsk =  new Kibic(nazwa, Miasto::wymiary);

      Miasto::kibice.push_back(wsk);
    }
}



void Miasto::zapisz_i_narysuj(){
    ofstream polonia, legia, gnuplot;
    polonia.open("polonia.txt");
    legia.open("legia.txt");
    for(int index=0; index<Miasto::liczba_kibicow; index++)
    {
        switch(Miasto::kibice[index]->getKlub()){
        case 0:
            legia<<Miasto::kibice[index];
        break;
        case 1:
            polonia<<Miasto::kibice[index];
        break;
        default:
            cout<<"Ups cos poszlo nie tak z dzieleniem"<<endl;
        break;
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

    std::vector<int> zadowolenie_kibicow;
    int suma_zadowolenia = 0;
    for(int index = 0; index<Miasto::kibice.size(); index++)
    {
        int zadowolenie = Miasto::kibice[index]->zadowolenie(*this);

        suma_zadowolenia+=zadowolenie;
        zadowolenie_kibicow.push_back(zadowolenie);

        printProgress((double)index/Miasto::liczba_kibicow);

    }

    for(int index = 0; index<Miasto::liczba_kibicow; index++) if(zadowolenie_kibicow[index]<0) Miasto::kibice[index]->przeprowadzka(Miasto::wymiary, Miasto::promien_przeprowadzki);
    printProgress(1.);
    cout<<endl<<"Srednia zadowolenia jest rowna: "<< (float)suma_zadowolenia/Miasto::liczba_kibicow<<endl;
}

void Miasto::wczytaj(string nazwa_pliku)
{
  ifstream plik;
  plik.open(nazwa_pliku);
  float x, y;
  string nazwa_klubu;
  while(plik>>x>>y>>nazwa_klubu)
  {
    if(x>Miasto::wymiary || x<0) {
      cout<<"Error: Blednie podane dane polozenia kibica w pliku"<<endl;
      exit(-3);
    }
    if(y>Miasto::wymiary || y<0) {
      cout<<"Error: Blednie podane dane polozenia kibica w pliku"<<endl;
      exit(-3);
    }

    if(nazwa_klubu == "Legia") {
      KibicBaza *wsk;
      if(Miasto::kwadraty) wsk =  new KibicKwadrat(x, y, nazwa_klubu);
      else wsk =  new Kibic(x, y, nazwa_klubu);
      Miasto::kibice.push_back(wsk);
      Miasto::liczba_kibicow++;
    }
    else if(nazwa_klubu == "Polonia") {
      KibicBaza *wsk;
      if(Miasto::kwadraty) wsk =  new KibicKwadrat(x, y, nazwa_klubu);
      else wsk =  new Kibic(x, y, nazwa_klubu);
      Miasto::kibice.push_back(wsk);
      Miasto::liczba_kibicow++;
    }
    else{
      char wybor;
      cout<<"Nazwa " <<nazwa_klubu<< " nie zgadza sie z obslugiwanymi klubami!"<<endl;
      cout<<"Co chcesz zrobic z podanym kibicem: "<<endl;
      cout<<"1 - Dopisac jako kibica Legii,"<<endl;
      cout<<"2 - Dopisac jako kibica Polonii,"<<endl;
      cout<<"3 - Pomin"<<endl;
      cout<<"4 - Zakoncz program"<<endl;
      cin>>wybor;
      switch (wybor) {
        case '1':
        {
          string nazwa = "Legia";
          KibicBaza *wsk;
          if(Miasto::kwadraty) wsk =  new KibicKwadrat(x, y, nazwa);
          else wsk =  new Kibic(x, y, nazwa);
          Miasto::kibice.push_back(wsk);
          Miasto::liczba_kibicow++;
          break;
        }
        case '2':
        {
          string nazwa = "Polonia";
          KibicBaza *wsk;
          if(Miasto::kwadraty) wsk =  new KibicKwadrat(x, y, nazwa);
          else wsk =  new Kibic(x, y, nazwa);
          Miasto::kibice.push_back(wsk);
          Miasto::liczba_kibicow++;
          break;
        }
        case '3':
        break;
        case '4':
        {
          cout<<"To koniec!"<<endl;
          exit(-1);
          break;
        }
        default:
        {
          cout<<"Error: Nie ma takiej opcji!"<<endl;
          exit(-1);
          break;
        }
      }
    }
  }
  plik.close();
}

void Miasto::narysuj(string nazwa_pliku, int size, float r){
  cout<<"Proces rysowania: "<<endl;
  ofstream plik;
  plik.open(nazwa_pliku);
  plik<<"P3"<<endl;
  plik<<size<<" "<<size<<endl;
  plik<<255<<endl;

  std::vector<int> v(size, 255);
  std::vector<std::vector<int> > R(size, v);
  std::vector<std::vector<int> > G(size, v);
  std::vector<std::vector<int> > B(size, v);

  int sufit_r = ceil(r);
  float przelicznik = (float)size / Miasto::wymiary;

  for(int index_kibica = 0; index_kibica < Miasto::liczba_kibicow; index_kibica++){
    double procent = (double)index_kibica/Miasto::liczba_kibicow;
    printProgress(procent*0.5);
    int x = round((Miasto::kibice[index_kibica]->getX())*(przelicznik));
    int y = round((Miasto::kibice[index_kibica]->getY())*(przelicznik));
    for(int i = x - sufit_r; i<x+sufit_r; i++){
      if(i>0 && i<size){
        for(int k = y - sufit_r; k<y+sufit_r; k++){
          if(k>0 && k<size){
            if((i-x)*(i-x) + (k-y)*(k-y)<=r*r){
              switch (Miasto::kibice[index_kibica]->getKlub()) {
                case 0:
                {
                  R[i][k] = 0;
                  G[i][k] = 255;
                  B[i][k] = 0;
                  break;
                }
                case 1:
                {
                  R[i][k] = 255;
                  G[i][k] = 0;
                  B[i][k] = 0;
                  break;
                }
                default:
                {
                  cout<<"Error: Bledna druzyna u jednego z kibicow";
                  exit(-3);
                  break;
                }
              }
            }
          }
        }
      }
    }
  }

  for(int i = 0; i<size; i++){
    for(int k = 0; k<size; k++){
      plik<<R[k][i]<<" "<<G[k][i]<<" "<<B[k][i]<<endl;
    }
    printProgress(0.5 + 0.5*i/size);
  }
  printProgress(1.);
  plik.close();
  cout<<endl;
}

int Miasto::getLiczbaKibicow(){
  return Miasto::liczba_kibicow;
}

float Miasto::getPromienSprawdzania(){
  return Miasto::promien_sprawdzania;
}

float Miasto::getWymiary(){
  return Miasto::wymiary;
}

KibicBaza* Miasto::getKibic(int index){
  if(index<Miasto::kibice.size())
    return Miasto::kibice[index];
  else{
    cout<<"Nie ma takiego kibica!"<<endl;
    exit(-5);
  }
}

void Miasto::setPromienSprawdzania(float promien_sprawdzania){
  Miasto::promien_sprawdzania = promien_sprawdzania;
}

void Miasto::setPromienPrzeprowadzki(float promien_przeprowadzki){
  Miasto::promien_przeprowadzki = promien_przeprowadzki;
}

void Miasto::setWymiary(float wymiary){
  Miasto::wymiary = wymiary;
}

void Miasto::setKwadraty(bool kwadraty){
  Miasto::kwadraty = kwadraty;
}
