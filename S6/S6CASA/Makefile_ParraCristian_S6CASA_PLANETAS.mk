PLOTS_CristianParra_S6CASA_PLANETAS.png : PLOTS_CristianParra_S6CASA_ODE2_PLANETAS.py Planetas.dat
	python3 PLOTS_CristianParra_S6CASA_ODE2_PLANETAS.py

Planetas.dat : ParraCristian_S6CASA_ODE2_PLANETAS.cpp
	g++ ParraCristian_S6CASA_ODE2_PLANETAS.cpp -o ODE2_PLANETAS.exe
	./ODE2_PLANETAS.exe