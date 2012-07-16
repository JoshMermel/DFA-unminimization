#include "vertex.h"
#include "node.h"
#include "circ_list.h"
#include <iostream>
#include <vector>

Circ_list::Circ_list(Vertex* vert)
{
	start_list_with(vert);
}

Circ_list::Circ_list(Circ_list* list)
{    
    //Copy start and set it up
	Node* remote_ptr = list->start;
	Vertex* tmp_vrt = new Vertex(remote_ptr->vert);
	start = new Node(tmp_vrt);
    start->next=start;
    start->prev=start;
	if(list->start->vert->index > 1000)
		cout << "urine\n";
	if(remote_ptr->next->vert->index > 1000)
	{
		cout << "poop\n";
	}
	remote_ptr=remote_ptr->next;
   	//continuously add new nodes to match the remote list
	while(remote_ptr->vert!=list->start->vert)
	{
      	add_to_list(new Node(new Vertex(remote_ptr->vert)), start);
		remote_ptr=remote_ptr->next;
	}
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
	Node* temp = start->next;
	while(temp != start)
	{
		if(!temp->vert->is_satisfied())
		{
			// check if start wants to connect to temp
			if(start->vert->needs(temp->vert->get_index()))
			{
				// connect them
				start->vert->set((temp->vert->index), true);
				temp->vert->set((start->vert->index), true);
				// also remove all vertices between them.
				cout << "Removing between vertex " << start->vert->index+1 << " and vertex " << temp->vert->index+1 << endl;
				remove(start, temp);
				return;
			}
			cout << "Vertex "<< temp->vert->index+1<< " doesn't need anything\n";
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
			if(start->vert->needs(temp->vert->get_index()))
			{
				// check if they should connect and connect them.
				start->vert->set((temp->vert->index), true);
				temp->vert->set((start->vert->index), true);
				// also remove all vertices between them.
				cout << "Removing between vertex " << start->vert->index+1 << " and vertex " << temp->vert->index+1 << endl;
				remove(temp, start);
				return;
			}
			cout << "Vertex "<< temp->vert->index+1<< " doesn't need anything\n";
			return;
		}
		temp = temp -> prev;
	}
}

void Circ_list::have_children(Vertex** vert_set, vector<int> perm)
{
	for(int i = 0; i < perm.size(); i++)
	{
		if(start->vert->needs(i))
		{
			cout << "Vertex " << start->vert->index+1 
                << " needs vertex " << perm[i]+1 << endl;
			// create that vertex and add it after start
			Vertex* temp_vert = new Vertex(vert_set[perm[i]]);
			Node* temp_node = new Node(temp_vert);
			add_to_list(temp_node, start);
			temp_vert->set((start->vert->index), true);
			// copy whatever vertex start pointed to after that vertex
			start->vert->set(perm[i], true);
			temp_node = new Node(new Vertex(start->vert));
			start->vert->increase_references();
			add_to_list(temp_node, start->next);
			start = start->next->next;
		}
	}	
	// incrememnt start to the next unsaturated node
	while(start->vert->is_satisfied())
	{
		cout << "Vertex " << start->vert->index+1 << " is happy for now.\n";
		start = start->next;
	}
}

void Circ_list::remove(Node* begin, Node* end)
{
	Node* temp = new Node;			// declare a temp node and make it the
	temp -> next = begin -> next;		// beginning of a new linked list whose
						// second node is the one after begin
	temp -> next -> prev = temp;		// correct that node's prev pointer
	end -> prev -> next = NULL;		// replace the end of the segment to be
						// removed with NULL
	begin -> next = end;			// contract the list so begin and end are
	end -> prev = begin;			// adjacent

	Node* tmp2 = temp;
	while(temp != NULL)			// now read from temp until NULL
	{
		tmp2 = temp;			// deleting the Node before where you are
		temp = temp->next;
		delete tmp2;
	}
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

Circ_list::~Circ_list()
{
	start->prev->next=NULL;
	while(start!=NULL)
	{	
		Node *temp=start;
		if(start->next==NULL){
			start=NULL;
			delete temp;
			break;
		}
		else 
			start=start->next;
		delete temp;
	}
}
