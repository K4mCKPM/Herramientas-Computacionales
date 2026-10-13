PLOTS_CristianParra_S8C1_EDP.png : PLOTS_CristianParra_S8C1_EDP.py EDP.dat
	python3 PLOTS_CristianParra_S8C1_EDP.py

EDP.dat : ParraCristian_S8C1_EDP.cpp
	g++ ParraCristian_S8C1_EDP.cpp -o EDP.exe
	./EDP.exe