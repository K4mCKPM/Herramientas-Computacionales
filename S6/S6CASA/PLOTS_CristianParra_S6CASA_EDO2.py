import numpy as np
import matplotlib.pyplot as plt

Datos = np.genfromtxt("EDO2.dat", delimiter=",")
b = 0.08
k = 50
m = 0.2
omega = np.sqrt((k/m) - (b/2)**2)
C1 = 0.1
C2 = 0.05*b/omega

tiempo = Datos[:,0]
x_Euler = Datos[:,1]
x_LeapFrog = Datos[:,2]
x_Euler_A = Datos[:,3]  #Amortiguado
analitica = C1*np.cos(np.sqrt(k/m) * tiempo)
analitica_A = np.exp(-(b/2) * tiempo) * (C1*np.cos(omega * tiempo) + C2*np.sin(omega * tiempo))

fig0, ax0 = plt.subplots(figsize=(10,6))
fig1, ax1 = plt.subplots(figsize=(10,6))

ax0.plot(tiempo, x_Euler, label="x Euler")
ax0.plot(tiempo, x_LeapFrog, label="x Leap Frog", ls = "--")
ax0.plot(tiempo, x_Euler_A, label="x Euler Amortiguado", ls = "-.")

ax0.set_xlabel("Tiempo t")
ax0.set_ylabel("Funcion x")
ax0.legend()
fig0.savefig("PLOTS_CristianParra_S6CASA_EDO2_RESORTE.png")

plt.plot(tiempo, analitica, label="x Leap Frog", ls = "--")
plt.plot(tiempo, analitica_A, label="x Analítica Amortiguado", ls = "-.")
plt.xlabel("Tiempo t")
plt.ylabel("Funcion x")
plt.legend()
fig1.savefig("PLOTS_CristianParra_S6CASA_EDO2_AMORTIGUADO.png")