#ifndef KIBIC_H
#define KIBIC_H
#include<iostream>

using namespace std;

class Miasto;

class Kibic{
    public:
        int index, klub, kolumna, wiersz;
        float x, y;
        string nazwa_klubu;
        Kibic(float, float, int, int, string);
        virtual ~Kibic();
        int zadowolenie(Miasto, int&);
        void przeprowadzka(float&, float);
    private:
        bool czy_w_promieniu(float, float, float, float, float);
        bool czy_sasiaduja(Kibic, float, float, float);
        float RandomFloat(float, float);

};

#endif // KIBIC_H
