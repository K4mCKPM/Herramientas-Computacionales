#include <fstream>
#include <iostream>
#include <array>
#include <cmath>

// Actualicé el archivo de la entrega anterior, por alguna razón estaba actualizando
// 'T_p' y 'T_p' dentro de un ciclo, por lo que no funcionaba correctamente.

int main(){
    // Condiciones iniciales
    const double V = 1e-4; // Coeficiente de difusión
    const int L = 1;
    const int N = 10; // Cantidad de puntos en una dimensión de la red (10X10)
    const int T = 130; // Pasos temporales
    double t_final = 2600.0;

    // Tomando delta_y igual a delta_x se reduce la complejidad del código.
    double delta_x = 0.1;
    double delta_t = 0.2*delta_x*delta_x/V;

    // Arreglos (matrices i,k) usadas:
    std::array<std::array<double, N>, N> T_f; // T futuro
    std::array<std::array<double, N>, N> T_p; // T presente


    // Condiciones iniciales
    for (int i = 0; i<N; i++){
        for (int k = 0; k<N; k++){
            if (k <= 3 && k >=2 && i<= 5 && i>=4){
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
            T_f[i][k] = T_p[i][k] + 0.25*V*V*delta_t*delta_t*(T_p[i+1][k] + T_p[i-1][k] + T_p[i][k+1] + T_p[i][k-1] - 4*T_p[i][k])/(delta_x*delta_x);
        }
    }


    // Se guardan los archivos en C2_EDP.dat
    // Cada fila representa la 'matriz' como un vector que luego en python se puede reconstruir.
    std::ofstream outfile;
    outfile.open("C2_EDP.dat");

    // Evolución temporal
    for (int j = 0; j<T; j++){
        for (int i = 0; i<N; i++){
            for (int k = 0; k<N; k++){
                // Condiciones de frontera:
                if (i == 0 || i == N-1 || k == 0 || k == N-1){
                    T_f[i][k] = 50.0;
                }
                // Actualización fuera de la frontera
                else{
                T_f[i][k] = T_p[i][k] + V*delta_t*(T_p[i+1][k] + T_p[i-1][k] + T_p[i][k+1] + T_p[i][k-1] - 4*T_p[i][k])/(delta_x*delta_x);
                }
            }
        }
        
        // Guardar algunos arreglos cada 100 segundos en 'C2_EDP.dat'
        if (j%5 == 0){
            for(int p=0; p<N;p++){
                for (int q=0; q<N;q++){
                    outfile << T_p[p][q] << ",";
                }
            }
            outfile << std::endl;
        }   

        // Actualizar los arreglos (matrices) para el siguiente paso
        T_p = T_p;
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

    std::cout << ">>>Guardando los valores en 'C2_EDP.dat'" << std::endl;
    outfile.close();
    
}