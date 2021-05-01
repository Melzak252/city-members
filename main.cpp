#include <iostream>
#include <ctime>
#include <cstdlib>
#include "src/Miasto.cpp"

using namespace std;

int main()
{
    srand(time(NULL));
    int liczba_ludzi;
    float wymiary = 25., promien_sprawdzania = 1., promien_przeprowadzki = 1.0 , stosunek = 0.5;
    cout<<"Prosze o podanie liczby Mieszkancow: ";
    cin>>liczba_ludzi;
    Miasto m(liczba_ludzi, stosunek, wymiary, promien_sprawdzania, promien_przeprowadzki);
    m.zaludnij();
    m.zapisz_i_narysuj();
    for(int i=0; i<20; i++){
        cout<<"Rok: "<<i+1<<endl;
        m.ewoluuj();
    }
    m.zapisz_i_narysuj();
    return 0;
}
