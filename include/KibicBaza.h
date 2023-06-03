#ifndef KIBICBAZA_H
#define KIBICBAZA_H
#include<iostream>

using namespace std;

class Miasto;


class KibicBaza{
    public:
        KibicBaza(string, float);
        KibicBaza(float, float, string);
        virtual ~KibicBaza();
        int zadowolenie(Miasto);
        void przeprowadzka(float&, float);
        friend ostream& operator<<(ostream&, KibicBaza&);
        float getX();
        float getY();
        int getKlub();
        string getNazwa();
        void setX(float);
        void setY(float);

    protected:
        int klub;
        float x, y;
        string nazwa_klubu;
        virtual bool czy_w_promieniu(float, float, float, float, float) = 0;
        virtual bool czy_sasiaduja(KibicBaza*, float, float) = 0;
};

#endif // KIBICBAZA_H
