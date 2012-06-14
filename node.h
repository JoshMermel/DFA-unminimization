/*
 * node, by Josh Mermelstein
 * Written 6/13/12
 * to be used as part of a circular doubly linked list.
 */

#ifndef MERMEL_NODE
#define MERMEL_NODE

class Node
{
	public:
		Node();
		~Node();

		Vertex* vert;
		Node* next;
		Node* prev;

	private:
};

#endif
