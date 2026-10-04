#include <fstream>
#include <iostream>
#include <array>
#include <string>

float Funcion(float yy, float mm, float kk){
    // La función a la que se le va a resolver la EDO de segundo orden d²y/dt² = f(y)
  return - (kk/mm) * yy;
}

float Amortiguado(float yy, float vv, float mm, float kk, float bb){
    // La función a la que se le va a resolver la EDO de segundo orden d²y/dt² = f(y)
  return - (kk/mm) * yy - bb*vv;
}

float Euler_x(float yy, float vv, float hh){
    // yy : El valor de la función en el paso n actual
    // hh : El tamaño de paso inicialmente definido
    float yy_n1 = yy + hh*vv;
  return yy_n1;
}

float Euler_v(float yy, float vv, float hh , float mm, float kk){
    // yy : El valor de la función en el paso n actual
    // hh : El tamaño de paso inicialmente definido
    float vv_n1 = vv + hh*Funcion(yy, mm, kk);
  return vv_n1;
}

float Euler_Ax(float yy, float vv, float hh){
    // yy : El valor de la función en el paso n actual
    // hh : El tamaño de paso inicialmente definido
    float yy_n1 = yy + hh*vv;
  return yy_n1;
}

float Euler_Av(float yy, float vv, float hh, float mm, float kk, float bb){
    // yy : El valor de la función en el paso n actual
    // hh : El tamaño de paso inicialmente definido
    float vv_n1 = vv + hh*Amortiguado(yy, vv, mm, kk, bb);
  return vv_n1;
}

float X_Leap_Frog(float yy, float vv, float hh){
    // yy : El valor de la función en el paso n actual
    // vv : El valor de la velocidad en el paso n+1/2 actual
    // hh : El tamaño de paso inicialmente definido
    float yy_n1 = yy + hh*vv;                // yy_n+1
    return yy_n1;
}

float V_Leap_Frog(float yy_nn12, float vv, float hh, float mm, float kk){
    // yy : El valor de la función en el paso n actual
    // vv : El valor de la velocidad en el paso n+1/2 actual
    // hh : El tamaño de paso inicialmente definido
    float vv_n32 = vv + hh*Funcion(yy_nn12, mm, kk);   // vv_n+3/2
    return vv_n32;
}

float RK4(float yy, float vv, float hh, float mm, float kk, float bb){
  // yy : El valor de la función en el paso n actual
  // hh : El tamaño de paso inicialmente definido
  float k1_x = hh*Amortiguado(yy, vv, mm, kk, bb);
  float k2_x = hh*Amortiguado(yy + k1_x/2, vv, mm, kk, bb);
  float k3_x = hh*Amortiguado(yy + k2_x/2, vv, mm, kk, bb);
  float k4_x = hh*Amortiguado(yy + k3_x, vv, mm, kk, bb);
  
  float rk_x = yy + (1.0/6.0) * (k1_x + 2*k2_x + 2*k3_x + k4_x);

  return rk_x;
}

float RK4_V_A(float yy, float vv, float hh, float mm, float kk, float bb){
  // yy : El valor de la función en el paso n actual
  // hh : El tamaño de paso inicialmente definido
  float k1_v = hh*Amortiguado(yy, vv, mm, kk, bb);
  float k2_v = hh*Amortiguado(yy + k1_v/2, vv, mm, kk, bb);
  float k3_v = hh*Amortiguado(yy + k2_v/2, vv, mm, kk, bb);
  float k4_v = hh*Amortiguado(yy + k3_v, vv, mm, kk, bb);
  
  float rk_xv= vv + (1.0/6.0) * (k1_v + 2*k2_v + 2*k3_v + k4_v);
  return rk_xv;
}

int main(){
    float m = 0.2;  // m
    float k = 50.0;   // N/m
    const int N = 50000;
    float t_final = 2.0;// s
    double h = t_final/N;
    float b = 0.08;

    // Se inicializan los arreglos
    std::array<float, N> x_Euler;
    std::array<float, N> vx_Euler;
    std::array<float, N> x_LF;
    std::array<float, N> vx_LF;

    std::array<float, N> Ax_Euler;   // Amortiguado
    std::array<float, N> Avx_Euler;  // Amortiguado
    std::array<float, N> Ax_RK;   // Amortiguado
    std::array<float, N> Avx_RK;  // Amortiguado
    std::array<float, N> t;
    
    // Se escogen las condiciones iniciales
    float x0 = 0.1;
    float vx0 = 0.0;
    t[0] = 0.0;
    x_Euler[0] = x0;
    vx_Euler[0] = vx0;
    x_LF[0] = x0;
    vx_LF[0] = vx0 + (1.0/2.0) * h * Funcion(x0, m, k);
    Ax_Euler[0] = x0;
    Avx_Euler[0] = vx0;

    for (int i = 0; i < N-1; i++){
        t[i+1] = (i+1)*h;
        x_Euler[i+1] = Euler_x(x_Euler[i], vx_Euler[i], h);
        vx_Euler[i+1] = Euler_v(x_Euler[i], vx_Euler[i], h, m, k);
        x_LF[i+1] = X_Leap_Frog(x_LF[i], vx_LF[i], h);
        vx_LF[i+1] = V_Leap_Frog(x_LF[i+1], vx_LF[i], h, m, k);
        Ax_Euler[i+1] = Euler_Ax(Ax_Euler[i], Avx_Euler[i], h);
        Avx_Euler[i+1] = Euler_Av(Ax_Euler[i], Avx_Euler[i], h, m, k, b);
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