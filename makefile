all: main

main: main.cpp graph.cpp graph.h
	g++ -std=c++11 main.cpp graph.cpp -o main

clean: 
	rm main