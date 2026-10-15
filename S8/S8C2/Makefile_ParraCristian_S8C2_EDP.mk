PLOTS_CristianParra_S8C2_EDP.png : PLOTS_CristianParra_S8C2_EDP.py C2_EDP.dat
	python3 PLOTS_CristianParra_S8C2_EDP.py

C2_EDP.dat : ParraCristian_S8C2_EDP.cpp
	g++ ParraCristian_S8C2_EDP.cpp -o EDP.exe
	./EDP.exe