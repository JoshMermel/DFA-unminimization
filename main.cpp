#include "circ_list.h"
#include <iostream>
using namespace std;

int main()
{
	// determine how many vertices there are
	int num_vertices;
	cin >> num_vertices;

	// create an array to store them
	Vertex** vert_set = new Vertex*[num_vertices];

	// read them into that array
	string temp="";
	for(int i = 0; i < num_vertices; i++)
	{
		vert_set[i] = new Vertex(num_vertices, i);
		while(strcmp(temp.c_str(),"\n"))
		//read stdin char by char until newline
		{
		  scanf("%s", &temp);
		  vert_set[i]->set(atoi(temp.c_str()), 0);
		}
		getchar();//eat the remaining newline
	}

	// declare the circular doubly linked list and put the vertex whose index
	// is the same as the enviromental variable first into it to start it
	Circ_list my_list(vert_set[atoi(getenv("FIRST"))]);

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
			return 0;
		}
		// now look at what it is missing and create those nodes
		my_list.have_children(vert_set);
	}

	cout << "flow got to the end of main - past the while loop\n";
	exit(1);
}
