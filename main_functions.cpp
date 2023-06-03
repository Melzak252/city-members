#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

#include "src/Miasto.cpp"

using namespace std;

float WYMIARY = 25., PROMIEN_SPRAWDZANIA = 1., PROMIEN_PRZEPROWADZKI = 1., PROMIEN_PUNKTU = 5.;
int BOK_RYSUNKU= 1000;
bool KWADRATY = false, END = false;

void zaludnij_miasto(Miasto &m){
  float stosunek;
  int liczba_ludzi;
  cout<<"Podaj liczbe mieszkancow: ";
  cin>>liczba_ludzi;
  cout<<"Podaj procentowy udzial kibicow Legii w miescie: ";
  if(liczba_ludzi<0) {
    cout<<"Liczba kibicow nie moze byc ujemna!"<<endl;
    exit(-2);
  }
  cin>>stosunek;

  if(0<=stosunek && stosunek<=1.) {
    m.zaludnij(liczba_ludzi, stosunek);
  }
  else {
    cout<< "Error: Procentowy wskaznik kibicow Legii w miescie powinien byc z przedzialu [0, 1]"<<endl;
    exit(-2);
  }

}

void wczytanie(Miasto &m){
  char decyzja;
  cout<<"Wybierz sposob zaludnienia miasta: "<<endl;
  cout<<"1 - Losowanie,"<<endl;
  cout<<"2 - Z pliku,"<<endl;
  cout<<"3 - Zakoncz program."<<endl;
  cin>>decyzja;
  switch (decyzja) {
    case '1':
      zaludnij_miasto(m);
    break;
    case '2':
    {
      string nazwa_pliku;
      cout<<"Podaj nazwe pliku: ";
      cin>>nazwa_pliku;
      m.wczytaj(nazwa_pliku);
      break;
    }

    case '3':
      exit(-1);
    break;
    default:
      exit(-2);
    break;
  }
}

void help(){
  cout<<"Opcje dodatkowe do programu:"<<endl;
  cout<<"-h, Wypisuje krótkie opisy wszystkich funkcji"<<endl;
  cout<<"-rp [float], Zmienia wartosc promien sprawdzania sasiedztwa kibicow, bazowo, 1.0"<<endl;
  cout<<"-rs [float], Zmienia wartosc promien sprawdzania przeprowadzki kibicow, bazowo 1.0"<<endl;
  cout<<"-w [float], Zmienia wielkosc miasta, bazowo 25.0"<<endl;
  cout<<"-pix [int], Zmienia wielkosc plikow ppm, bazowo 1000 pixeli"<<endl;
  cout<<"-rpix [float], Zmienia wielkosc prominienia kibica na rysunku, bazowo promien 5.0 pixeli"<<endl;
  cout<<"-sq, Wlacza wersje symulacji gdzie sprawdzanie sasiedztwa jest na bazie kwadratu"<<endl;
  cout<<"-end, Wlacza wersje symulacji gdzie zapisz_i_narysuj jest wlaczane tylko na poczatku i koncu programu"<<endl;

}

void parser(int argc, char* argv[], Miasto &m){
  for(int i = 1; i<argc; i+=2) {
    if(string(argv[i])== "-h") {
      help();
      exit(-1);
    }
    else if(string(argv[i])=="-sq"){
      KWADRATY = true;
      i--;
    }
    else if(string(argv[i])=="-end"){
      END = true;
      i--;
    }
    else{
      if(argc>i+1){
        if(string(argv[i])=="-rs") {
          PROMIEN_SPRAWDZANIA = atoi(argv[i+1]);
          if(PROMIEN_SPRAWDZANIA<0) {
            cout<<"Dlugosc promienia sprawdzania nie moze byc ujemny!"<<endl;
            exit(-5);
          }
        }
        else if(string(argv[i])=="-rp") {
          PROMIEN_PRZEPROWADZKI= atof(argv[i+1]);
          if(PROMIEN_SPRAWDZANIA<0) {
            cout<<"Dlugosc promienia przeprowadzki nie moze byc ujemny!"<<endl;
            exit(-5);
          }
        }
        else if(string(argv[i])=="-w") {
          WYMIARY = atof(argv[i+1]);
          if(PROMIEN_SPRAWDZANIA<0) {
            cout<<"Wymiary miasta nie moga byc ujemne!"<<endl;
            exit(-5);
          }
        }
        else if(string(argv[i])=="-pix") {
          BOK_RYSUNKU= atoi(argv[i+1]);
          if(BOK_RYSUNKU<0) {
            cout<<"Wymiary rysunku nie moga byc ujemne!"<<endl;
            exit(-5);
          }
        }
        else if(string(argv[i])=="-rpix") {
          PROMIEN_PUNKTU = atof(argv[i+1]);
          if(PROMIEN_PUNKTU<0) {
            cout<<"Dlugosc promienia nie moze byc ujemna!"<<endl;
            exit(-5);
          }
        }
        else {
          cout<<"Nie ma takiej opcji jak: "<<argv[i]<<endl;
          help();
          exit(-4);
        }
      }
      else{
        cout<<"Brakuje wartosci po wywolaniu funkcji "<<argv[i]<<endl;
        exit(-4);
      }
    }
  }
}


void symulacja(Miasto &m){
  int lata;
  cout<<endl<<"Podaj ile lat ewolucji oczekujesz: ";
  cin>>lata;

  if(lata<0){
    cout<<"Symulacja dziala tylko dla wartosci dodatnich lat"<<endl;
    exit(-3);
  }
  m.zapisz_i_narysuj();
  for(int rok=0; rok<lata; rok++){
      cout<<endl<<"Rok: "<<rok+1<<endl;

      m.ewoluuj();

      string nazwa_pliku = "Rok_" + to_string(rok+1)+".ppm";

      if((rok+1)%5 == 0) m.narysuj(nazwa_pliku, BOK_RYSUNKU, PROMIEN_PUNKTU);
      if(!END) m.zapisz_i_narysuj();
  }
  if(END)m.zapisz_i_narysuj();

  cout<<endl;
}


void start(int argc, char* argv[]){

  Miasto m;
  m.setWymiary(WYMIARY);
  m.setKwadraty(KWADRATY);
  m.setPromienSprawdzania(PROMIEN_SPRAWDZANIA);
  m.setPromienPrzeprowadzki(PROMIEN_PRZEPROWADZKI);
  parser(argc, argv, m);

  srand(time(NULL));
  wczytanie(m);
  symulacja(m);
}
