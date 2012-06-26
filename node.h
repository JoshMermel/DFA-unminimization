/*
 * node, by Josh Mermelstein
 * Written 6/13/12
 * to be used as part of a circular doubly linked list.
 */

#ifndef MERMEL_NODE
#define MERMEL_NODE

#include "vertex.h"

class Node
{
	public:
		Node();
		// default constructor

		Node(Vertex *my_vert);
		// secondary constructor, takes a vertex and puts it in a Node

		~Node();
		// the destructor.  It handles some reference counting issues.

		// Note: there is intentionally not a destructor. Memory isn't being
		// leaked by not handling deleting vert because the deleting of
		// verticies is handled by main.

		Vertex* vert;
		Node* next;
		Node* prev;
};

#endif
