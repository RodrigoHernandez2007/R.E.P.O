#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <fstream>

// Estructura para almacenar informacion del cantante
struct Cantante {
    std::string nombre;
    std::string nacionalidad;
    int anioNacimiento;
    std::string generoMusical;
};

// Estructura para almacenar informacion del album
struct Album {
    std::string nombreAlbum;
    Cantante artista;
    int anioLanzamiento;
    int numeroTemas;
    std::string discografica;
    int aniosTranscurridos; // Se calculara automaticamente
};

// Funcion para registrar informacion del album y cantante
struct Album registrarAlbum() {
    Album nuevoAlbum;
    
    std::cout << "=== REGISTRO DE ALBUM ===" << std::endl;
    std::cout << "Ingrese el nombre del album: ";
    std::cin.ignore(); // Limpiar buffer
    getline(std::cin, nuevoAlbum.nombreAlbum);
    
    std::cout << "\n--- Informacion del Artista ---" << std::endl;
    std::cout << "Ingrese el nombre del cantante/artista: ";
    getline(std::cin, nuevoAlbum.artista.nombre);
    
    std::cout << "Ingrese la nacionalidad del artista: ";
    getline(std::cin, nuevoAlbum.artista.nacionalidad);
    
    std::cout << "Ingrese el ano de nacimiento del artista: ";
    std::cin >> nuevoAlbum.artista.anioNacimiento;
    
    std::cout << "Ingrese el genero musical del artista: ";
    std::cin.ignore();
    getline(std::cin, nuevoAlbum.artista.generoMusical);
    
    std::cout << "\n--- Informacion del Album ---" << std::endl;
    std::cout << "Ingrese el ano de lanzamiento: ";
    std::cin >> nuevoAlbum.anioLanzamiento;
    
    std::cout << "Ingrese el numero de temas: ";
    std::cin >> nuevoAlbum.numeroTemas;
    
    std::cout << "Ingrese la discografica: ";
    std::cin.ignore();
    getline(std::cin, nuevoAlbum.discografica);
    
    // Inicializar anos transcurridos en 0, se calculara despues
    nuevoAlbum.aniosTranscurridos = 0;
    
    std::cout << "Album registrado exitosamente!" << std::endl << std::endl;
    return nuevoAlbum;
}

// Funcion para mostrar todos los albums registrados y permitir seleccionar uno
void mostrarListaAlbumes(const std::vector<Album>& albums) {
    if (albums.empty()) {
        std::cout << "No hay albums registrados." << std::endl << std::endl;
        return;
    }
    
    std::cout << "=== LISTA DE ALBUMS REGISTRADOS ===" << std::endl;
    for (int i = 0; i < albums.size(); i++) {
        std::cout << (i + 1) << ". " << albums[i].nombreAlbum << " - " << albums[i].artista.nombre << std::endl;
    }
    std::cout << "===================================" << std::endl << std::endl;
}

// Funcion para mostrar todos los datos del album y cantante
void mostrarDatosAlbum(const Album& album) {
    std::cout << "=== INFORMACION DEL ALBUM ===" << std::endl;
    std::cout << "Nombre del album: " << album.nombreAlbum << std::endl;
    std::cout << "Ano de lanzamiento: " << album.anioLanzamiento << std::endl;
    std::cout << "Numero de temas: " << album.numeroTemas << std::endl;
    std::cout << "Discografica: " << album.discografica << std::endl;
    std::cout << "Anos transcurridos desde el lanzamiento: " << album.aniosTranscurridos << std::endl;
    std::cout << "\n--- INFORMACION DEL ARTISTA ---" << std::endl;
    std::cout << "Nombre: " << album.artista.nombre << std::endl;
    std::cout << "Nacionalidad: " << album.artista.nacionalidad << std::endl;
    std::cout << "Ano de nacimiento: " << album.artista.anioNacimiento << std::endl;
    std::cout << "Genero musical: " << album.artista.generoMusical << std::endl;
    std::cout << "================================" << std::endl << std::endl;
}

// Funcion para calcular anos transcurridos desde el lanzamiento (arreglada)
int calcularAniosTranscurridos(Album& album) {
    // Obtener la fecha actual
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    int anioActual = now->tm_year + 1900;
    
    // Calcular anos transcurridos
    int anios = anioActual - album.anioLanzamiento;
    
    // Validar que el resultado sea logico
    if (anios < 0) {
        std::cout << "Advertencia: El ano de lanzamiento es futuro. Estableciendo anos transcurridos en 0." << std::endl;
        anios = 0;
    }
    
    // Almacenar el valor en la estructura
    album.aniosTranscurridos = anios;
    
    return anios;
}

// Funcion para guardar datos en archivo
void guardarDatos(const std::vector<Album>& albums) {
    std::ofstream archivo("albums_data.txt");
    if (!archivo.is_open()) {
        std::cout << "Error al crear archivo de datos." << std::endl;
        return;
    }
    
    archivo << albums.size() << std::endl;
    for (const Album& album : albums) {
        archivo << album.nombreAlbum << "|"
                << album.artista.nombre << "|"
                << album.artista.nacionalidad << "|"
                << album.artista.anioNacimiento << "|"
                << album.artista.generoMusical << "|"
                << album.anioLanzamiento << "|"
                << album.numeroTemas << "|"
                << album.discografica << "|"
                << album.aniosTranscurridos << std::endl;
    }
    archivo.close();
    std::cout << "Datos guardados exitosamente!" << std::endl;
}

// Funcion para cargar datos desde archivo
void cargarDatos(std::vector<Album>& albums) {
    std::ifstream archivo("albums_data.txt");
    if (!archivo.is_open()) {
        return; // No hay archivo previo, iniciar vacio
    }
    
    int numAlbums;
    archivo >> numAlbums;
    archivo.ignore(); // Ignorar el salto de linea
    
    for (int i = 0; i < numAlbums; i++) {
        Album album;
        std::string linea;
        getline(archivo, linea);
        
        // Parsear la linea usando el delimitador |
        size_t pos = 0;
        std::string token;
        std::vector<std::string> datos;
        
        while ((pos = linea.find("|")) != std::string::npos) {
            token = linea.substr(0, pos);
            datos.push_back(token);
            linea.erase(0, pos + 1);
        }
        datos.push_back(linea); // El ultimo elemento
        
        if (datos.size() == 9) {
            album.nombreAlbum = datos[0];
            album.artista.nombre = datos[1];
            album.artista.nacionalidad = datos[2];
            album.artista.anioNacimiento = std::stoi(datos[3]);
            album.artista.generoMusical = datos[4];
            album.anioLanzamiento = std::stoi(datos[5]);
            album.numeroTemas = std::stoi(datos[6]);
            album.discografica = datos[7];
            album.aniosTranscurridos = std::stoi(datos[8]);
            
            albums.push_back(album);
        }
    }
    archivo.close();
}

// Funcion principal para demostrar el uso
int main() {
    std::vector<Album> albums; // Vector para almacenar multiples albums
    int opcion;
    
    // Cargar datos previos al iniciar
    cargarDatos(albums);
    if (!albums.empty()) {
        std::cout << "Se cargaron " << albums.size() << " albums previamente guardados." << std::endl << std::endl;
    }
    
    do {
        std::cout << "=== SISTEMA DE GESTION DE ALBUMES ===" << std::endl;
        std::cout << "1. Registrar album" << std::endl;
        std::cout << "2. Mostrar informacion del album" << std::endl;
        std::cout << "3. Calcular anos transcurridos" << std::endl;
        std::cout << "4. Mostrar todos los albums" << std::endl;
        std::cout << "5. Guardar datos" << std::endl;
        std::cout << "6. Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;
        
        switch(opcion) {
            case 1: {
                Album nuevoAlbum = registrarAlbum();
                albums.push_back(nuevoAlbum);
                std::cout << "Album agregado a la coleccion!" << std::endl << std::endl;
                break;
            }
            case 2: {
                if (albums.empty()) {
                    std::cout << "No hay albums registrados. Por favor registre uno primero." << std::endl << std::endl;
                } else {
                    mostrarListaAlbumes(albums);
                    std::cout << "Seleccione el numero del album que desea ver: ";
                    int seleccion;
                    std::cin >> seleccion;
                    
                    if (seleccion >= 1 && seleccion <= albums.size()) {
                        mostrarDatosAlbum(albums[seleccion - 1]);
                    } else {
                        std::cout << "Seleccion invalida." << std::endl << std::endl;
                    }
                }
                break;
            }
            case 3: {
                if (albums.empty()) {
                    std::cout << "No hay albums registrados. Por favor registre uno primero." << std::endl << std::endl;
                } else {
                    mostrarListaAlbumes(albums);
                    std::cout << "Seleccione el numero del album para calcular anos transcurridos: ";
                    int seleccion;
                    std::cin >> seleccion;
                    
                    if (seleccion >= 1 && seleccion <= albums.size()) {
                        int anios = calcularAniosTranscurridos(albums[seleccion - 1]);
                        std::cout << "Han transcurrido " << anios << " anos desde el lanzamiento del album '" 
                             << albums[seleccion - 1].nombreAlbum << "'." << std::endl << std::endl;
                    } else {
                        std::cout << "Seleccion invalida." << std::endl << std::endl;
                    }
                }
                break;
            }
            case 4: {
                mostrarListaAlbumes(albums);
                break;
            }
            case 5: {
                guardarDatos(albums);
                std::cout << std::endl;
                break;
            }
            case 6:
                // Guardar automaticamente al salir
                if (!albums.empty()) {
                    guardarDatos(albums);
                }
                std::cout << "Gracias por usar el sistema!" << std::endl;
                break;
            default:
                std::cout << "Opcion invalida. Intente nuevamente." << std::endl << std::endl;
        }
    } while(opcion != 6);
    
    return 0;
}