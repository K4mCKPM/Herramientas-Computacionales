#include <fstream>
#include <iostream>
#include <array>
#include <cmath>

// No logré que la cuerda bajara a alturas negativas.

int main(){
    // Condiciones iniciales
    const int c = 300;
    const int L = 2;
    const int N = 101; // Cantidad de puntos
    const int T = 100000; // Pasos temporales
    double h = 0.1; // Altura inicial
    double v = 0.0; // Velocidad inicial | No la he aplicado
    double t_final = 0.1;
    double delta_x = 2.0/101.0;
    double delta_t = 0.5*delta_x/c;

    // Arreglos usados:
    std::array<double, N> u_fut; // U futuro
    std::array<double, N> u_pres; // U presente
    std::array<double, N> u_pas; // U pasado

    for (int i = 0; i<N-1; i++){
        if (i < 51){    
            u_pas[i] = 0.1*i*delta_x;
        }
        if (i > 50){
            u_pas[i] =  0.1*50*delta_x - 0.1*(i-50)*delta_x;
        }
    }

    // Primer paso
    for (int i = 1; i<N-1; i++){
        u_pres[i] = u_pas[i] + 0.5*c*c*delta_t*delta_t*(u_pas[i+1] - 2*u_pas[i] + u_pas[i-1])/(delta_x*delta_x);
    }
    
    // Se guardan los archivos en EDP.dat
    // El orden de las columnas es: 
    // arreglo posiciones en tiempo
    std::ofstream outfile;
    outfile.open("EDP.dat");
    

    // Comentario con el nombre de las columnas
    outfile << "#Amplitud de los puntos"  << "\n";

    // Evolución temporal
    for (int k = 0; k<T; k++){
        // Se calcula el arreglo "futuro"
        for (int j = 1; j<N-1; j++){
            u_fut[j] = 2*u_pres[j] - u_pas[j] 
            + c*c*delta_t*delta_t*(u_pres[j+1] - 2*u_pres[j] + u_pres[j-1])/(delta_x*delta_x);
        }
        
        // Guardar algunos arreglos "pasado" en 'EDP.dat'
        if (k%100 == 0){
            for(int p=0; p<(N-1);p++){
            outfile << u_pas[p] << "," ;
            }

            outfile << u_pas[N-1] << std::endl;
        }   
        // Actualizar los arreglos
        for (int i = 0; i<N; i++){
            u_pas = u_pres;
            u_pres = u_fut;
        }
    }
    
    // Se termina de escribir el archivo
    std::cout << ">>>Guardando los valores en 'EDP.dat'" << std::endl;
    outfile.close();
    
}