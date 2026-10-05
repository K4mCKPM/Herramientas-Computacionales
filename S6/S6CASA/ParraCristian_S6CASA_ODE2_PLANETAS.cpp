#include <fstream>
#include <iostream>
#include <array>
#include <cmath>
#include <string>
// Aún tiene errores aaaa.
double Orbita_x(double uu, double ww, double GG, double M0=1){
    // uu: Las coordenadas en donde se calcula la dirección, es decir,
    // si es la coordenada x entonces es en dirección del vector unitario i.
    // ww: La coordenada complementaria con la que se forma el vector r.
    return - (GG * M0 * uu)/(std::pow((uu*uu + ww*ww),(3.0/2.0))); // Se calcula en la dirección de uu
}

double Euler_U(double uu, double vv, double hh){
    // uu : El valor de la función en el paso n actual
    // vv : La primer derivada de la función en el paso n
    // hh : El tamaño de paso inicialmente definido
    double uu_n1 = uu + hh*vv;
  return uu_n1;
}

double Euler_V(double uu, double ww, double vv, double GG, double hh){
    // uu : El valor de la coordenada en el paso n actual
    // vv : La primer derivada de la función en el paso n
    // ww : El valor de la coordenada complementaria en el paso n
    // hh : El tamaño de paso inicialmente definido
    double vv_n1 = vv + hh*Orbita_x(uu, ww, GG);
  return vv_n1;
}

double Leap_Frog_U(double uu, double vv, double hh){
    // uu : El valor de la función en el paso n actual
    // vv : El valor de la velocidad en el paso n+1/2 actual
    // hh : El tamaño de paso inicialmente definido
    double uu_n1 = uu + hh*vv;                // uu_n+1
    return uu_n1;
}

double Leap_Frog_V(double uu_nn12, double vv, double GG,double hh){
    // uu : El valor de la función en el paso n actual
    // vv : El valor de la velocidad en el paso n+1/2 actual
    // hh : El tamaño de paso inicialmente definido
    double vv_n32 = vv + hh*Orbita_x(uu_nn12, vv, GG);   // vv_n+3/2
    return vv_n32;
}

int main(){
    double M = 1.988475e30;     // kg
    double AU = 1.49597870700e11; // m
    double days = 86400;        //s
    double G = 6.67e-8;         // m^3 kg^-1 s^-2
    double G_M0 = G*M*(1/std::pow(AU,3))*(days*days);       // UA^3 M0 days^-2

    const int N = 1000;
    double h = 0.02;

    std::array<double, N> x_Euler;
    std::array<double, N> y_Euler;
    std::array<double, N> vx_Euler;
    std::array<double, N> vy_Euler;

    std::array<double, N> x_LF;
    std::array<double, N> y_LF;
    std::array<double, N> vx_LF;
    std::array<double, N> vy_LF;

    std::array<double, N> t;

    // Se escogen las condiciones iniciales
    double x0 = 1;
    double y0 = 0;
    double vx0 = 0.0;
    double vy0 = 0.7;

    t[0] = 0;
    x_Euler[0] = x0;
    y_Euler[0] = y0;
    vx_Euler[0] = vx0;
    vy_Euler[0] = vy0;
    
    x_LF[0] = x0;
    y_LF[0] = y0;
    vx_LF[0] = vx0 + h * Orbita_x(x0, y0, G_M0)/2.0;
    vy_LF[0] = vy0 + h * Orbita_x(y0, x0, G_M0)/2.0;


    for (int i = 0; i < N-1; i++){
        t[i+1] = i/N;
        x_Euler[i+1] = Euler_U(x_Euler[i], vx_Euler[i], h);
        y_Euler[i+1] = Euler_U(y_Euler[i], vy_Euler[i], h);

        vx_Euler[i+1] = Euler_V(x_Euler[i], y_Euler[i], vx_Euler[i], G_M0, h);
        vy_Euler[i+1] = Euler_V(y_Euler[i], x_Euler[i], vy_Euler[i], G_M0, h);

        x_LF[i+1] = Leap_Frog_U(x_LF[i], vx_LF[i], h);
        y_LF[i+1] = Leap_Frog_U(y_LF[i], vy_LF[i], h);

        vx_LF[i+1] = Leap_Frog_V(x_LF[i+1], vx_LF[i], G_M0, h);
        vy_LF[i+1] = Leap_Frog_V(y_LF[i+1], vy_LF[i], G_M0, h);
    }

    // Se guardan los archivos en Planetas.dat
    // El orden de las columnas es: tiempo , Euler x, Euler y, LeapFrog x, LeapFrog y
    std::ofstream outfile;
    outfile.open("Planetas.dat");
    std::cout << ">>>Guardando los valores en 'Planetas.dat'" << std::endl;

    for(int p=0; p<(N);p++){
    outfile << t[p] << " , " << x_Euler[p] << " , " << y_Euler[p] << " , " 
    << x_LF[p] << " , " << y_LF[p]<< "\n";
    }

    outfile.close();


}