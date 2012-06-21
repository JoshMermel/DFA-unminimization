#include "vertex.h"
#include "node.h"
#include "circ_list.h"
#include "bitset"
#include <iostream>


Circ_list::Circ_list(Vertex* vert)
{
	//initialize variables
	start = NULL;
	size = 0;
}

// insert the first node into the list
void Circ_list::start_list_with(Vertex* vert)
{
	// shuffle pointers appropriately
	start = vert;
	vert -> next = vert;
	vert -> prev = vert;

	// set size appropriately
	size = 1;
}

// insert a node with index a after the node called prior
void Circ_list::add_to_list(int a, Node* prior)
{
	//shuffle pointers to put the one in.
	Node* temp = new Node(Vertex(a));
	temp -> prev = prior;
	temp -> next = prior -> next;
	prior -> next = temp;
	temp -> next -> prev = temp;

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

void Circ_list::check_forward()
{
	Node* temp = start->next;
	while(temp != start)
	{
		if(!temp->vert->is_satisfied())
		{
			// check if they should connect and connect them.
			// also remove all vertices between them.
			return;
		}
		temp = temp -> next;
	}
}

void Circ_list::check_backward()
{
	Node* temp = start->prev;
	while(temp != start)
	{
		if(!temp->vert->is_satisfied())
		{
			// check if they should connect and connect them.
			// also remove all vertices between them.
			return;
		}
		temp = temp -> prev;
	}
}

void Circ_list::have_children()
{
	for(int i = 0; i < start.num_verices; i++)
	{

	}
}

void Circ_list::remove(Node* begin, Node* end)
{
	Node* temp;
	temp -> next = begin -> next;
	temp -> prev = end -> prev;
	begin -> next = end;
	end -> prev = begin;
	while(temp != end)
	{
		temp = temp -> next;
		temp->vert->decrease references();
	}
}

// WARNING, I think this fails in the case of a list of size 1. I shoudl check
// start before I do other stuff.
bool Circ_list::is_done()
{
	Node* temp = start -> next;
	// loop through the infinite face
	while(temp != start)
	{
		// return false if you see something unsatisfied
		if(!temp->vert->is_satisfied())
			return false;
		temp = temp-> next;
	}
	// if you get back to the start and have yet to see an unsatisfied vertex
	// go ahead and return true
	return true;
}
