PLOTS_CristianParra_S9C1_EDP_Fija.png : PLOTS_CristianParra_S9C1_EDP.py C2_EDP_Fija.dat
	python3 PLOTS_CristianParra_S9C1_EDP.py

C2_EDP_Fija.dat : ParraCristian_S9C1_EDP.cpp
	g++ ParraCristian_S9C1_EDP.cpp -o EDP.exe
	./EDP.exe