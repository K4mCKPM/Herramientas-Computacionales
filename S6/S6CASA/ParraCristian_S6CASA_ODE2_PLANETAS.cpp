#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
// Aún tiene errores aaaa.
double Orbita_x(double xx, double yy, double GG, double M0=1){
    return - (GG * M0)/(std::pow((xx*xx + yy*yy),(3.0/2.0))) ;
}

double Euler_x(double yy, double vv, double hh){
    // yy : El valor de la función en el paso n actual
    // hh : El tamaño de paso inicialmente definido
    double yy_n1 = yy + hh*vv;
  return yy_n1;
}

double Euler_v(double xx, double yy, double vv, double GG, double hh){
    // yy : El valor de la función en el paso n actual
    // hh : El tamaño de paso inicialmente definido
    double vv_n1 = vv + hh*Orbita_x(xx, yy, GG);
  return vv_n1;
}

double X_Leap_Frog(double yy, double vv, double hh){
    // yy : El valor de la función en el paso n actual
    // vv : El valor de la velocidad en el paso n+1/2 actual
    // hh : El tamaño de paso inicialmente definido
    double yy_n1 = yy + hh*vv;                // yy_n+1
    return yy_n1;
}

double V_Leap_Frog(double yy_nn11, double vv, double GG, double hh){
    // yy : El valor de la función en el paso n actual
    // vv : El valor de la velocidad en el paso n+1/2 actual
    // hh : El tamaño de paso inicialmente definido
    double vv_n32 = vv + hh*Orbita_x(yy_nn11, GG);   // vv_n+3/2
    return vv_n32;
}

int main(){
    double M = 1.988475e30;  // kg
    double AU = 149597870700; // m
    double days = 86400;      //s
    double G = 6.67e-8;      // m^3 kg^-1 s^-2
    double G_M0 = G*M*(1/std::pow(AU,3))*(days*days);       // m^3 M0 s^-2

    const int N = 20000;
    int h = 0.0001;

    std::vector<double> x_Euler(N);
    std::vector<double> y_Euler(N);
    std::vector<double> vx_Euler(N);
    std::vector<double> x_LF(N);
    std::vector<double> vx_LF(N);
    std::vector<double> t(N);

    // Se escogen las condiciones iniciales
    double x0 = 1;
    double y0 = 0;
    double vx0 = 0.0;
    t[0] = 0;
    x_Euler[0] = x0;
    y_Euler[0] = y0;
    vx_Euler[0] = vx0;
    x_LF[0] = x0;
    vx_LF[0] = vx0 + (1.0/2.0) * h * Orbita_x(x0, 0, G_M0);


    for (int i = 0; i < N-1; i++){
        t[i+1] = (i+1)/(N*h);
        x_Euler[i+1] = Euler_x(x_Euler[i], vx_Euler[i], h);
        y_Euler[i+1] = Euler_x(y_Euler[i], vx_Euler[i], h);
        vx_Euler[i+1] = Euler_v(x_Euler[i], y_Euler[i], vx_Euler[i], h);
        x_LF[i+1] = X_Leap_Frog(x_LF[i], vx_LF[i], h);
        vx_LF[i+1] = V_Leap_Frog(x_LF[i+1], vx_LF[i], h);
    }

    // Se guardan los archivos en EDO2.dat
    // El orden de las columnas es: tiempo , Euler x, Euler y, LeapFrog 
    std::ofstream outfile;
    outfile.open("EDO2.dat");
    std::cout << ">>>Guardando los valores en 'PLANETAS.dat'" << std::endl;

    for(int v=0; v<(N);v++){
    outfile << t[v] << " , " << x_Euler[v] << " , " << y_Euler[v] << " , " << x_LF[v] << std::endl;
    }

    outfile.close();


}