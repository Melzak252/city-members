#ifndef KIBIC_H
#define KIBIC_H
#include<iostream>
#include "KibicBaza.h"

using namespace std;


class Miasto;

class Kibic: public KibicBaza{
    public:
        Kibic(string, float);
        Kibic(float, float, string);
        virtual ~Kibic();
        friend ostream& operator<<(ostream&, Kibic*);
      protected:
        virtual bool czy_w_promieniu(float, float, float, float, float);
        virtual bool czy_sasiaduja(KibicBaza*, float, float);
};

#endif // KIBIC_H
