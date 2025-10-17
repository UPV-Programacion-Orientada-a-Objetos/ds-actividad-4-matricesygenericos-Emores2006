#ifndef CAMPO2D_H
#define CAMPO2D_H

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

template <typename T>
class Campo2D {
private:
    T** matriz;
    int filas;
    int columnas;

public:
    // Constructor
    Campo2D(int f, int c);
    // Destructor
    ~Campo2D();
    // Redimensionar la matriz
    void redimensionar(int nuevaF, int nuevaC);
    // Establecer valor en una posicion
    void setValor(int f, int c, T valor);
    // Obtener valor en una posicion
    T getValor(int f, int c);
    // Calcular gradiente promedio en una region
    T calcularGradientePromedio(int inicioF, int finF, int inicioC, int finC);
    // Mostrar la matriz
    void mostrarGrid();
    // Menu principal
    void menu();
};

// =========================================================
// DEFINICION/IMPLEMENTACION DE LOS METODOS
// =========================================================

template <typename T>
Campo2D<T>::Campo2D(int f, int c) : filas(f), columnas(c) {
    matriz = new T*[filas];
    for (int i = 0; i < filas; i++) {
        matriz[i] = new T[columnas];
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = 0;
        }
    }
    std::cout << "Creando Grid de " << filas << "x" << columnas << "..." << std::endl;
}

template <typename T>
Campo2D<T>::~Campo2D() {
    std::cout << "Destructor invocado. Liberando memoria de la Matriz 2D..." << std::endl;
    if (matriz != nullptr) {
        for (int i = 0; i < filas; i++) {
            delete[] matriz[i];
        }
        delete[] matriz;
        matriz = nullptr;
    }
}

template <typename T>
void Campo2D<T>::setValor(int f, int c, T valor) {
    if (f >= 0 && f < filas && c >= 0 && c < columnas) {
        matriz[f][c] = valor;
    } else {
        std::cout << "Indice fuera de rango." << std::endl;
    }
}

template <typename T>
T Campo2D<T>::getValor(int f, int c) {
    if (f >= 0 && f < filas && c >= 0 && c < columnas) {
        return matriz[f][c];
    }
    return 0;
}

template <typename T>
void Campo2D<T>::redimensionar(int nuevaF, int nuevaC) {
    std::cout << "\nRedimensionando Grid de " << filas << "x" << columnas
              << " a " << nuevaF << "x" << nuevaC << "..." << std::endl;

    srand(time(0));

    // Crear nueva matriz
    T** matriz_aux = new T*[nuevaF];
    for (int i = 0; i < nuevaF; i++) {
        matriz_aux[i] = new T[nuevaC];
        for (int j = 0; j < nuevaC; j++) {
            matriz_aux[i][j] = 0;
        }
    }

    // Copiar datos existentes
    int minF = (filas < nuevaF) ? filas : nuevaF;
    int minC = (columnas < nuevaC) ? columnas : nuevaC;

    for (int i = 0; i < minF; i++) {
        for (int j = 0; j < minC; j++) {
            matriz_aux[i][j] = matriz[i][j];
        }
    }

    // Rellenar datos faltantes con valores aleatorios
    for (int i = 0; i < nuevaF; i++) {
        for (int j = 0; j < nuevaC; j++) {
            if (i >= minF || j >= minC) {
                T valor_aleatorio = (T)(rand() % 20 + 1);
                matriz_aux[i][j] = valor_aleatorio;
            }
        }
    }

    // Liberar matriz antigua
    for (int i = 0; i < filas; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;

    // Asignar nueva matriz
    matriz = matriz_aux;
    filas = nuevaF;
    columnas = nuevaC;

    std::cout << "Datos copiados y rellenados con valores aleatorios. Memoria antigua liberada." << std::endl;
}

template <typename T>
T Campo2D<T>::calcularGradientePromedio(int inicioF, int finF, int inicioC, int finC) {
    // Validar limites
    if (inicioF < 0 || finF >= filas || inicioC < 0 || finC >= columnas ||
        inicioF > finF || inicioC > finC) {
        std::cout << "Region invalida." << std::endl;
        return 0;
    }

    T sumaGradiente = 0;
    int contador = 0;

    // Recorrer cada celda en la region
    for (int i = inicioF; i <= finF; i++) {
        for (int j = inicioC; j <= finC; j++) {
            T gradienteCelda = 0;
            int vecinos = 0;

            // Vecino derecha (se mantiene tu lógica de solo vecino dentro de la subregión)
            if (j + 1 <= finC) {
                gradienteCelda += (T)std::abs(matriz[i][j + 1] - matriz[i][j]);
                vecinos++;
            }

            // Vecino abajo (se mantiene tu lógica de solo vecino dentro de la subregión)
            if (i + 1 <= finF) {
                gradienteCelda += (T)std::abs(matriz[i + 1][j] - matriz[i][j]);
                vecinos++;
            }

            if (vecinos > 0) {
                // CAMBIO 1: Forzar la división a double para obtener el promedio decimal de la celda.
                sumaGradiente += (T)((double)gradienteCelda / vecinos);
                contador++;
            }
        }
    }

    if (contador > 0) {
        // CAMBIO 2: Forzar la división a double para obtener el promedio final.
        return (T)((double)sumaGradiente / contador);
    }
    return 0;
}

template <typename T>
void Campo2D<T>::mostrarGrid() {
    std::cout << "\nGrid Actual:" << std::endl;
    for (int i = 0; i < filas; i++) {
        std::cout << "| ";
        for (int j = 0; j < columnas; j++) {
            std::cout << matriz[i][j] << " | ";
        }
        std::cout << std::endl;
    }
}

template <typename T>
void Campo2D<T>::menu() {
    int res = 0;

    std::cout << "\n--- Simulador Genérico de Campo 2D ---\n" << std::endl;
    std::cout << ">> Inicializando Campo Gravitatorio (Tipo FLOAT) <<" << std::endl;

    // Crear el campo
    Campo2D<float> campo(3, 3);
    std::cout << "Estableciendo valores iniciales..." << std::endl;

    // Establecer valores iniciales
    campo.setValor(0, 0, 10.0);
    campo.setValor(0, 1, 8.0);
    campo.setValor(0, 2, 5.0);
    campo.setValor(1, 0, 12.0);
    campo.setValor(1, 1, 9.0);
    campo.setValor(1, 2, 6.0);
    campo.setValor(2, 0, 15.0);
    campo.setValor(2, 1, 11.0);
    campo.setValor(2, 2, 7.0);

    campo.mostrarGrid();

    do {
        std::cout << "\n--- Menu de acciones ---" << std::endl;
        std::cout << "1. Calcular Gradiente Promedio" << std::endl;
        std::cout << "2. Redimensionar" << std::endl;
        std::cout << "3. Salir" << std::endl;
        std::cout << "\nOpcion seleccionada: ";
        std::cin >> res;

        switch (res) {
            case 1: {
                std::cout << "\nOpcion seleccionada: " << res << std::endl;
                
                int inicioF_usuario, finF_usuario, inicioC_usuario, finC_usuario;
                
                // Pedir límites basados en 1 al usuario
                std::cout << "Ingrese Fila Inicial (1 a " << campo.filas << "): ";
                std::cin >> inicioF_usuario;
                std::cout << "Ingrese Fila Final (1 a " << campo.filas << "): ";
                std::cin >> finF_usuario;
                std::cout << "Ingrese Columna Inicial (1 a " << campo.columnas << "): ";
                std::cin >> inicioC_usuario;
                std::cout << "Ingrese Columna Final (1 a " << campo.columnas << "): ";
                std::cin >> finC_usuario;

                // Converison a matriz (posiciones)
                int inicioF = inicioF_usuario - 1;
                int finF = finF_usuario - 1;
                int inicioC = inicioC_usuario - 1;
                int finC = finC_usuario - 1;
                
                std::cout << "\nCalculando Gradiente Promedio en la region (Índice 0-basado) [" << inicioF_usuario << ","
                          << finF_usuario << "]x[" << inicioC_usuario << "," << finC_usuario << "]..." << std::endl;

                float gradiente = campo.calcularGradientePromedio(inicioF, finF, inicioC, finC);
                std::cout << "Gradiente Promedio calculado: " << gradiente << " unidades/metro." << std::endl;
                break;
            }

            case 2: {
                std::cout << "\nOpcion seleccionada: " << res << std::endl;
                int nuevaF, nuevaC;
                std::cout << "Tamano actual: " << campo.filas << "x" << campo.columnas << std::endl;
                std::cout << "Ingrese nuevo numero de filas: ";
                std::cin >> nuevaF;
                std::cout << "Ingrese nuevo numero de columnas: ";
                std::cin >> nuevaC;
                campo.redimensionar(nuevaF, nuevaC);
                campo.mostrarGrid();
                break;
            }

            case 3:
                std::cout << "\nOpcion seleccionada: " << res << std::endl;
                std::cout << "Sistema cerrado." << std::endl;
                break;

            default:
                std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
        }

    } while (res != 3);
}

#endif // CAMPO2D_H