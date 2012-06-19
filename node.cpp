Node::Node()
{
	vert = NULL;
	next = NULL;
	prev = NULL;
}

Node::Node(Vertex* my_vert)
{
	vert = my_vert;
	next = NULL;
	prev = NULL;
}
