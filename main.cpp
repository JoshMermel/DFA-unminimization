#include "circ_list.h"
#include <iostream>
#define FIRST 0
using namespace std;

int main(int argc, char* argv[])
{
	// determine how many vertices there are
	int num_vertices;
	cin >> num_vertices;
	// purges a newline from the stream
	cin.get();

	// create an array to store them
	Vertex** vert_set = new Vertex*[num_vertices];
	// read them into that array
	char temp;
	string temp_string;
	
	// for each vertex
	for(int i = 0; i < num_vertices; i++)
	{
		// create an object to hold the data
		vert_set[i] = new Vertex(i, num_vertices);
		// read until you see a newline
		temp = 'b';
		while(1)
		{
			temp_string = "";
			if(temp == '\n')
				break;
			temp = cin.get();
			//r read until you see a space
			while(1)
			{
				if(temp == ' ' || temp=='\n')
					break;
				//concatonate newly read chars onto temp_string
				temp_string += temp;
				temp = cin.get();
			}
			// set the vertex to know that it needs what was just found
			vert_set[i]->set(atoi(temp_string.c_str())-1, 0);
		}
			
	}



	// declare the circular doubly linked list and put the vertex whose index
	// is the same as the enviromental variable first into it to start it
	
	Circ_list my_list(vert_set[FIRST]);

	while(true)
	{
		
		// check forward and backward of the vertex to see if it want to
		// connect to the nearest non-saturated neighber and vice versa
		my_list.check_forward();
		my_list.check_backward();
		// check if we are done
		if(my_list.is_done())
		{
			//delete some dynamically allocated memory
			cout << "I win!\n";
			return 0;
		}
		// now look at what it is missing and create those nodes
		my_list.have_children(vert_set);
	}

	cout << "flow got to the end of main - past the while loop\n";
	exit(1);
}
