#ifndef MIASTO_H
#define MIASTO_H
#include"Kibic.h"
#include<vector>



class Miasto
{
    public:
        int liczba_kibicow;
        std::vector<std::vector<Kibic>>pola_miasta;
        std::vector<Kibic> kibice;
        float promien_sprawdzania, promien_przeprowadzki, wymiary, stosunek;

        Miasto(int, float, float, float, float);
        virtual ~Miasto();

        void zaludnij();
        void zapisz_i_narysuj();
        void ewoluuj();
    private:
};

#endif // MIASTO_H
