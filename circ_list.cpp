#include "vertex.h"
#include "node.h"
#include "circ_list.h"
#include <iostream>


Circ_list::Circ_list(Vertex* vert)
{
	start_list_with(vert);
}

// insert the first node into the list
void Circ_list::start_list_with(Vertex* vert)
{
	// shuffle pointers appropriately
	Vertex* V = new Vertex(vert);
	start = new Node(V);
	start -> next = start;
	start -> prev = start;
}

// insert a node called to_add after the node called prior
void Circ_list::add_to_list(Node* to_add, Node* prior)
{
	//shuffle pointers to put the one in.
	
	to_add -> prev = prior;
	to_add-> next = prior -> next;
	prior -> next = to_add;
	to_add -> next -> prev = to_add;
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
		Node* temp = begin->next;
		cout << begin->vert->index +1<< ' ';
		while(temp != begin)
		{
			cout << temp->vert->index +1<< ' ';
			temp = temp -> next;
		}
		cout << endl;
	}
}

void Circ_list::check_forward()
{
	cout << "contracting forward\n";
	Node* temp = start->next;
	while(temp != start)
	{
		if(!temp->vert->is_satisfied())
		{
			// check if start wants to connect to temp
			if(start->vert->is_needed(temp->vert->get_index()))
			{
				// connect them
				start->vert->set((temp->vert->index)-1, true);
				temp->vert->set((start->vert->index)-1, true);
				// also remove all vertices between them.
				remove(start, temp);
				print_list(start);
				return;
			}
		}
		temp = temp -> next;
	}
	print_list(start);
}

void Circ_list::check_backward()
{
	cout << "contracting backward\n";
	Node* temp = start->prev;
	while(temp != start)
	{
		if(!temp->vert->is_satisfied())
		{
			if(start->vert->neighbors[(temp->vert->index)-1] == 0)
			{
				// check if they should connect and connect them.
				start->vert->set((temp->vert->index)-1, true);
				temp->vert->set((start->vert->index)-1, true);
				// also remove all vertices between them.
				remove(temp, start);
				print_list(start);
				return;
			}
		}
		temp = temp -> prev;
	}

	print_list(start);
}

void Circ_list::have_children(Vertex** vert_set)
{
	for(int i = 0; i < start->vert->neighbors.size(); i++)
	{
		// check if it needs a vertex
		if(start->vert->is_needed(i))
		{
			// create that vertex and add it after start
			Vertex* temp_vert = new Vertex(vert_set[i]);
			Node* temp_node = new Node(temp_vert);
			add_to_list(temp_node, start);
			temp_vert->set((start->vert->index), true);
			// copy whatever vertex start pointed to after that vertex
			start->vert->set(i, true);
			temp_node = new Node(start->vert);
			start->vert->increase_references();
			add_to_list(temp_node, start->next);
			start = start->next->next;
		}
	}
	cout << "having children\n";
	print_list(start);
	start->vert->bit_print();
	// incrememnt start to the next unsaturated node
	while(start->vert->is_satisfied())
	{
		start = start->next;
	}
}

void Circ_list::remove(Node* begin, Node* end)
{
/*
	if(begin->next->next == end)
	{
		cout << "fuckity fuck\n";
		exit(1);
	}
*/
	Node* temp = new Node;			// declare a temp node and make it the
	temp -> next = begin -> next;		// beginning of a new linked list whose
						// second node is the one after begin
	temp -> next -> prev = temp;		// correct that node's prev pointer
	end -> prev -> next = NULL;		// replace the end of the segment to be
						// removed with NULL
	begin -> next = end;			// contract the list so begin and end are
	end -> prev = begin;			// adjacent
/*	while(temp != NULL)			// now read from temp until NULL
	{
						// deleting the Node before where you are
		if(temp->next = NULL)
		{
			delete temp;
			cout << "remove finished successfully\n";
			return;
		}
		temp = temp -> next;
		delete temp -> prev;	// as you read
	}*/
}

bool Circ_list::is_done()
{
	if(!start->vert->is_satisfied())
	{
		return false;
		// without this line, this function would fail on lists of size 1
	}

	Node* temp = start -> next;
	// loop through the infinite face
	while(temp != start)
	{
		// return false if you see something unsatisfied
		if(!temp->vert->is_satisfied())
		{
			return false;
		}
		temp = temp-> next;
	}
	// if you get back to the start and have yet to see an unsatisfied vertex
	// go ahead and return true
	return true;
}
