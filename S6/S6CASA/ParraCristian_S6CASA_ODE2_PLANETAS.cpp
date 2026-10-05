#include <fstream>
#include <iostream>
#include <array>
#include <cmath>

double Orbita_U(double uu, double ww, double GG, double M0=1){
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
    double vv_n1 = vv + hh*Orbita_U(uu, ww, GG);
  return vv_n1;
}

double Leap_Frog_U(double uu, double vv, double hh){
    // uu : El valor de la función en el paso n actual
    // vv : El valor de la velocidad en el paso n+1/2 actual
    // hh : El tamaño de paso inicialmente definido
    double uu_n1 = uu + hh*vv;                // uu_n+1
    return uu_n1;
}

double Leap_Frog_V(double uu_nn12, double ww_nn12, double vv, double GG,double hh){
    // uu : El valor de la función en el paso n actual
    // vv : El valor de la velocidad en el paso n+1/2 actual
    // hh : El tamaño de paso inicialmente definido
    double vv_n32 = vv + hh*Orbita_U(uu_nn12, ww_nn12, GG);   // vv_n+3/2
    return vv_n32;
}

int main(){
    double M = 1.988475e30;         // kg | Masa solar (=1)
    double Mt =  5.9742e24/M;       // kg | Masa de la tierra
    double AU = 1.49597870700e11;   // m  | Unidades Astronómicas (=1)
    double year = 31557600;         //s   | Años (=1)
    double G = 6.67430e-11;            // m^3 kg^-1 s^-2 | Constante de gravitación
    double G_0 = G*M*(1/std::pow(AU,3))*(year*year); // UA^3 M0 year^-2

    // Condiciones de paso y cantidad de pasos
    const int N = 1827;     // ~ 5 años
    double h = 1.0/365.25;

    // Caso 1 | Sol estático:
    // Arrays para el método de Euler
    std::array<double, N> x_Euler;
    std::array<double, N> y_Euler;
    std::array<double, N> vx_Euler;
    std::array<double, N> vy_Euler;

    // Arrays para el método de Leap Frog
    std::array<double, N> x_LF;
    std::array<double, N> y_LF;
    std::array<double, N> vx_LF;
    std::array<double, N> vy_LF;

    // Caso 2 | Sol en movimiento:
    // Usaré el factor de escala M/Mtotal sobre los arrays anteriores

    // Datos órbita elíptica:
    std::array<double, N> x_elip;
    std::array<double, N> y_elip;
    std::array<double, N> vx_elip;
    std::array<double, N> vy_elip;

    // Array del tiempo
    std::array<double, N> t;
    
    // El caso 3 creo que toca con clases como dijo la profe,
    // lastimosamente no puedo dedicarle más tiempo al código.
    // Intentaré regresar a este código para mejorarlo.

    // Se escogen las condiciones iniciales
    double x0 = 1;  // UA
    double y0 = 0;  // UA
    double vx0 = 0.0;       // UA/año
    double vy0 = 2*M_PI;    // UA/año (suponiendo órbita circular)

    // Caso 2:
    // Factores de escala que multiplican la posición y la velocidad
    double fe_T = 1.0/(1.0 + Mt);     // Factor de escala para la tierra
    double fe_S = -Mt/(1.0 + Mt);     // Factor de escala para el sol

    // Comparación órbita real (elíptica):
    double excentricidad = 0.01671022;          // Dato de Nasa Planetary Factsheet
    double perihelio = 1.0*(1.0-excentricidad); // Suponiendo que se situa en el eje x
    double vel_peri = 2.0*M_PI*std::sqrt((1.0+excentricidad)/(1.0-excentricidad)); // Velocidad inicial

    t[0] = 0;
    // Caso 1:
    x_Euler[0] = x0;
    y_Euler[0] = y0;
    vx_Euler[0] = vx0;
    vy_Euler[0] = vy0;
    
    x_LF[0] = x0;
    y_LF[0] = y0;
    vx_LF[0] = vx0 + h * Orbita_U(x0, y0, G_0)/2.0;
    vy_LF[0] = vy0 + h * Orbita_U(y0, x0, G_0)/2.0;

    // Datos órbita elíṕtica:
    x_elip[0] = perihelio;
    y_elip[0] = y0;
    vx_elip[0] = vx0 + h * Orbita_U(perihelio, y0, G_0)/2.0;
    vy_elip[0] = vel_peri + h * Orbita_U(y0, perihelio, G_0)/2.0;
    
    
    // Escritura de los arrays
    for (int i = 0; i < N-1; i++){
        t[i+1] = t[i] + h;

        // Caso 1:
        x_Euler[i+1] = Euler_U(x_Euler[i], vx_Euler[i], h);
        y_Euler[i+1] = Euler_U(y_Euler[i], vy_Euler[i], h);

        vx_Euler[i+1] = Euler_V(x_Euler[i], y_Euler[i], vx_Euler[i], G_0, h);
        vy_Euler[i+1] = Euler_V(y_Euler[i], x_Euler[i], vy_Euler[i], G_0, h);

        x_LF[i+1] = Leap_Frog_U(x_LF[i], vx_LF[i], h);
        y_LF[i+1] = Leap_Frog_U(y_LF[i], vy_LF[i], h);

        vx_LF[i+1] = Leap_Frog_V(x_LF[i+1], y_LF[i+1], vx_LF[i], G_0, h);
        vy_LF[i+1] = Leap_Frog_V(y_LF[i+1], x_LF[i+1], vy_LF[i], G_0, h);

        // Caso 2:
        // Aplico los factores de escala sobre los valores anteriores
        // en la escritura de "Planetas.dat" 

        // Datos ŕbita elíptica:
        x_elip[i+1] = Leap_Frog_U(x_elip[i], vx_elip[i], h);
        y_elip[i+1] = Leap_Frog_U(y_elip[i], vy_elip[i], h);

        vx_elip[i+1] = Leap_Frog_V(x_elip[i+1], y_elip[i+1], vx_elip[i], G_0, h);
        vy_elip[i+1] = Leap_Frog_V(y_elip[i+1], x_elip[i+1], vy_elip[i], G_0, h);
        }

    // Se guardan los archivos en Planetas.dat
    // El orden de las columnas es: 
    // Caso 1 | tiempo , Euler x, Euler y, LeapFrog x, LeapFrog y.
    // Caso 2 | Euler x sol, Euler y sol, Euler x tierra, Euler y tierra
    // Leapfrog x sol, Leapfrog y sol, Leapfrog x tierra, Leapfrog y tierra.
    // Órbita elíptica | x elíptica, y elíptica.

    std::ofstream outfile;
    outfile.open("Planetas.dat");
    std::cout << ">>>Guardando los valores en 'Planetas.dat'" << std::endl;

    for(int p=0; p<(N);p++){
    outfile << t[p] << " , " 
    << x_Euler[p] << " , " << y_Euler[p] << " , " 
    << x_LF[p] << " , " << y_LF[p]<< " , "
    << fe_S*x_Euler[p] << " , " << fe_S*y_Euler[p] << " , "
    << fe_T*x_Euler[p] << " , " << fe_T*y_Euler[p] << " , "
    << fe_S*x_LF[p] << " , " << fe_S*y_LF[p]<< " , "
    << fe_T*x_LF[p] << " , " << fe_T*y_LF[p]<< " , "
    << x_elip[p] << " , " << y_elip[p]<< "\n";
    }

    outfile.close();
}