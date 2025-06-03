#include <iostream>
using namespace std;
int main(){
int num1, suma = 0;

cout << "Por favor ingrese un numero: " <<endl;
cin >>num1;

for (; num1 > 0; num1 /=10 )
{
    int numero = num1 % 10;
    suma += numero;
}

    cout << "La suma de los numeros es: " << suma <<endl;




    return 0;
}