#include <fstream>
#include <iostream>
#include <array>
#include <string>

double Funcion(double yy, double mm, double kk){
    // La función a la que se le va a resolver la EDO de segundo orden d²y/dt² = f(y)
  return - (kk/mm) * yy;
}

double Amortiguado(double yy, double vv, double mm, double kk, double bb){
    // La función a la que se le va a resolver la EDO de segundo orden d²y/dt² = f(y)
  return - (kk/mm) * yy - bb*vv;
}

double Euler_x(double yy, double vv, double hh){
    // yy : El valor de la función en el paso n actual
    // hh : El tamaño de paso inicialmente definido
    double yy_n1 = yy + hh*vv;
  return yy_n1;
}

double Euler_v(double yy, double vv, double hh , double mm, double kk){
    // yy : El valor de la función en el paso n actual
    // hh : El tamaño de paso inicialmente definido
    double vv_n1 = vv + hh*Funcion(yy, mm, kk);
  return vv_n1;
}

double Euler_Ax(double yy, double vv, double hh){
    // yy : El valor de la función en el paso n actual
    // hh : El tamaño de paso inicialmente definido
    double yy_n1 = yy + hh*vv;
  return yy_n1;
}

double Euler_Av(double yy, double vv, double hh, double mm, double kk, double bb){
    // yy : El valor de la función en el paso n actual
    // hh : El tamaño de paso inicialmente definido
    double vv_n1 = vv + hh*Amortiguado(yy, vv, mm, kk, bb);
  return vv_n1;
}

double X_Leap_Frog(double yy, double vv, double hh){
    // yy : El valor de la función en el paso n actual
    // vv : El valor de la velocidad en el paso n+1/2 actual
    // hh : El tamaño de paso inicialmente definido
    double yy_n1 = yy + hh*vv;                // yy_n+1
    return yy_n1;
}

double V_Leap_Frog(double yy_nn12, double vv, double hh, double mm, double kk){
    // yy : El valor de la función en el paso n actual
    // vv : El valor de la velocidad en el paso n+1/2 actual
    // hh : El tamaño de paso inicialmente definido
    double vv_n32 = vv + hh*Funcion(yy_nn12, mm, kk);   // vv_n+3/2
    return vv_n32;
}

double RK4(double yy, double vv, double hh, double mm, double kk, double bb){
  // yy : El valor de la función en el paso n actual
  // hh : El tamaño de paso inicialmente definido
  double k1_x = hh*Amortiguado(yy, vv, mm, kk, bb);
  double k1_v = hh*Amortiguado(yy, vv, mm, kk, bb);
  double k2_x = hh*Amortiguado(yy, vv + k1_v/2, mm, kk, bb);
  double k2_v = hh*Amortiguado(yy + k1_x/2, vv, mm, kk, bb);
  double k3_x = hh*Amortiguado(yy, vv + k2_v/2, mm, kk, bb);
  double k3_v = hh*Amortiguado(yy + k2_x/2, vv, mm, kk, bb);
  double k4_x = hh*Amortiguado(yy, vv + k3_v, mm, kk, bb);
  double k4_v = hh*Amortiguado(yy + k3_x, vv, mm, kk, bb);
  double rk_x = yy + (1.0/6.0) * (k1_x + 2*k2_x + 2*k3_x + k4_x);

  return rk_x;
}

int main(){
    double m = 0.2;  // m
    double k = 50.0;   // N/m
    const int N = 20000;
    double t_final = 2.0;// s
    double h = t_final/N;
    double b = 0.08;

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
    vx_LF[0] = vx0 + (1.0/2.0) * h * Funcion(x0, m, k);
    Ax_Euler[0] = x0;
    Avx_Euler[0] = vx0;
    Ax_RK[0] = x0;
    Avx_RK[0] = vx0;

    for (int i = 0; i < N-1; i++){
        t[i+1] = (i+1)*h;
        x_Euler[i+1] = Euler_x(x_Euler[i], vx_Euler[i], h);
        vx_Euler[i+1] = Euler_v(x_Euler[i], vx_Euler[i], h, m, k);
        x_LF[i+1] = X_Leap_Frog(x_LF[i], vx_LF[i], h);
        vx_LF[i+1] = V_Leap_Frog(x_LF[i+1], vx_LF[i], h, m, k);
        Ax_Euler[i+1] = Euler_Ax(Ax_Euler[i], Avx_Euler[i], h);
        Avx_Euler[i+1] = Euler_Av(Ax_Euler[i], Avx_Euler[i], h, m, k, b);
        Ax_RK[i+1] = RK4(Ax_RK[i], Avx_RK[i], h, m, k, b);
    }

    // Se guardan los archivos en EDO2.dat
    // El orden de las columnas es: tiempo , Euler , LeapFrog, Euler Amortiguado, RK4 amortiguado
    std::ofstream outfile;
    outfile.open("EDO2.dat");
    std::cout << ">>>Guardando los valores en 'EDO2.dat'" << std::endl;

    for(int v=0; v<(N);v++){
    outfile << t[v] << " , " << x_Euler[v] << " , " << x_LF[v] << " , " << Ax_Euler[v] << " , " << Ax_RK[v] << "\n";
    }

    outfile.close();

    return 0;
}