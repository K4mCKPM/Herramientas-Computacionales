#include <fstream>
#include <iostream>
#include <vector>
#include <string>

float t_final = 2.0;

float funcion(float y){
  // La función a la que se le va a resolver la EDO dy/dt = f(y)
  return -y;
}

float Euler(float y, float h){
  // y : El valor de la función en el paso n actual
  // h : El tamaño de paso inicialmente definido
  return h*funcion(y);
}

float RK4(float y, float h){
  // y : El valor de la función en el paso n actual
  // h : El tamaño de paso inicialmente definido
  float k1 = h*funcion(y);
  float k2 = h*funcion(y + k1/2);
  float k3 = h*funcion(y + k2/2);
  float k4 = h*funcion(y + k3);
  float rk = (1.0/6.0) * (k1 + 2*k2 + 2*k3 + k4);
  return rk;
}

void principal(float h, std::string h_nombre){
  // Es el código que se va a ejecutar para cada h seleccionado en main
  int N = t_final / h;

  // Se crean vectores que guardan los datos para cada método, y el tiempo
  std::vector<float> y_E(N);
  std::vector<float> y_RK(N);
  std::vector<float> t(N);

  // El vector del tiempo toma los valores desde 0 hasta t_final
  for (int i = 0; i < N; i++){
    t[i] = h*i;
  }

  // Se inician ambos vectores (t=0) de los métodos con un uno
  y_E[0] = 1.0;
  y_RK[0] = 1.0;
  
  // Se llena el vector con valores de Euler:
  for (int j = 0; j < N-1; j++){
    y_E[j+1] = y_E[j] + Euler(y_E[j], h);
  }

  // Se completa el vector con valores de RK4:
  for (int k = 0; k < N-1; k++){
    y_RK[k+1] = y_RK[k] + RK4(y_RK[k], h);
  }

  // Se guardan los archivos en datosh#.dat
  // El orden de las columnas es: tiempo , Euler , RK4
  std::ofstream outfile;
  outfile.open("datosh" + h_nombre + ".dat");
  std::cout << ">>>Guardando los valores en 'datos" << h_nombre << ".dat'" << std::endl;

  for(int v=0; v<(N);v++){
  outfile << t[v] << " , " << y_E[v] << " , " << y_RK[v] << std::endl;
  }

  outfile.close();
}

int main(){
  // Para el h voy a tomar los valores: h = 0.1, 0.05, 0.01, 0.005
  // Todos para el mismo tiempo final: t_final = 2.0
  principal(0.1, "01");
  principal(0.05, "005");
  principal(0.01, "001");
  principal(0.005, "0005");
  
  return 0;
}
