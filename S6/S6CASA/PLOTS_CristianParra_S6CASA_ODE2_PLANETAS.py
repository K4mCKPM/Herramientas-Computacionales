import numpy as np
import matplotlib.pyplot as plt

# Variables del problema
N = 10000
h = 0.0002

# Crear los datos desde 'Planetas.dat'
Datos = np.genfromtxt("Planetas.dat", delimiter=",")

tiempo = Datos[:,0]
x_Euler = Datos[:,1]
y_Euler = Datos[:,2]
x_LeapFrog = Datos[:,3]
y_LeapFrog = Datos[:,3]

# Inicialización gráficas
fig0, ax0 = plt.subplots(figsize=(10,6))
fig1, ax1 = plt.subplots(figsize=(10,6))

# Gráfica del resorte
ax0.plot(tiempo, x_Euler, label="x Euler", ls = "--", color = "crimson")
ax0.plot(tiempo, y_Euler, label="y Euler", ls = ":", color = "indigo")
ax0.set_xlabel("Tiempo t")
ax0.set_ylabel("Funcion x")
ax0.set_title(f"EDO 2do orden resorte (k = {k}, m = {m}, b = 0, h = {h})")
ax0.legend()
fig0.savefig("PLOTS_CristianParra_S6CASA_ODE2_Planetas_E.png")

# Gráfica del resorte amortiguado
ax1.plot(tiempo, x_LeapFrog, label="x Leap Frog", ls = "--", color = "crimson")
ax1.plot(tiempo, y_LeapFrog, label="y Leap Frog", ls = ":", color = "indigo")
ax1.set_xlabel("Tiempo t")
ax1.set_ylabel("Funcion x")
ax1.set_title("Orbita del planeta tierra con el método Leap Frog")
plt.legend()
fig1.savefig("PLOTS_CristianParra_S6CASA_ODE2_Planetas_LF.png")