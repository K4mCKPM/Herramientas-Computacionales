import numpy as np
import matplotlib.pyplot as plt


# Parámetros del modelo
V = 0.0001
L = 1
N = 100
T = 13000
delta_x = 0.1
delta_t = 20


fronteras = ["Fija", "Periodica", "Abierta"]
inst = [0, 1, 10, 25] # Instantaneas de interes para graficar

for frontera in fronteras:
    Datos = np.genfromtxt(f"C2_EDP_{frontera}.dat", delimiter=",")
    fig, ((ax0,ax1),(ax2,ax3)) = plt.subplots(2,2, constrained_layout=True)
    ejes = [ax0,ax1,ax2,ax3]

    for ax, i in zip(ejes, inst):
        plano = Datos[i,:-1].reshape((N, N))
        
        ax.set_ylim(0, L)
        ax.set_xlim(0, L)
        ax.set_title(f"Tiempo t = {i*100} s")
        ax.set_xlabel("Posición (m)")
        ax.set_ylabel("Posición (m)")
        im = ax.imshow(plano, cmap='inferno', interpolation='none', extent=[0, L, 0, L])
        fig.colorbar(im, ax=ax, label='Temperatura (°C)')
        

    fig.suptitle(f"Placa cuadrada con condiciones de frontera {frontera}")
    fig.savefig(f"PLOTS_CristianParra_S9C1_EDP_{frontera}.png")
    print(f">>>Guardando la gráfica en 'PLOTS_CristianParra_S9C1_EDP_{frontera}.png'")