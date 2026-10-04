import numpy as np
import matplotlib.pyplot as plt

Datos = np.genfromtxt("EDO2.dat", delimiter=",")

tiempo = Datos[:,0]
x_Euler = Datos[:,1]
x_LeapFrog = Datos[:,2]
v_LeapFrog = Datos[:,3]

fig = plt.figure(figsize=(10,6))

plt.plot(tiempo, x_Euler, label="x Euler")
plt.plot(tiempo, x_LeapFrog, label="x Leap Frog")
#plt.plot(tiempo + 1/2, v_LeapFrog, label="v Leap Frog")
plt.xlabel("Paso n")
plt.ylabel("Funcion x")
plt.legend()
fig.savefig("PLOTS_CristianParra_S6C1_EDO2.png")