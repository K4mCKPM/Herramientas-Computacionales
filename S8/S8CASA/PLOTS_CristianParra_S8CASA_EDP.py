import numpy as np
import matplotlib.pyplot as plt

# Nombre de los archivos que se van a leer y graficar
archivos = ["Fijo", "Forzado"]

for file in archivos:
    Datos = np.genfromtxt(f"EDP_{file}.dat", delimiter=",")
    posicion = np.zeros(len(Datos[0]))

    for i in range(len(Datos[0])):
        posicion[i] = i*2/(100)

    fig, ax = plt.subplots(figsize=(14,6))

    tiempos = [0, 5, 10, 16, 20, 28, 32]    # Son tiempos escogidos a mano que muestran mejor el comportamiento de la cuerda fija.
    for i in tiempos:
            ax.plot(posicion, Datos[i, :])

    # Se grafica el archivo
    plt.title(f"Evolución de la onda en el tiempo para el extremo izquierdo Fijo y el extremo derecho {file}")
    plt.xlabel("Posición (m)")
    plt.ylabel("Altura (m)")
    plt.ylim(-0.15, 0.15)
    plt.grid(True)

    fig.savefig(f"PLOTS_CristianParra_S8CASA_EDP_{file}.png")
    print(f">>>Guardando la gráfica en 'PLOTS_CristianParra_S8CASA_EDP_{file}.png'")