import matplotlib.pyplot as plt
import numpy as np

aleatorios = "aleatorios.dat"
y = np.genfromtxt(aleatorios, delimiter=",")
x = np.arange(len(y))

plt.scatter(x,y, color = "indigo", s=1.5)
plt.xlabel("Posición")
plt.ylabel("Valor del número")
plt.savefig("aleatorios.png")
