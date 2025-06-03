#include <iostream>
using namespace std;

int main(){
int Kwh, tarifa;
double precio = 1.50;
cout << "Ingrese su tarifa de luz: " <<endl;
cin >> Kwh;

if (Kwh < 100)
{
    cout << "Su tarifa de Luz es baja. " <<endl;
}
else if (Kwh >= 100 && Kwh <= 200)
{
cout << "Su tarifa de luz es media" <<endl;    
}

else if (Kwh > 200)
{
    cout << "Su tarifa de Luz es alta. " <<endl;
}

else
{
  cout <<"Esa no es una opcion. " <<endl;
}

if (tarifa = Kwh * precio)
{
    cout <<"El precio de su tarifa de luz es:$ " << tarifa <<endl;
}

else
{}

cout << "Gracias por utilizar el programa. " <<endl;

 





    return 0;
}