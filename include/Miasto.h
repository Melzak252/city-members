#ifndef MIASTO_H
#define MIASTO_H
#include"Kibic.h"
#include<vector>



class Miasto
{
    public:
        int liczba_kibicow;
        std::vector<Kibic> kibice;
        float promien_sprawdzania, promien_przeprowadzki, wymiary;

        Miasto(int, float, float);
        virtual ~Miasto();

        void zaludnij();
        void zapisz_i_narysuj();
        void ewoluuj();
    protected:

    private:
        float RandomFloat(float, float);
};

#endif // MIASTO_H
