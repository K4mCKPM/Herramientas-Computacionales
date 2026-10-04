import matplotlib.pyplot as plt
import numpy as np

aleatorios = "aleatorios.dat"
y = np.genfromtxt(aleatorios, delimiter=",")
x = np.arange(len(y))

plt.plot(x,y, color = "indigo")
plt.xlabel("Posición")
plt.ylabel("Valor del número")
plt.savefig("aleatorios.png")
