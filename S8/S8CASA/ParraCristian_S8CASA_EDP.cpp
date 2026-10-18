#include <fstream>
#include <iostream>
#include <array>
#include <cmath>
#include <string>

//--- Condiciones iniciales
const int c = 300;          // Velocidad de propagación
const double L = 2.0;       // Posición final de la cuerda
const double h = 0.1;       // Altura inicial del punto central
const int N = 101;          // Cantidad de puntos | Haciendo pruebas es mucho mejor el resultado con N = 1001, pero el ejercicio pide N = 101

double t_final = 0.1;
double delta_x = L/(N - 1);
double delta_t = 0.45*delta_x/c;
const int T = (t_final/delta_t) + 1; // Pasos temporales

//--- Función principal del código:
void onda(double amplitud, std::string nombre){
    // Actualiza los valores de posición de la onda y los guarda en los archivos correspondientes
    //---Parámetros
    // Amplitud : La amplitud de la función sinusoidal que genera el forzamiento
    // nombre : Nombre que va a tener el archivo (dat) donde se guardan las posiciones de la cuerda
    
    //--- Se inicializan los arreglos usados:
    std::array<double, N> u_fut;    // U futuro
    std::array<double, N> u_pres;   // U presente
    std::array<double, N> u_pas;    // U pasado

    //--- Se crea la forma de la cuerda en su posición inicial (triángulo)
    int mitad = N/2;    // Como N/2 = 50.5 para N=101, entonces toma el valor de 50
    for (int i = 0; i<N; i++){      
        if (i <= mitad){    
            u_pas[i] = h*i*delta_x;
        }
        if (i > mitad){
            u_pas[i] =  h*mitad*delta_x - h*(i-mitad)*delta_x;
        }
    }

    //--- Se actualiza el primer paso de la onda
    for (int i = 1; i<N; i++){
        u_pres[i] = u_pas[i] + 0.5*c*c*delta_t*delta_t*(u_pas[i+1] - 2*u_pas[i] + u_pas[i-1])/(delta_x*delta_x);
    }
    u_pres[0] = 0.0;
    u_pres[N-1] = 0.0;

    //--- Se abre el archivo .dat donde se va a guardar el avance temporal de la cuerda
    std::ofstream outfile;
    outfile.open(nombre);

    // Evolución temporal
    for (int k = 0; k<T; k++){
        // Se calcula el arreglo "futuro"
        for (int j = 1; j<N; j++){
            u_fut[j] = 2*u_pres[j] - u_pas[j] 
                    + c*c*delta_t*delta_t*(u_pres[j+1] - 2*u_pres[j] + u_pres[j-1])/(delta_x*delta_x);
        }
        u_fut[0] = 0.0;
        u_fut[N-1] = amplitud*std::sin(M_PI*k/871);
        

        // Guardar algunos arreglos "futuro" en 'EDP_.dat'
        if (k%(N-1) == 0){
            for(int p=0; p<(N-1);p++){
            outfile << u_fut[p] << "," ;
            }

            outfile << u_fut[N-1] << std::endl;
        }   

        // Actualizar los arreglos
        u_pas = u_pres;
        u_pres = u_fut;
    }

    //--- Se termina de escribir el archivo
    std::cout << ">>>Guardando los valores en " << nombre << std::endl;
    outfile.close();
}


int main(){
    // Se llama a la función onda con ambos extremos fijos, y se guarda en 'EDP_Fijo,dat'
    onda(0.0, "EDP_Fijo.dat");

    // Se llama a la función onda con el extremo derecho forzado, y se guarda en 'EDP_Forzado,dat'
    onda(0.05, "EDP_Forzado.dat");

    return 0;
}