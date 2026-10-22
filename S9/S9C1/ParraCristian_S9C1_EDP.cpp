#include <fstream>
#include <iostream>
#include <array>
#include <cmath>
#include <string>

//--- Cambios respecto a la entrega de la semana pasada:
// Ahora las lineas de tiempo se grafican en una sola imagen, esto con el fin
// de separar facilmente las nuevas condiciones de frontera añadidas al código.

// Condiciones iniciales
const double V = 1e-4; // Coeficiente de difusión
const int L = 1;
const int N = 100; // Cantidad de puntos en una dimensión de la red (10X10)
const int T = 13000; // Pasos temporales
double t_final = 26000.0;

// Tomando delta_y igual a delta_x se reduce la complejidad del código.
double delta_x = 0.1;
double delta_t = 0.2*delta_x*delta_x/V;

// Arreglos (matrices i,k) usadas:
std::array<std::array<double, N>, N> T_f; // T futuro
std::array<std::array<double, N>, N> T_p; // T presente

void guardado(int condicion_frontera){
    // Condiciones iniciales
    int arriba = 0.4*N;
    int abajo = 0.2*N;
    int derecha = 0.6*N;
    int izquierda = 0.4*N;
    std::cout << arriba << std::endl;
    std::cout << abajo << std::endl;
    std::cout << derecha << std::endl;
    std::cout << izquierda << std::endl;
    for (int i = 0; i<N; i++){
        for (int k = 0; k<N; k++){
            if (k <= arriba && k >= abajo && i <= derecha && i>= izquierda){
                T_p[i][k] = 100.0;
            }
            else{
                T_p[i][k] = 50.0;
            }
        }
    }

    // Primer paso
    for (int i = 0; i<N; i++){
        for (int k = 0; k<N; k++){
            // Fronteras fijas
            if (condicion_frontera == 0){
                if (i == 0 || i == N-1 || k == 0 || k == N-1){
                    T_f[i][k] = 50.0;
                }
                else{
                T_f[i][k] = T_p[i][k] + 0.25*V*V*delta_t*delta_t*(T_p[i+1][k] + T_p[i-1][k] + T_p[i][k+1] + T_p[i][k-1] - 4*T_p[i][k])/(delta_x*delta_x);
                }
            }

            // Fronteras periodicas
            if (condicion_frontera == 1){
                if (i == 0 || i == N-1 || k == 0 || k == N-1){
                    T_f[0][k] = T_f[N-2][k];
                    T_f[N-1][k] = T_f[1][k];
                    T_f[i][0] = T_f[i][N-2];
                    T_f[i][N-1] = T_f[i][1];
                }
                else{
                T_f[i][k] = T_p[i][k] + 0.25*V*V*delta_t*delta_t*(T_p[i+1][k] + T_p[i-1][k] + T_p[i][k+1] + T_p[i][k-1] - 4*T_p[i][k])/(delta_x*delta_x);
                }
            }

            // Fronteras abiertas
            if (condicion_frontera == 2){
                if (i == 0 || i == N-1 || k == 0 || k == N-1){
                    T_f[0][k] = T_f[1][k];
                    T_f[N-1][k] = T_f[N-2][k];
                    T_f[i][0] = T_f[i][1];
                    T_f[i][N-1] = T_f[i][N-2];
                }
                else{
                T_f[i][k] = T_p[i][k] + 0.25*V*V*delta_t*delta_t*(T_p[i+1][k] + T_p[i-1][k] + T_p[i][k+1] + T_p[i][k-1] - 4*T_p[i][k])/(delta_x*delta_x);
                }
            }
        }
    }

    //--- Condiciones de frontera:
    // 0: Condición dija
    // 1: Condición periódica
    // 2: Condición abierta

    // Se guardan los archivos en C2_EDP_condicion.dat
    // Cada fila representa la 'matriz' como un vector que luego en python se puede reconstruir.
    std::ofstream outfile;
    
    if (condicion_frontera == 0){
        outfile.open("C2_EDP_Fija.dat");
    }
    
    if (condicion_frontera == 1){
        outfile.open("C2_EDP_Periodica.dat");
    }

    if (condicion_frontera == 2){
        outfile.open("C2_EDP_Abierta.dat");

    }
    // Evolución temporal
    for (int j = 0; j<T; j++){
        for (int i = 0; i<N; i++){
            for (int k = 0; k<N; k++){
                // Condiciones de frontera:
                // Fronteras fijas
                if (condicion_frontera == 0){
                    if (i == 0 || i == N-1 || k == 0 || k == N-1){
                    T_f[i][k] = 50.0;
                    }
                    // Actualización fuera de la frontera
                    else{
                    T_f[i][k] = T_p[i][k] + V*delta_t*(T_p[i+1][k] + T_p[i-1][k] + T_p[i][k+1] + T_p[i][k-1] - 4*T_p[i][k])/(delta_x*delta_x);
                    }
                }

                // Fronteras periodicas
                if (condicion_frontera == 1){
                    if (i == 0 || i == N-1 || k == 0 || k == N-1){
                    T_f[0][k] = T_f[N-2][k];
                    T_f[N-1][k] = T_f[1][k];
                    T_f[i][0] = T_f[i][N-2];
                    T_f[i][N-1] = T_f[i][1];
                    }
                    // Actualización fuera de la frontera
                    else{
                    T_f[i][k] = T_p[i][k] + V*delta_t*(T_p[i+1][k] + T_p[i-1][k] + T_p[i][k+1] + T_p[i][k-1] - 4*T_p[i][k])/(delta_x*delta_x);
                    }
                }

                // Fronteras abiertas
                if (condicion_frontera == 2){
                    if (i == 0 || i == N-1 || k == 0 || k == N-1){
                    T_f[0][k] = T_f[1][k];
                    T_f[N-1][k] = T_f[N-2][k];
                    T_f[i][0] = T_f[i][1];
                    T_f[i][N-1] = T_f[i][N-2];
                    }
                    // Actualización fuera de la frontera
                    else{
                    T_f[i][k] = T_p[i][k] + V*delta_t*(T_p[i+1][k] + T_p[i-1][k] + T_p[i][k+1] + T_p[i][k-1] - 4*T_p[i][k])/(delta_x*delta_x);
                    }
                }
            }
        }
        
        // Guardar algunos arreglos cada 100 segundos en 'C2_EDP.dat'
        if (j%500 == 0){
            for(int p=0; p<N;p++){
                for (int q=0; q<N;q++){
                    outfile << T_p[p][q] << ",";
                }
            }
            outfile << std::endl;
        }   

        // Actualizar los arreglos (matrices) para el siguiente paso
        T_p = T_f;
    }
    
    // Se termina de escribir el archivo
    // Se guardan algunos parámetros que pueden ser utiles para reconstruir los datos en python.
    outfile << "# Parámetros del modelo" << std::endl;
    outfile << "# V: " << V << std::endl;
    outfile << "# L: " << L << std::endl;
    outfile << "# N: " << N << std::endl;
    outfile << "# T: " << T << std::endl;
    outfile << "# delta_x: " << delta_x << std::endl;
    outfile << "# delta_t: " << delta_t << std::endl;

    if (condicion_frontera == 0){
    std::cout << ">>>Guardando los valores en 'C2_EDP_Fija.dat'" << std::endl;
    }

    if (condicion_frontera == 1){
    std::cout << ">>>Guardando los valores en 'C2_EDP_Periodica.dat'" << std::endl;
    }

    if (condicion_frontera == 2){
    std::cout << ">>>Guardando los valores en 'C2_EDP_Abierta.dat'" << std::endl;
    }
    outfile.close();
}

int main(){

    // Frontera fija
    guardado(0);

    // Frontera periodica
    guardado(1);

    // Frontera abierta
    guardado(2);

}