import numpy as np
import matplotlib.pyplot as plt

# Crear los datos desde 'EDO2.dat'
Datos = np.genfromtxt("EDO2.dat", delimiter=",")

# Variables del problema
t_final = 2.0
m = Datos[-1,0]
k = Datos[-1,1]
b = Datos[-1,2]
h = Datos[-1,3]

# Constantes de solución
omega = np.sqrt((k/m) - (b/2)**2)
C1 = 0.1
C2 = 0.05*b/omega

# División de cada tipo de dato en arreglos separados
tiempo = Datos[:-1,0]
x_Euler = Datos[:-1,1]
x_LeapFrog = Datos[:-1,2]
analitica = C1*np.cos(np.sqrt(k/m) * tiempo)

# Datos del caso amortiguado
x_Euler_A = Datos[:-1,3]  #Amortiguado
x_RK4_A = Datos[:-1,4]    #Amortiguado
analitica_A = np.exp(-(b/2) * tiempo) * (C1*np.cos(omega * tiempo) + C2*np.sin(omega * tiempo))

# Inicialización gráficas
fig0, ax0 = plt.subplots(figsize=(10,6))
fig1, ax1 = plt.subplots(figsize=(10,6))

# Gráfica del resorte
ax0.plot(tiempo, analitica, label="x Analítica", color = "limegreen")
ax0.plot(tiempo, x_Euler, label="x Euler", ls = "--", color = "crimson")
ax0.plot(tiempo, x_LeapFrog, label="x Leap Frog", ls = ":", lw= 2, color = "indigo")
ax0.set_xlabel("Tiempo t")
ax0.set_ylabel("Funcion x")
ax0.set_title(f"EDO 2do orden resorte (k = {k}, m = {m}, b = 0, h = {h})")
ax0.legend()
fig0.savefig("PLOTS_CristianParra_S6CASA_EDO2_RESORTE.png")

# Gráfica del resorte amortiguado
ax1.plot(tiempo, analitica_A, label="x Analítica Amortiguado", color = "limegreen")
ax1.plot(tiempo, x_Euler_A, label="x Euler Amortiguado", ls = "--", color = "crimson")
ax1.plot(tiempo, x_RK4_A, label="x RK4 Amortiguado", ls = ":", lw= 2, color = "indigo")
ax1.set_xlabel("Tiempo t")
ax1.set_ylabel("Funcion x")
ax1.set_title(f"EDO 2do orden amortiguado (k = {k}, m = {m}, b = {b}, h = {h})")
ax1.legend()
fig1.savefig("PLOTS_CristianParra_S6CASA_EDO2_AMORTIGUADO.png")