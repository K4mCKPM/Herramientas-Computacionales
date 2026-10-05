import numpy as np
import matplotlib.pyplot as plt

# Variables del problema
N = 10000
h = 0.02

# Crear los datos desde 'Planetas.dat'
Datos = np.genfromtxt("Planetas.dat", delimiter=",")

tiempo = Datos[:,0]
x_Euler = Datos[:,1]
y_Euler = Datos[:,2]
x_LeapFrog = Datos[:,3]
y_LeapFrog = Datos[:,4]

# Inicialización gráficas
fig0, ax0 = plt.subplots(figsize=(10,6))
fig1, ax1 = plt.subplots(figsize=(10,6))

# Gráfica del resorte
ax0.plot(x_Euler, y_Euler, label="Órbita con Euler", ls = "--", color = "crimson")
ax0.axis("equal")
ax0.set_xlabel("x (UA)")
ax0.set_ylabel("y (UA)")
ax0.set_title("Orbita del planeta tierra con el método Leap Frog")
ax0.legend()
fig0.savefig("PLOTS_CristianParra_S6CASA_ODE2_Planetas_E.png")

# Gráfica del resorte amortiguado
ax1.plot(x_LeapFrog, y_LeapFrog, label="Órbita con Leap Frog", ls = ":", color = "indigo")
ax1.axis("equal")
ax1.set_xlabel("x (UA)")
ax1.set_ylabel("y (UA)")
ax1.set_title("Orbita del planeta tierra con el método Leap Frog")
ax1.legend()
fig1.savefig("PLOTS_CristianParra_S6CASA_ODE2_Planetas_LF.png")