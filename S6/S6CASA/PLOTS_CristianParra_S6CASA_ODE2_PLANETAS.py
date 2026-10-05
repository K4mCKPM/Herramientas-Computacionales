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
eliptica_x = Datos[:,13]
eliptica_y = Datos[:,14]

# Inicialización gráficas

fig1, (ax0, ax1) = plt.subplots(1,2,figsize=(14,6))
fig2, (ax2, ax3) = plt.subplots(1,2,figsize=(14,6))

# Caso 1 | Sol estático:
# Gráfica de la órbita mediante el método de Euler
ax0.scatter(0, 0, s = 422, color = "orange", label = "Sol")
ax0.scatter(x_Euler[-1], y_Euler[-1], s = 25, color = "royalblue", label = "Tierra")
ax0.plot(eliptica_x, eliptica_y, label = 'Orbita "Real"', color = "limegreen", alpha=0.5)
ax0.plot(x_Euler, y_Euler, label="Órbita con Euler", ls = ":", color = "indigo")
ax0.axis("equal")
ax0.set_xlabel("x (UA)")
ax0.set_ylabel("y (UA)")
ax0.set_title("Método de Euler")
ax0.legend(loc='lower left')

# Gráfica de la órbita mediante el método de Leap Frog
ax1.scatter(0, 0, s = 422, color = "orange", label = "Sol")
ax1.scatter(x_LeapFrog[-1], y_LeapFrog[-1], s = 25, color = "royalblue", label = "Tierra")
ax1.plot(eliptica_x, eliptica_y, label = 'Orbita "Real"', color = "limegreen", alpha=0.5)
ax1.plot(x_LeapFrog, y_LeapFrog, label="Órbita con Leap Frog", ls = ":", color = "indigo")
ax1.axis("equal")
ax1.set_xlabel("x (UA)")
ax1.set_ylabel("y (UA)")
ax1.set_title("Método Leap Frog")
ax1.legend(loc='upper right')
fig1.suptitle("Órbita del planeta tierra")
fig1.savefig("PLOTS_CristianParra_S6CASA_ODE2_Planetas_Tierra.png")

# Caso 2 | Sol moviendose:
# Gráfica de las órbitas mediante el método de Euler
ax2.scatter(Sol_x_Euler[-1], Sol_y_Euler[-1], s = 422, color = "orange", label = "Sol")
ax2.scatter(Tierra_x_Euler[-1], Tierra_y_Euler[-1], s = 25, color = "royalblue", label = "Tierra")
ax2.plot(eliptica_x, eliptica_y, label = 'Orbita "Real" de la tierra', color = "limegreen", alpha=0.5)
ax2.plot(Sol_x_Euler, Sol_y_Euler, label="Órbita solar con Euler", color = "crimson")
ax2.plot(Tierra_x_Euler, Tierra_y_Euler, label="Órbita de la tierra con Euler", ls = ":", color = "darkgreen")
ax2.axis("equal")
ax2.set_xlabel("x (UA)")
ax2.set_ylabel("y (UA)")
ax2.set_title("Método de Euler")
ax2.legend(loc = 'lower left')

# Gráfica de las órbitas mediante el método de Leap Frog
ax3.scatter(Sol_x_LeapFrog[-1], Sol_y_LeapFrog[-1], s = 422, color = "orange", label = "Sol")
ax3.scatter(Tierra_x_LeapFrog[-1], Tierra_y_LeapFrog[-1], s = 25, color = "royalblue", label = "Tierra")
ax3.plot(eliptica_x, eliptica_y, label = 'Orbita "Real" de la tierra', color = "limegreen", alpha=0.5)
ax3.plot(Sol_x_LeapFrog, Sol_y_LeapFrog, label="Órbita solar con Leap Frog", color = "crimson")
ax3.plot(Tierra_x_LeapFrog, Tierra_y_LeapFrog, label="Órbita de la tierra con Leap Frog", ls = ":", color = "darkgreen")
ax3.axis("equal")
ax3.set_xlabel("x (UA)")
ax3.set_ylabel("y (UA)")
ax3.set_title("Método Leap Frog")
ax3.legend(loc = 'upper right')
fig2.suptitle("Órbitas del sol y la tierra")
fig2.savefig("PLOTS_CristianParra_S6CASA_ODE2_Planetas_Sol.png")
