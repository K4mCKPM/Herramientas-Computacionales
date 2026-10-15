import numpy as np
import matplotlib.pyplot as plt

# Crear los datos desde 'Planetas.dat'
Datos = np.genfromtxt("C2_EDP.dat", delimiter=",")

# Parámetros del modelo
V = 0.0001
L = 1
N = 10
T = 130
delta_x = 0.1
delta_t = 20


inst = [0, 1, 10, 25] # Instantaneas de interes para graficar

for i in inst:
    plano = Datos[i,:-1].reshape((N, N))
    
    fig, ax = plt.subplots()

    plt.ylim(0, L)
    plt.xlim(0, L)
    plt.title(f"Placa cuadrada en el tiempo t = {i*100} s")
    plt.xlabel("Posición (m)")
    plt.ylabel("Posición (m)")
    plt.imshow(plano, cmap='inferno', interpolation='nearest', extent=[0, L, 0, L])
    plt.colorbar(label='Temperatura (°C)')
    plt.gca().invert_yaxis()

    fig.savefig(f"PLOTS_CristianParra_S8C2_EDP_T_{i*100}s.png")
    print(f">>>Guardando la gráfica en 'PLOTS_CristianParra_S8C2_EDP_T_{i*100}s.png'")