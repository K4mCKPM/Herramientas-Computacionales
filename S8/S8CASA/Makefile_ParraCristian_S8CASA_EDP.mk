# Calcular la gráfica para '*_Fijo.png' calcula también la de '*_Forzado.png', por eso no está explícito
PLOTS_CristianParra_S8CASA_EDP_Fijo.png : PLOTS_CristianParra_S8CASA_EDP.py EDP_Fijo.dat
	python3 PLOTS_CristianParra_S8CASA_EDP.py

# Al igual que las gráficas, como ambos archivos de datos se calculan desde el mismo archivo, solo dejo
# explícito para 'EDP_Fijo.dat', y ya queda implícito 'EDP_Forzado.dat'
EDP_Fijo.dat : ParraCristian_S8CASA_EDP.cpp
	g++ ParraCristian_S8CASA_EDP.cpp -o EDP.exe
	./EDP.exe