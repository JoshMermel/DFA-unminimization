#include "vertex.h"
#include "node.h"
#include "circ_list.h"
#include "bitset"
#include <iostream>


Circ_list::Circ_list()
{
	//initialize variables
	start = NULL;
	size = 0;
}

//insert a node with index a after the node called prior
void Circ_list::add_to_list(int a, Node* prior)
{
	// if the list isn't empty
	if(prior != NULL)
	{
		//shuffle pointers to put the one in.
		Node* temp = new Node(Vertex(a));
		temp -> prev = prior;
		temp -> next = prior -> next;
		prior -> next = temp;
		temp -> next -> prev = temp;
		}
	// otherwise (the list is empty), put the node to be added in.
	else
	{
		start = new Node(Vertex(a));
		start -> next = start; 
		start -> prev = start;
	}

	// keep track of the size
	size++;
}

// passed a Node* at which to start printing
// prints forward from that node until it loops
void Circ_list::print_list(Node* begin)
{
	if(begin == NULL)
	{
		cout << "the list is empty\n";
	}
	else
	{
		cout << begin->vert->index << endl;
		Node* temp = begin->next;
		while(temp != begin)
		{
			cout << temp->vert->index << endl;
			temp = temp -> next;
		}
	}
}
