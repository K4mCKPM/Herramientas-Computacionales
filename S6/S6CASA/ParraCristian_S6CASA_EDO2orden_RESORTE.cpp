#include <fstream>
#include <iostream>
#include <array>
#include <string>

double Funcion(double yy, double mm, double kk){
    // La función a la que se le va a resolver la EDO de segundo orden d²y/dt² = -k/m y
  return - (kk/mm) * yy;
}

double Amortiguado(double yy, double vv, double mm, double kk, double bb){
    // La función a la que se le va a resolver la EDO de segundo orden d²y/dt² = -k/m y - b dy/dt
  return - (kk/mm) * yy - bb*vv;
}

double Euler_X(double yy, double vv, double hh){
    // yy : El valor de la función en el paso n actual
    // hh : El tamaño de paso inicialmente definido
    double yy_n1 = yy + hh*vv;
  return yy_n1;
}

double Euler_V(double yy, double vv, double hh , double mm, double kk){
    // yy : El valor de la función en el paso n actual
    // hh : El tamaño de paso inicialmente definido
    double vv_n1 = vv + hh*Funcion(yy, mm, kk);
  return vv_n1;
}

double Euler_X_A(double yy, double vv, double hh){
    // yy : El valor de la función en el paso n actual
    // hh : El tamaño de paso inicialmente definido
    double yy_n1 = yy + hh*vv;
  return yy_n1;
}

double Euler_V_A(double yy, double vv, double hh, double mm, double kk, double bb){
    // yy : El valor de la función en el paso n actual
    // hh : El tamaño de paso inicialmente definido
    double vv_n1 = vv + hh*Amortiguado(yy, vv, mm, kk, bb);
  return vv_n1;
}

double Leap_Frog_X(double yy, double vv, double hh){
    // yy : El valor de la función en el paso n actual
    // vv : El valor de la velocidad en el paso n+1/2 actual
    // hh : El tamaño de paso inicialmente definido
    double yy_n1 = yy + hh*vv;                // yy_n+1
    return yy_n1;
}

double Leap_Frog_V(double yy_nn12, double vv, double hh, double mm, double kk){
    // yy : El valor de la función en el paso n actual
    // vv : El valor de la velocidad en el paso n+1/2 actual
    // hh : El tamaño de paso inicialmente definido
    double vv_n32 = vv + hh*Funcion(yy_nn12, mm, kk);   // vv_n+3/2
    return vv_n32;
}

int main(){
    double m = 0.2;  // m
    double k = 50.0;   // N/m
    const int N = 10000;
    const double t_final = 2.0;// s
    double h = t_final/N;
    double b = 0.8;

    // Se inicializan los arreglos
    std::array<double, N> x_Euler;
    std::array<double, N> vx_Euler;
    std::array<double, N> x_LF;
    std::array<double, N> vx_LF;

    std::array<double, N> Ax_Euler;   // Amortiguado
    std::array<double, N> Avx_Euler;  // Amortiguado
    std::array<double, N> Ax_RK;   // Amortiguado
    std::array<double, N> Avx_RK;  // Amortiguado
    std::array<double, N> t;
    
    // Se escogen las condiciones iniciales
    double x0 = 0.1;
    double vx0 = 0.0;
    t[0] = 0.0;
    x_Euler[0] = x0;
    vx_Euler[0] = vx0;
    x_LF[0] = x0;
    vx_LF[0] = vx0 + h * Funcion(x0, m, k)/2.0;
    Ax_Euler[0] = x0;
    Avx_Euler[0] = vx0;
    Ax_RK[0] = x0;
    Avx_RK[0] = vx0;

    // Escribo los valores de todos los arreglos
    for (int i = 0; i < N-1; i++){
        t[i+1] = (i+1)*h;
        x_Euler[i+1] = Euler_X(x_Euler[i], vx_Euler[i], h);
        vx_Euler[i+1] = Euler_V(x_Euler[i], vx_Euler[i], h, m, k);
        x_LF[i+1] = Leap_Frog_X(x_LF[i], vx_LF[i], h);
        vx_LF[i+1] = Leap_Frog_V(x_LF[i+1], vx_LF[i], h, m, k);
        Ax_Euler[i+1] = Euler_X_A(Ax_Euler[i], Avx_Euler[i], h);
        Avx_Euler[i+1] = Euler_V_A(Ax_Euler[i], Avx_Euler[i], h, m, k, b);

        // RK4 seguía sin funcionar dentro de una función, por eso ahora
        // está dentro del loop (Idea con ayuda de IA)
        double k1_x = h*Avx_RK[i];
        double k1_v = h*Amortiguado(Ax_RK[i], Avx_RK[i], m, k, b);

        double k2_x = h*(Avx_RK[i] + k1_v/2);
        double k2_v = h*Amortiguado(Ax_RK[i] + k1_x/2, Avx_RK[i] + k1_v/2, m, k, b);
        
        double k3_x = h*(Avx_RK[i] + k2_v/2);
        double k3_v = h*Amortiguado(Ax_RK[i] + k2_x/2, Avx_RK[i] + k2_v/2, m, k, b);
        
        double k4_x = h*(Avx_RK[i] + k3_v);
        double k4_v = h*Amortiguado(Ax_RK[i] + k3_x, Avx_RK[i] + k3_v, m, k, b);
        
        Ax_RK[i+1] = Ax_RK[i] + (k1_x + 2*k2_x + 2*k3_x + k4_x)/6.0;
        Avx_RK[i+1] = Avx_RK[i] + (k1_v + 2*k2_v + 2*k3_v + k4_v)/6.0;
    }

    // Se guardan los archivos en EDO2.dat
    // El orden de las columnas es: tiempo , Euler , LeapFrog,
    // Euler Amortiguado, RK4 amortiguado
    std::ofstream outfile;
    outfile.open("EDO2.dat");
    std::cout << ">>>Guardando los valores en 'EDO2.dat'" << std::endl;

    // Comentario con el nombre de las columnas
    outfile << "#Tiempo, Euler, LeapFrog, Euler Amortiguado, RK4 Amortiguado" << "\n";

    for(int w=0; w<(N);w++){
    outfile << t[w] << " , " << x_Euler[w] << " , " << x_LF[w] 
    << " , " << Ax_Euler[w] << " , " << Ax_RK[w] << "\n";
    }

    outfile.close();

    return 0;
}