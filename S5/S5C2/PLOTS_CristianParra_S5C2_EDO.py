import numpy as np
import matplotlib.pyplot as plt

archivos = ["datosh01.dat", "datosh005.dat", "datosh001.dat", "datosh0005.dat"]

# Inicio ambas figuras para guardar las imágenes con los gráficos
fig1, ejes1 = plt.subplots(1, 4, figsize=(18, 4))
fig2, ejes2 = plt.subplots(1, 4, figsize=(18, 4), sharey=True)

for file, axs1, axs2 in zip(archivos, ejes1, ejes2):
    datos = np.genfromtxt(file, delimiter = ",")

    #Desde los archivos cargo el tiempo, el método de Euler y el método RK4
    t = datos[:,0]     
    Analitica = np.exp(-t)

    Euler = datos[:,1]
    Euler_err = np.abs(Analitica - Euler)

    RK4 = datos[:,2]
    RK_err = np.abs(Analitica - RK4)

    # Creación gráfica de comparación entre los métodos
    axs1.plot(t, Analitica, label="Analítica")
    axs1.plot(t, Euler, label="Euler", color = "indigo", ls=":")
    axs1.plot(t, RK4, label="RK4", color = "darkgreen", ls="-.")

    axs1.set_xlabel("Tiempo (t)")
    axs1.set_title(f"h = 0.{file[7:-4]}")
    axs1.legend()
    axs1.grid(True)

    # Creación gráfica de comparación de los errores
    axs2.semilogy(t, Euler_err, label="Error Euler", color = "indigo")
    axs2.semilogy(t, RK_err, label="Error RK4", color = "darkgreen")
    
    axs2.set_xlabel("Tiempo (t)")
    axs2.set_title(f"h = 0.{file[7:-4]}")
    axs2.legend()
    axs2.grid(True)

fig1.suptitle("Comparación del método de Euler y el Método de RK4 para distintos valores de h")
fig2.suptitle("Comparación de los errores del método Euler y el Método de RK4 para distintos valores de h")
ejes1[0].set_ylabel("Valor función (y)")
ejes2[0].set_ylabel("Error")
ejes2[3].tick_params(axis="y", right=True, labelright=True)

# Guardo ambas gráficas en su respectivo archivo .png
fig1.savefig("Plots_EDO.png")
fig2.savefig("Errors_EDO.png")