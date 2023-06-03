#ifndef MIASTO_H
#define MIASTO_H
#include"KibicBaza.h"
#include<vector>

using namespace std;

class Miasto
{
    public:
        Miasto();
        virtual ~Miasto();
        void zaludnij(int, float);
        void zapisz_i_narysuj();
        void ewoluuj();
        void wczytaj(string);
        void narysuj(string, int, float);
        KibicBaza* getKibic(int);
        int getLiczbaKibicow();
        float getPromienSprawdzania();
        float getStosunek();
        float getPromienPrzeprowadzki();
        float getWymiary();
        bool getKwadraty();
        void setPromienSprawdzania(float);
        void setPromienPrzeprowadzki(float);
        void setKwadraty(bool);
        void setWymiary(float);
        void setStosunek(float);
        void setLizbaKibicow(int);

      private:
        int liczba_kibicow;
        std::vector<KibicBaza*> kibice;
        float promien_sprawdzania, promien_przeprowadzki, wymiary, stosunek;
        bool kwadraty;
};

#endif // MIASTO_H
