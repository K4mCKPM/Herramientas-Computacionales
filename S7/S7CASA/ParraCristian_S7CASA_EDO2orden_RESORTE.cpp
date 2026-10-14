#include <fstream>
#include <iostream>
#include <array>
#include <string>

//--- Cambios respecto a la entrega anterior:
//- Reuní la función amortiguada dentro de la general, si es amortiguada se le pasa el parámetro bb = b, 
// si no es amortiguada se le pasa bb = 0.0, y la función se comporta como la función normal.
//- Reduje las funciones a la mitad, mezclando la posición y la velocidad en la misma función y usando
// un arreglo para guardar los valores respectivos.
//- Dentro del archivo 'EDO2.dat' ahora se guardan también los valores de m, k, b y h, que luego se usan
// en la parte de gráficas para mostrar en las imagenes los parámetros usados.

double Funcion(double yy, double vv, double mm, double kk, double bb){
    // La función a la que se le va a resolver la EDO de segundo orden d²y/dt² = f(y)
  return - (kk/mm) * yy - bb*vv;
}

std::array<double, 2> Euler(double yy, double vv, double hh, double mm, double kk,  double bb){
    // yy : El valor de la función en el paso n actual
    // vv ; El valor de la velocidad en el paso n actual
    // hh : El tamaño de paso inicialmente definido
    double yy_n1 = yy + hh*vv;
    double vv_n1 = vv + hh*Funcion(yy, vv, mm, kk, bb);
    return {yy_n1, vv_n1};
}

std::array<double, 2> Leap_Frog(double yy, double vv, double hh, double mm, double kk,  double bb){
    // yy : El valor de la función en el paso n actual
    // vv : El valor de la velocidad en el paso n+1/2 actual
    // hh : El tamaño de paso inicialmente definido
    double yy_n1 = yy + hh*vv;                // yy_n+1
    double vv_n32 = vv + hh*Funcion(yy_n1, vv, mm, kk, bb);   // vv_n+3/2
    return {yy_n1, vv_n32};
}

std::array<double, 2> RK4(double yy, double vv, double hh, double mm, double kk,  double bb){
    // yy : El valor de la función en el paso n actual
    // vv : El valor de la velocidad en el paso n actual
    // hh : El tamaño de paso inicialmente definido
    double k1_x = hh*vv;
    double k1_v = hh*Funcion(yy, vv, mm, kk, bb);

    double k2_x = hh*(vv + k1_v/2);
    double k2_v = hh*Funcion(yy + k1_x/2, vv + k1_v/2, mm, kk, bb);
    
    double k3_x = hh*(vv + k2_v/2);
    double k3_v = hh*Funcion(yy + k2_x/2, vv + k2_v/2, mm, kk, bb);
    
    double k4_x = hh*(vv + k3_v);
    double k4_v = hh*Funcion(yy + k3_x, vv + k3_v, mm, kk, bb);
    
    double Ax_RK = yy + (k1_x + 2*k2_x + 2*k3_x + k4_x)/6.0;
    double Avx_RK = vv + (k1_v + 2*k2_v + 2*k3_v + k4_v)/6.0;
    
    return {Ax_RK, Avx_RK};
}

int main(){
    double m = 0.2;  // m
    double k = 50.0;   // N/m
    const int N = 1000;
    const double t_final = 2.0;// s
    double h = t_final/N;
    double b = 0.8;

    //--- Se inicializan los arreglos
    std::array<double, N> t;

    // Sin amortiguamiento
    std::array<double, N> x_Euler;
    std::array<double, N> vx_Euler;
    std::array<double, N> x_LF;
    std::array<double, N> vx_LF;

    // Con amortiguamiento
    std::array<double, N> Ax_Euler;
    std::array<double, N> Avx_Euler;
    std::array<double, N> Ax_RK;
    std::array<double, N> Avx_RK;
    
    
    //--- Se escogen las condiciones iniciales
    double x0 = 0.1;
    double vx0 = 0.0;
    t[0] = 0.0;
    // Método de Euler
    x_Euler[0] = x0;
    vx_Euler[0] = vx0;
    
    // Método de Leap Frog
    x_LF[0] = x0;
    vx_LF[0] = vx0 + h * Funcion(x0, vx0, m, k, b)/2.0;

    // Método de Euler Amortiguado
    Ax_Euler[0] = x0;
    Avx_Euler[0] = vx0;
    
    // Método de RK4 Amortiguado
    Ax_RK[0] = x0;
    Avx_RK[0] = vx0;

    // Escribo los valores de todos los arreglos
    for (int i = 0; i < N-1; i++){
        t[i+1] = (i+1)*h;

        // Sin amortiguar
        x_Euler[i+1] = Euler(x_Euler[i], vx_Euler[i], h, m, k, 0)[0];
        vx_Euler[i+1] = Euler(x_Euler[i], vx_Euler[i], h, m, k, 0)[1];
        x_LF[i+1] = Leap_Frog(x_LF[i], vx_LF[i], h, m, k, 0)[0];
        vx_LF[i+1] = Leap_Frog(x_LF[i], vx_LF[i], h, m, k, 0)[1];
        
        // Amortiguado
        Ax_Euler[i+1] = Euler(Ax_Euler[i], Avx_Euler[i], h, m, k, b)[0];
        Avx_Euler[i+1] = Euler(Ax_Euler[i], Avx_Euler[i], h, m, k, b)[1];
        Ax_RK[i+1] = RK4(Ax_RK[i], Avx_RK[i], h, m, k, b)[0];
        Avx_RK[i+1] = RK4(Ax_RK[i], Avx_RK[i], h, m, k, b)[1];
    }

    // Se guardan los archivos en EDO2.dat
    // El orden de las columnas es: tiempo , Euler , LeapFrog,
    // Euler Amortiguado, RK4 amortiguado
    std::ofstream outfile;
    outfile.open("EDO2.dat");
    std::cout << ">>>Guardando los valores en 'EDO2.dat'" << std::endl;

    // Comentario con el nombre de las columnas
    outfile << "#Tiempo, Euler, LeapFrog, Euler Amortiguado, RK4 Amortiguado" << "\n";

    // Se escriben los valores de todos los arreglos
    for(int w=0; w<(N);w++){
    outfile << t[w] << " , " << x_Euler[w] << " , " << x_LF[w] 
    << " , " << Ax_Euler[w] << " , " << Ax_RK[w] << "\n";
    }

    // Comentario adicional para guardar los parámetros del resorte:
    outfile << "#m, k, b, h, 0.0" << "\n";
    outfile << m << " , " << k << " , " << b << " , " << h << " , " << "0.0" << "\n";

    outfile.close();

    return 0;
}