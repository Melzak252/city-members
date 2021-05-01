#include <iostream>
#include <ctime>
#include <cstdlib>
#include "src/Miasto.cpp"

using namespace std;

int main()
{
    int liczba_ludzi;
    float wymiary = 25.;
    cout<<"Prosze o podanie liczby Mieszkancow: ";
    cin>>liczba_ludzi;
    Miasto m(liczba_ludzi, wymiary, 10.);
    m.zaludnij();
    m.zapisz_i_narysuj();
    for(int i=0; i<20; i++){
        cout<<"Rok: "<<i+1<<endl;
        m.ewoluuj();
    }
    m.zapisz_i_narysuj();
    return 0;
}
