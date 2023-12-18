#include <iostream>
#include <string>
#include <cmath>
#include <fstream>


#include "Poly.h"


using namespace std;




int main(void)
{
    int n;
    cout<<"digite o grau do polinomio"<<endl;
    cin>>n;
    Poly P(n);
    cin>>P;
    cout<<P<<endl;
    for(int j = 0; j<=P.getGrau(); j++){
        P.setCoef(j,2*j);
    }
    cout<<P<<endl;


  return 0;
}
