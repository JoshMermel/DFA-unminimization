#include "circ_list.h"
#include <iostream>

using namespace std;

int main()
{
	// determine how many vertices there are
	int num_vertices;
	cin << num_vertices;

	// create an array to store them
	Vertex** vert_set = new Vertex*[num_vertices];

	// read them into that array
	for(int i = 0; i < num_vertices; i++)
	{
		vert_set[i] = new Vertex(i);
		while(cin >> temp)
		{
			vert_set[i].set(temp, 0);
		}
	}

	// declare the circular doubly linked list
	circ_list my_list;

	// put on of the vertices into it.
	circ_list.add_to_list(vert_set(get_env(FIRST)), NULL);
	//IMPORTANT, figure out which one this should be

	while(true)
	{
		// check forward and backward of the vertex to see if it want to
		// connect to the nearest non-saturated neighber and vice versa
			// do or don't do it
			// if you did, check if every vertex is satisfied
				//if so, end.
		// now look at what it is missing and create those nodes
		// adjust the circ_list as appropriate
	}

	return 0;
}
