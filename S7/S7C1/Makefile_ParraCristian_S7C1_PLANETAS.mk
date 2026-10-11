PLOTS_CristianParra_S7C1_PLANETAS_Tierra.png : PLOTS_CristianParra_S7C1_ODE2_PLANETAS.py Planetas.dat
	python3 PLOTS_CristianParra_S7C1_ODE2_PLANETAS.py

Planetas.dat : ParraCristian_S7C1_ODE2_PLANETAS.cpp
	g++ ParraCristian_S7C1_ODE2_PLANETAS.cpp -o ODE2_PLANETAS.exe
	./ODE2_PLANETAS.exe