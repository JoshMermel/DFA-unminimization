Node::Node()
{
	vert = NULL;
}

Node::Node(Vertex* my_vert)
{
	vert = my_vert;
}

Node::~Node()
{
	delete vert; 
}
