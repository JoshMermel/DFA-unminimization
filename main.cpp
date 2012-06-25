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
	int temp;
	for(int i = 0; i < num_vertices; i++)
	{
		vert_set[i] = new Vertex(i);
		while(cin >> temp) //NEEDS CHANGE.
		{
			vert_set[i]->set(temp, 0);
		}
	}

	// declare the circular doubly linked list
	Circ_list my_list;

	// put one of the vertices into it.
	// which vertex is put in is determined by an enviromental variable called
	// "FIRST"
	my_list.start_list_with(vert_set[atoi(getenv("FIRST"))]);


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
