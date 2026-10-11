#include <fstream>
#include <iostream>
#include <array>
#include <cmath>

// Me falta conseguir guardar el avance temporal

int main(){
    // Condiciones iniciales
    const int c = 300;
    const int L = 2;
    const int N = 101; // Cantidad de puntos
    const int T = 100; // Pasos temporales
    double h = 0.1; // Altura inicial
    double v = 0.0; // Velocidad inicial 
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

    for (int i = 0; i<N; i++){
        u_pres[i] = u_pas[i];
    }
    // Primer paso
    
    // Se guardan los archivos en EDP.dat
    // El orden de las columnas es: 
    // tiempo ; arreglo posiciones en tiempo
    std::ofstream outfile;
    outfile.open("EDP.dat");
    

    // Comentario con el nombre de las columnas
    outfile << "#Tiempo, Amplitud de los puntos"  << "\n";

    for(int p=0; p<(N);p++){
    outfile << u_pas[p] << "," ;
    }
    std::cout << ">>>Guardando los valores en 'EDP.dat'" << std::endl;
    outfile.close();

    // Evolución temporal
    for (int k = 0; k<T; k++){
        // Se calcula el arreglo "futuro"
        for (int j = 1; j<N-1; j++){
            u_fut[j] = u_pres[j] - u_pas[j] 
            + c*c*delta_t*delta_t*(u_pres[j+1] - 2*u_pres[j] + u_pres[j-1])/(delta_x*delta_x);
        }
        // Actualizar los arreglos
        for (int i = 0; i<N; i++){
            u_pas = u_pres;
            u_pres = u_fut;
        }

        // Se escribe la fila k del archivo
        //outfile << k*(T/t_final) << " , " << 
        //for (int k = 0; k<N; k++){
        //    u_fut[k] << " , "
        //} << std::endl;
    }

    
    // Se termina de escribir el archivo

    
}