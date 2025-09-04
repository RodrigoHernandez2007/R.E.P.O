#include <iostream>
#include <iomanip>

double radio(double r) {
    return 3.1416 * r * r;
}

int main(){
    double r;
    std::cout << "Ingrese el radio: ";
    std::cin >> r;
    std::cout << "El area es: " << std::fixed << std::setprecision(2) << radio(r) << std::endl;
    return 0;
}