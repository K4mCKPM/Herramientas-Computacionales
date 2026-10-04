aleatorios.png : aleatorios.dat num_aleatorios.py
	python3 num_aleatorios.py

aleatorios.dat : ParraCristian_S5CASA_repasocpp.cpp
	g++ ParraCristian_S5CASA_repasocpp.cpp -o repaso.exe
	./repaso.exe