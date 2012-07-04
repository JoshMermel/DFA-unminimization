expand: main.o circ_list.o node.o vertex.o
	g++ -g main.o circ_list.o node.o vertex.o -o expand

main.o: main.cpp
	g++ -g -c main.cpp

circ_list.o: circ_list.cpp
	g++ -g -c circ_list.cpp

node.o: node.cpp
	g++ -g -c node.cpp

vertex.o: vertex.cpp
	g++ -g -c vertex.cpp
