# Las imágenes de los gráficos de la función solución y de los errores son las de más alto nivel
Plots_EDO.png Errors_edo.png: PLOTS_CristianParra_S5CASA_EDO.py datosh01.dat datosh001.dat datosh005.dat datosh0005.dat
	python3 PLOTS_CristianParra_S5CASA_EDO.py

# Los datos para h=0.005 se cargan desde el archivo c++
datosh0005.dat : ParraCristian_S5CASA_EDO.cpp
	g++ ParraCristian_S5CASA_EDO.cpp -o EDO.exe
	./EDO.exe

# Los datos para otros h verifican si h=0.005 se actualizó
datosh01.dat datosh001.dat datosh005.dat: datosh0005.dat