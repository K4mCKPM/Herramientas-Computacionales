import numpy as np
import matplotlib.pyplot as plt

# Crear los datos desde 'Planetas.dat'
Datos = np.genfromtxt("EDP.dat", delimiter=",")

tiempo = np.zeros(len(Datos))

for i in range(len(Datos)):
    tiempo[i] = i*2/(101)

fig, ax = plt.subplots(figsize=(14,6))
ax.plot(tiempo, Datos)
fig.savefig("PLOTS_CristianParra_S7C2_EDP.png")
