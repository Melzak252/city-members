#ifndef KIBICKWADRAT_H
#define KIBICKWADRAT_H
#include<iostream>
#include "KibicBaza.h"

using namespace std;

class Miasto;


class KibicKwadrat: public KibicBaza{
    public:
        KibicKwadrat(string, float);
        KibicKwadrat(float, float, string);
        virtual ~KibicKwadrat();
        friend ostream& operator<<(ostream&, KibicKwadrat*);
      protected:
        virtual bool czy_w_promieniu(float, float, float, float, float);
        virtual bool czy_sasiaduja(KibicBaza*, float, float);
};

#endif // KIBICKWADRAT_H
