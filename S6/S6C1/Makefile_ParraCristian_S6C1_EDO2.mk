PLOTS_CristianParra_S6C1_EDO2.png : PLOTS_CristianParra_S6C1_EDO2.py EDO2.dat
	python3 PLOTS_CristianParra_S6C1_EDO2.py

EDO2.dat : ParraCristian_S6C1_EDO2orden.cpp
	g++ ParraCristian_S6C1_EDO2orden.cpp -o EDO2.exe
	./EDO2.exe