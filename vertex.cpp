#include "vertex.h"
#include <iostream>

Vertex::Vertex(int my_index,int num_vertices)
{
	// fill the bitset with all ones
	neighbors.resize(num_vertices+1, 1);
	index = my_index;
	references = 1;
	cout << "the constructor for vertex ran successfully\n";
}

void Vertex::increase_references()
{
	references++;
}

bool Vertex::decrease_references()
{
	references--;
	return (references == 0);
}

int Vertex::get_references()
{
	return references;
}

int Vertex::get_index()
{
	return index;
}

bool Vertex::is_needed(int index)
{
	return neighbors[index];
}

void Vertex::set(int index, bool val)
{
	cout << "set was called\n";
	neighbors.at(index) = val;
}

bool Vertex::is_satisfied()
{
	for(int i = 1; i <= neighbors.size(); i++)
	{
		if(neighbors[i] == 0)
			return false;
	}
	return true;
}
