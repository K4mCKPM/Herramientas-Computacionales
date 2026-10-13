import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

#--- Variables del problema
N = 10000
h = 0.02

#--- Crear los datos desde 'Planetas.dat'
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


#--- Inicialización gráficas

fig1, (ax0, ax1) = plt.subplots(1,2,figsize=(14,6))
fig2, (ax2, ax3) = plt.subplots(1,2,figsize=(14,6))

#--- Caso 1 | Sol estático:
# Animación de la órbita mediante el método de Euler
ax0.scatter(0, 0, s = 222, color = "orange", label = "Sol")
scatter0 = ax0.scatter(x_Euler[0], y_Euler[0], s = 25, color = "royalblue", label = "Tierra")

line1 = ax0.plot(eliptica_x[0], eliptica_y[0], label = 'Orbita "Real"', color = "limegreen", alpha=0.5)[0]
line2 = ax0.plot(x_Euler[0], y_Euler[0], label="Órbita con Euler", ls = ":", color = "indigo")[0]
ax0.set(xlim=(-1.6, 1.6), ylim=(-1.6, 1.6))
ax0.set_xlabel("x (UA)")
ax0.set_ylabel("y (UA)")
ax0.set_title("Método de Euler")
ax0.legend(loc='lower left')

# Animación de la órbita mediante el método de Leap Frog
ax1.scatter(0, 0, s = 222, color = "orange", label = "Sol")
scatter1 = ax1.scatter(x_LeapFrog[0], y_LeapFrog[0], s = 25, color = "royalblue", label = "Tierra")
fig1.suptitle("Órbita del planeta tierra")

line3 = ax1.plot(eliptica_x[0], eliptica_y[0], label = 'Orbita "Real"', color = "limegreen", alpha=0.5)[0]
line4 = ax1.plot(x_LeapFrog[0], y_LeapFrog[0], label="Órbita con Leap Frog", ls = ":", color = "indigo")[0]
ax1.set(xlim=(-1.1, 1.1), ylim=(-1.1, 1.1), xlabel='Time [s]', ylabel='Z [m]')
ax1.set_xlabel("x (UA)")
ax1.set_ylabel("y (UA)")
ax1.set_title("Método Leap Frog")
ax1.legend(loc='upper right')

def update(frame):
    T_x_E = x_Euler[frame]
    T_y_E = y_Euler[frame]

    T_x_LF = x_LeapFrog[frame]
    T_y_LF = y_LeapFrog[frame]

    Eli_x = eliptica_x[:frame]
    Eli_y = eliptica_y[:frame]
    
    x = x_Euler[:frame]
    y = y_Euler[:frame]

    LF_x = x_LeapFrog[:frame]
    LF_y = y_LeapFrog[:frame]

    # update the line plot:
    line1.set_xdata(Eli_x[:frame])
    line1.set_ydata(Eli_y[:frame])

    line2.set_xdata(x[:frame])
    line2.set_ydata(y[:frame])

    line3.set_xdata(Eli_x[:frame])
    line3.set_ydata(Eli_y[:frame])
    
    line4.set_xdata(LF_x[:frame])
    line4.set_ydata(LF_y[:frame])

    scatter0.set_offsets([T_x_E, T_y_E])
    scatter1.set_offsets([T_x_LF, T_y_LF])

    return (line1, line2, line3, line4, scatter0, scatter1)

ani1 = animation.FuncAnimation(fig=fig1, func=update, frames=range(0,len(eliptica_x), 40))
ani1.save("PLOTS_CristianParra_S7C1_ODE2_Planetas_Tierra.gif", writer="pillow", fps=10)


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
fig2.savefig("PLOTS_CristianParra_S7C1_ODE2_Planetas_Sol.png")
