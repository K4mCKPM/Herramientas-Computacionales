import numpy as np
import matplotlib.pyplot as plt

# Crear los datos desde 'Planetas.dat'
Datos = np.genfromtxt("EDP.dat", delimiter=",")

tiempo = np.zeros(len(Datos[0]))

for i in range(len(Datos[0])):
    tiempo[i] = i*2/(101)

fig, ax = plt.subplots(figsize=(14,6))
for i in range(len(Datos)):
    ax.plot(tiempo, Datos[i, :])

plt.title("Evolución de la onda en el tiempo")
plt.xlabel("Posición (m)")
plt.ylabel("Altura (m)")
plt.ylim(-0.15, 0.15)
fig.savefig("PLOTS_CristianParra_S8C1_EDP.png")
print(">>>Guardando la gráfica en 'PLOTS_CristianParra_S8C1_EDP.png'")