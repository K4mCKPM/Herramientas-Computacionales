PLOTS_CristianParra_S7C2_EDP.png : PLOTS_CristianParra_S7C2_EDP.py EDP.dat
	python3 PLOTS_CristianParra_S7C2_EDP.py

EDP.dat : ParraCristian_S7C2_EDP.cpp
	g++ ParraCristian_S7C2_EDP.cpp -o EDP.exe
	./EDP.exe