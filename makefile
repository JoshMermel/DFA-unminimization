expand: main.o circ_list.o node.o vertex.o
	g++ -g main.o circ_list.o node.o vertex.o -o expand -lpthread

main.o: main.cpp
	g++ -g -c main.cpp -lpthread

circ_list.o: circ_list.cpp
	g++ -g -c circ_list.cpp

node.o: node.cpp
	g++ -g -c node.cpp

vertex.o: vertex.cpp
	g++ -g -c vertex.cpp
