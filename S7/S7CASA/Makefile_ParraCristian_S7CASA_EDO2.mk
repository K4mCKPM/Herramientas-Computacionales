PLOTS_CristianParra_S7CASA_EDO2.png : PLOTS_CristianParra_S7CASA_EDO2.py EDO2.dat
	python3 PLOTS_CristianParra_S7CASA_EDO2.py

EDO2.dat : ParraCristian_S7CASA_EDO2orden_RESORTE.cpp
	g++ ParraCristian_S7CASA_EDO2orden_RESORTE.cpp -o EDO2.exe
	./EDO2.exe