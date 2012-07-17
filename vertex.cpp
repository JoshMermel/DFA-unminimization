#include "vertex.h"
#include <iostream>

Vertex::Vertex(int my_index,int num_vertices)
{
	// fill the bitset with all ones
	neighbors = new bool[num_vertices];
    for(int i = 0; i < num_vertices; i++)
        neighbors[i]=1;
    size = num_vertices;
	index = my_index;
	references = 1;
}

Vertex::Vertex(Vertex* vert)
{
	index = vert->index;
    size = vert->size;
	references = 1;
	neighbors = new bool[size];
    for(int i = 0; i < size; i++)
        neighbors[i]=vert->neighbors[i];
}

Vertex::~Vertex()
{
    delete [] neighbors;
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

bool Vertex::needs(int index)
{
	return !neighbors[index];
}

void Vertex::set(int index, bool val)
{
	neighbors[index] = val;
}

bool Vertex::is_satisfied()
{
	for(int i = 0; i < size; i++)
	{
		if(neighbors[i] == 0)
			return false;
	}
	return true;
}

void Vertex::bit_print()
{
	cout << "bitset[" << index << "]:";
	for(int i = 0; i < size; i++)
	{
		cout << neighbors[i];
	}
	cout << endl;
}