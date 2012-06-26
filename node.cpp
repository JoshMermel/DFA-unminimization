#include "node.h"
using namespace std;

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

Node::~Node()
{
	vert->decrease_references();
	if(vert->get_references() == 0)
		delete vert;
}
