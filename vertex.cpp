Vertex::Vertex(int my_index)
{
	// fill the bitset with all ones
	neighbors.resize(num_vertices, 1)
	index = myindex;
	//now read through the definition of the vector with index myindex and set
	//all values listed as associated with it to 0;
	int temp;
	while(cin >> temp)
	{
		neighbors.set(temp, 0);
	}
}

int Vertex::get_index()
{
	return index;
}

bool Vertex::is_needed(int index)
{
	return neighbors[i];
}

void Vertex::set(int index, int val)
{
	neighbors[index] = val;
}

bool Vertex::is_satisfied()
{
	for(int i = 0; i < neighbors.size(); i++)
	{
		if(neighbors[i] == 0)
			return false;
	}
	return true;
}
