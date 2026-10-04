aleatorios.png : aleatorios.dat num_aleatorios.py
	python3 num_aleatorios.py

aleatorios.dat : ParraCristian_S5C2_repasoC.cpp
	g++ ParraCristian_S5C2_repasoC.cpp
	./a.out