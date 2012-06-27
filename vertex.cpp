#include "vertex.h"
#include <iostream>

Vertex::Vertex(int my_index,int num_vertices)
{
	// fill the bitset with all ones
	neighbors.resize(num_vertices+1,1);
	index = my_index;
	references = 1;
}

Vertex::Vertex(Vertex* vert)
{
	index = vert->index;
	references = 1;
	neighbors = vert->neighbors;
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
	return !neighbors[index];
}

void Vertex::set(int index, bool val)
{
	neighbors.at(index) = val;
}

bool Vertex::is_satisfied()
{
	for(int i = 1; i < neighbors.size(); i++)
	{
		if(neighbors[i] == 0)
			return false;
	}
	return true;
}
