PLOTS_CristianParra_S9C1_EDP_*.png : PLOTS_CristianParra_S9C1_EDP.py C2_EDP_*.dat
	python3 PLOTS_CristianParra_S9C1_EDP.py

C2_EDP.dat : ParraCristian_S9C1_EDP.cpp
	g++ ParraCristian_S9C1_EDP.cpp -o EDP.exe
	./EDP.exe