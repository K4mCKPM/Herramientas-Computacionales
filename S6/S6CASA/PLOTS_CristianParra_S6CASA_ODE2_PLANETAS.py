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
Sol_x_Euler = Datos[:,5]
Sol_y_Euler = Datos[:,6]
Tierra_x_Euler = Datos[:,7]
Tierra_y_Euler = Datos[:,8]
Sol_x_LeapFrog = Datos[:,9]
Sol_y_LeapFrog = Datos[:,10]
Tierra_x_LeapFrog = Datos[:,11]
Tierra_y_LeapFrog = Datos[:,12]

# Inicialización gráficas
fig0, ax0 = plt.subplots(figsize=(10,6))
fig1, ax1 = plt.subplots(figsize=(10,6))
fig2, ax2 = plt.subplots(figsize=(10,6))
fig3, ax3 = plt.subplots(figsize=(10,6))

# Caso 1 | Sol estático:
# Gráfica de la órbita mediante el método de Euler
ax0.plot(x_Euler, y_Euler, label="Órbita con Euler", ls = "--", color = "crimson")
ax0.scatter(0, 0, s = 422, color = "orange", label = "Sol")
ax0.axis("equal")
ax0.set_xlabel("x (UA)")
ax0.set_ylabel("y (UA)")
ax0.set_title("Orbita del planeta tierra con el método de Euler")
ax0.legend()
fig0.savefig("PLOTS_CristianParra_S6CASA_ODE2_Planetas_E.png")

# Gráfica de la órbita mediante el método de Leap Frog
ax1.plot(x_LeapFrog, y_LeapFrog, label="Órbita con Leap Frog", ls = ":", color = "indigo")
ax1.scatter(0, 0, s = 422, color = "orange", label = "Sol")
ax1.axis("equal")
ax1.set_xlabel("x (UA)")
ax1.set_ylabel("y (UA)")
ax1.set_title("Orbita del planeta tierra con el método Leap Frog")
ax1.legend()
fig1.savefig("PLOTS_CristianParra_S6CASA_ODE2_Planetas_LF.png")

# Caso 2 | Sol moviendose:
# Gráfica de las órbitas mediante el método de Euler
ax2.plot(Sol_x_Euler, Sol_y_Euler, label="Órbita solar con Euler", ls = "--", color = "crimson")
ax2.plot(Tierra_x_Euler, Tierra_y_Euler, label="Órbita de la tierra con Euler", ls = "--", color = "royalblue")
ax2.scatter(0, 0, s = 422, color = "orange", label = "Sol")
ax2.axis("equal")
ax2.set_xlabel("x (UA)")
ax2.set_ylabel("y (UA)")
ax2.set_title("Orbitas del sol y la tierra con el método de Euler")
ax2.legend()
fig2.savefig("PLOTS_CristianParra_S6CASA_ODE2_Planetas_E_Sol.png")

# Gráfica de las órbitas mediante el método de Leap Frog
ax3.plot(Sol_x_LeapFrog, Sol_y_LeapFrog, label="Órbita solar con Leap Frog", ls = ":", color = "indigo")
ax3.plot(Tierra_x_LeapFrog, Tierra_y_LeapFrog, label="Órbita de la tierra con Leap Frog", ls = ":", color = "darkgreen")
ax3.scatter(0, 0, s = 422, color = "orange", label = "Sol")
ax3.axis("equal")
ax3.set_xlabel("x (UA)")
ax3.set_ylabel("y (UA)")
ax3.set_title("Orbitas del sol y la tierra con el método Leap Frog")
ax3.legend()
fig3.savefig("PLOTS_CristianParra_S6CASA_ODE2_Planetas_LF_Sol.png")