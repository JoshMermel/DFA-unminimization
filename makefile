expand: main.o circ_list.o node.o vertex.o
	g++ main.o circ_list.o node.o vertex.o

circ_list.o: circ_list.cpp
	g++ -c circ_list.cpp

node.o: node.cpp
	g++ -c node.cpp

vertex.o: vertex.cpp
	g++ -c vertex.cpp
