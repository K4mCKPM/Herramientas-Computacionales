#include <fstream>
#include <iostream>
#include <vector>
#include <string>

float Funcion(float yy, float mm = 0.2, float kk= 50, float tt = 0){
    // La función a la que se le va a resolver la EDO de segundo orden d²y/dt² = f(y)
  return - (kk/mm) * yy;
}

float Euler(float yy, float yy_prev, float hh){
    // yy : El valor de la función en el paso n actual
    // yy_prev : El valor de la función en el paso n-1
    // hh : El tamaño de paso inicialmente definido
  return 2*yy - yy_prev + hh*hh*Funcion(yy);
}

float X_Leap_Frog(float yy, float vv, float hh){
    // yy : El valor de la función en el paso n actual
    // vv : El valor de la velocidad en el paso n+1/2 actual
    // hh : El tamaño de paso inicialmente definido
    float yy_n1 = yy + hh*vv;                // yy_n+1
    return yy_n1;
}

float V_Leap_Frog(float yy_nn11, float vv, float hh){
    // yy : El valor de la función en el paso n actual
    // vv : El valor de la velocidad en el paso n+1/2 actual
    // hh : El tamaño de paso inicialmente definido
    float vv_n32 = vv + hh*Funcion(yy_nn11);   // vv_n+3/2
    return vv_n32;
}

float RK4(float yy, float hh){
  // yy : El valor de la función en el paso n actual
  // hh : El tamaño de paso inicialmente definido
  float k1 = hh*Funcion(yy);
  float k2 = hh*Funcion(yy + k1/2);
  float k3 = hh*Funcion(yy + k2/2);
  float k4 = hh*Funcion(yy + k3);
  float rk = (1.0/6.0) * (k1 + 2*k2 + 2*k3 + k4);
  return rk;
}


int main(){
    float m = 0.2;  // m
    float k = 50;   // N/m
    int N = 2000;
    float h = 0.01;

    // Se inicializan los arreglos
    std::vector<float> x_Euler(N);
    std::vector<float> x_LF(N);
    std::vector<float> vx_LF(N);
    std::vector<float> t(N);
    
    // Se escogen las condiciones iniciales
    float x0 = 0.1;
    float vx0 = 0.0;
    t[0] = 0;
    x_Euler[0] = x0;
    x_Euler[1] = x0 + (1.0/2.0) * h*h * Funcion(x0);
    x_LF[0] = x0;
    vx_LF[0] = vx0 + (1.0/2.0) * h * Funcion(x0);

    for (int i = 0; i < N-1; i++){
        t[i+1] = i+1;
        x_LF[i+1] = X_Leap_Frog(x_LF[i], vx_LF[i], h);
        vx_LF[i+1] = V_Leap_Frog(x_LF[i+1], vx_LF[i], h);
    }

    for (int j = 1; j < N-1; j++){
        x_Euler[j+1] = Euler(x_Euler[j], x_Euler[j-1], h);
    }

    // Se guardan los archivos en EDO2.dat
    // El orden de las columnas es: tiempo , Euler , LeapFrog, Velocidad
    std::ofstream outfile;
    outfile.open("EDO2.dat");
    std::cout << ">>>Guardando los valores en 'EDO2.dat'" << std::endl;

    for(int v=0; v<(N);v++){
    outfile << t[v] << " , " << x_Euler[v] << " , " << x_LF[v] << " , " << vx_LF[v] << std::endl;
    }

    outfile.close();

    return 0;
}