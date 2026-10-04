#include <fstream>
#include <iostream>
#include <array>
#include <stdlib.h>

int Var1 = 107;
float Var2 = 5.2684;
const int N = 300;

  //Octavo punto:
float division(float mivarflotante, int mivarentera){
  return mivarflotante/mivarentera;
}

  // Décimo punto:
int minimo(std::array<int, N> arreglo){
  int min_tmp = arreglo[0];
  for (int i = 1; i<N; i++){
    if (min_tmp > arreglo[i]){
      min_tmp = arreglo[i];
    }
  }
  return min_tmp;
}

 // Onceavo punto:
 void impares(std::array<int, N> arreglo){
  for (int i = 0; i<N; i++){
    if (arreglo[i] > 800){
      break;
    }
    
    if (arreglo[i] % 2 == 1){
      std::cout << arreglo[i] << std::endl;
    }
  }
 }

int main(){
  srand(time(0));
  // Segundo punto:
  std::cout << "La primera tiene un valor de: " <<  Var1<< " y la segunda de: " << Var2 << std::endl;

  // Tercer punto:
  float Var3 = Var2/Var1;
  std::cout << "El resultado es: " << Var3 << std::endl << std::endl;

  // Cuarto punto:
  std::array<int, N>a1;
  for (int k = 0; k < N; k++){
    a1[k] = rand () % 900;
  }

  // Quinto punto:
  for (int i = 0; i < N; i++){
    std::cout << a1[i] << std::endl;
  }

  // Sexto punto:
  std::cout << "\n" << a1[4] << std::endl;

  // Septimo punto:
  int tamaño = a1.size(); 
  std::cout << "La longitud del arreglo es: " << tamaño << std::endl << std::endl;

  // Noveno punto:
  std::cout << division(17.5, 5) << std::endl << std::endl;

  //
  std::cout << minimo(a1) << std::endl << std::endl;
  
  //
  impares(a1);

  // Guardar el arreglo en "aleatorios.dat"
  std::ofstream outfile;
  outfile.open("aleatorios.dat");

  std::cout << ">>>Guardando el arreglo en 'aleatorios.dat'" << std::endl;

  // write inputted data into the file.
  for(int v=0; v<(N-1);v++){
  outfile << a1[v] <<",";
  }
  outfile << a1[N-1] << std::endl;


  // close the opened file.
  outfile.close();
  
  return 0;
}