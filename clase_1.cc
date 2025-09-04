#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

std::string GenerarCupon(std::string PEH){
    int numeroAleatorio = 100 + (rand() % 900); 
    std::string cupon = PEH + std::to_string(numeroAleatorio);
    return cupon;
}

bool VerificarPremio(std::string cupon) {
    int numero = std::stoi(cupon.substr(cupon.length() - 3));
    return (numero % 2 == 0);
}

std::string SolicitarYValidarLetras() {
    std::string letras;
    bool esValido = false;
    
    while (!esValido) {
        std::cout << "Ingrese las letras del cupon (3 caracteres): ";
        std::cin >> letras;
        
        // Validar longitud
        if (letras.length() == 3) {
            // Validar que solo contenga letras
            bool soloLetras = true;
            for (char c : letras) {
                if (!isalpha(c)) {
                    soloLetras = false;
                    break;
                }
            }
            
            if (soloLetras) {
                // Convertir a mayúsculas
                for (char &c : letras) {
                    c = toupper(c);
                }
                esValido = true;
            } else {
                std::cout << "Error: Solo se permiten letras.\n";
            }
        } else {
            std::cout << "Error: Debe tener exactamente 3 caracteres.\n";
        }
    }
    
    return letras;
}

int SolicitarCantidadCupones() {
    int cantidad;
    do {
        std::cout << "Ingrese la cantidad de cupones a generar (minimo 1): ";
        std::cin >> cantidad;
        if (cantidad < 1) {
            std::cout << "Error: La cantidad debe ser mayor a 0.\n";
        }
    } while (cantidad < 1);
    
    return cantidad;
}

int main(){
    srand(time(0)); 
    
    std::string letrasUsuario = SolicitarYValidarLetras();
    int cantidadCupones = SolicitarCantidadCupones();
    
    // Crear arreglo de cupones
    std::vector<std::string> cupones(cantidadCupones);
    
    // Generar cupones
    for (int i = 0; i < cantidadCupones; i++) {
        cupones[i] = GenerarCupon(letrasUsuario);
    }
    
    // Mostrar cupones y verificar premios
    std::cout << "\nCupones generados:\n";
    int cuponesConPremio = 0;
    
    for (int i = 0; i < cantidadCupones; i++) {
        std::cout << "Cupon " << (i + 1) << ": " << cupones[i];
        
        bool tienePremio = VerificarPremio(cupones[i]);
        if (tienePremio) {
            std::cout << " - TIENE PREMIO";
            cuponesConPremio++;
        } else {
            std::cout << " - No tiene premio";
        }
        std::cout << std::endl;
    }
    
    std::cout << "\nResumen: " << cuponesConPremio << " de " << cantidadCupones 
              << " cupones tienen premio." << std::endl;

    return 0;
}