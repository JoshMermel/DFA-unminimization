expand: main.o circ_list.o node.o vertex.o argbottle.o
	g++ -g main.o circ_list.o node.o vertex.o argbottle.o -o expand -lpthread

main.o: main.cpp permute.cpp
	g++ -g -c main.cpp permute.cpp -lpthread

circ_list.o: circ_list.cpp
	g++ -g -c circ_list.cpp

node.o: node.cpp
	g++ -g -c node.cpp

vertex.o: vertex.cpp
	g++ -g -c vertex.cpp

argbottle.o: argbottle.cpp
	g++ -g -c argbottle.cpp
