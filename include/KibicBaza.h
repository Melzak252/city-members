#ifndef KIBIC_BAZA_H
#define KIBIC_BAZA_H
#include<iostream>

using namespace std;

class KibicBaza{
    public:
        int klub;
        float x, y;
        KibicBaza(float, float, int);
        virtual ~KibicBaza();
};

#endif // KIBIC_H
