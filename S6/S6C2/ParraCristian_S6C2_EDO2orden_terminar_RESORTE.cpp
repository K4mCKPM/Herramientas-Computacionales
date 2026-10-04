#include <fstream>
#include <iostream>
#include <vector>
#include <string>

float Funcion(float yy, float mm = 0.2, float kk= 50, float tt = 0){
    // La función a la que se le va a resolver la EDO de segundo orden d²y/dt² = f(y)
  return - (kk/mm) * yy;
}

float Amortiguado(float yy, float vv, float mm = 0.2, float kk= 50, float bb = 0.08, float tt = 0){
    // La función a la que se le va a resolver la EDO de segundo orden d²y/dt² = f(y)
  return - (kk/mm) * yy - bb*vv;
}

float Euler_x(float yy, float vv, float hh){
    // yy : El valor de la función en el paso n actual
    // yy_prev : El valor de la función en el paso n-1
    // hh : El tamaño de paso inicialmente definido
    float yy_n1 = yy + hh*vv;
  return yy_n1;
}

float Euler_v(float yy, float vv, float hh){
    // yy : El valor de la función en el paso n actual
    // hh : El tamaño de paso inicialmente definido
    float vv_n1 = vv + hh*Funcion(yy);
  return vv_n1;
}

float Euler_Ax(float yy, float vv, float hh){
    // yy : El valor de la función en el paso n actual
    // hh : El tamaño de paso inicialmente definido
    float yy_n1 = yy + hh*vv;
  return yy_n1;
}

float Euler_Av(float yy, float vv, float hh){
    // yy : El valor de la función en el paso n actual
    // yy_prev : El valor de la función en el paso n-1
    // hh : El tamaño de paso inicialmente definido
    float vv_n1 = vv + hh*Amortiguado(yy, vv);
  return vv_n1;
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

float RK4(float yy, float vv, float hh){
  // yy : El valor de la función en el paso n actual
  // hh : El tamaño de paso inicialmente definido
  float k1_x = hh*Amortiguado(yy, vv);
  float k2_x = hh*Amortiguado(yy + k1_x/2, vv);
  float k3_x = hh*Amortiguado(yy + k2_x/2, vv);
  float k4_x = hh*Amortiguado(yy + k3_x, vv);
  
  float rk_x = yy + (1.0/6.0) * (k1_x + 2*k2_x + 2*k3_x + k4_x);

  return rk_x;
}

float RK4_V_A(float yy, float vv, float hh){
  // yy : El valor de la función en el paso n actual
  // hh : El tamaño de paso inicialmente definido
  float k1_v = hh*Amortiguado(yy, vv);
  float k2_v = hh*Amortiguado(yy + k1_v/2, vv);
  float k3_v = hh*Amortiguado(yy + k2_v/2, vv);
  float k4_v = hh*Amortiguado(yy + k3_v, vv);
  
  float rk_xv= vv + (1.0/6.0) * (k1_v + 2*k2_v + 2*k3_v + k4_v);
  return rk_xv;
}

int main(){
    float m = 0.2;  // m
    float k = 50;   // N/m
    int N = 500000;
    float h = 0.0001;
    float b = 800; //No cambia el comportamiento desde 0.08

    // Se inicializan los arreglos
    std::vector<float> x_Euler(N);
    std::vector<float> vx_Euler(N);
    std::vector<float> x_LF(N);
    std::vector<float> vx_LF(N);

    std::vector<float> Ax_Euler(N);   // Amortiguado
    std::vector<float> Avx_Euler(N);  // Amortiguado
    std::vector<float> Ax_RK(N);   // Amortiguado
    std::vector<float> Avx_RK(N);  // Amortiguado
    std::vector<float> t(N);
    
    // Se escogen las condiciones iniciales
    float x0 = 0.1;
    float vx0 = 0.0;
    t[0] = 0;
    x_Euler[0] = x0;
    vx_Euler[0] = vx0;
    x_LF[0] = x0;
    vx_LF[0] = vx0 + (1.0/2.0) * h * Funcion(x0);
    Ax_Euler[0] = x0;
    Avx_Euler[0] = vx0;

    for (int i = 0; i < N-1; i++){
        t[i+1] = (i+1)/(N*h);
        x_Euler[i+1] = Euler_x(x_Euler[i], vx_Euler[i], h);
        vx_Euler[i+1] = Euler_v(x_Euler[i], vx_Euler[i], h);
        x_LF[i+1] = X_Leap_Frog(x_LF[i], vx_LF[i], h);
        vx_LF[i+1] = V_Leap_Frog(x_LF[i+1], vx_LF[i], h);
        Ax_Euler[i+1] = Euler_Ax(Ax_Euler[i], Avx_Euler[i], h);
        Avx_Euler[i+1] = Euler_Av(Ax_Euler[i], Avx_Euler[i], h);
    }

    // Se guardan los archivos en EDO2.dat
    // El orden de las columnas es: tiempo , Euler , LeapFrog, Euler Amortiguado, 
    std::ofstream outfile;
    outfile.open("EDO2.dat");
    std::cout << ">>>Guardando los valores en 'EDO2.dat'" << std::endl;

    for(int v=0; v<(N);v++){
    outfile << t[v] << " , " << x_Euler[v] << " , " << x_LF[v] << " , " << Ax_Euler[v] << std::endl;
    }

    outfile.close();

    return 0;
}