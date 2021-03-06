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
    num_verts = list->num_verts;
    copies = new int[num_verts];
    for(int i = 0; i < num_verts; i++)
        copies[i] = list->copies[i];
    //Copy start and set it up
	Node* remote_ptr = list->start;
	start = new Node(new Vertex(remote_ptr->vert));
    start->next=start;
    start->prev=start;
	remote_ptr=remote_ptr->next;
	Node* start_ptr = start;
   	//continuously add new nodes to match the remote list
	while(remote_ptr!=list->start)
	{
      	add_to_list(new Node(new Vertex(remote_ptr->vert)), start_ptr); 
		remote_ptr=remote_ptr->next;
		start_ptr = start_ptr->next;
	}
}

// insert the first node into the list
void Circ_list::start_list_with(Vertex* vert)
{
    num_verts = vert->size;
    copies = new int [num_verts];
    for (int i = 0; i < num_verts; i++)
        copies[i]=0;
    copies[vert->index] = 1;
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
		Node* temp = begin;
		cout << begin->vert->index +1<< ' ';
		temp = begin->next;
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
        // if our pointer's vertex is not yet satisfied
		if(!temp->vert->is_satisfied())
		{
			// check if start wants to connect to temp
			if(start->vert->needs(temp->vert->index))
			{
				// connect them
				start->vert->set((temp->vert->index), true);
				temp->vert->set((start->vert->index), true);
				// also remove all vertices between them.
				cout << "Removing between vertex " << start->vert->index+1 << " and vertex " << temp->vert->index+1 << endl;
				remove(start, temp);
				return;
			}
			cout << "Vertex "<< temp->vert->index+1<< " doesn't need Vertex " << start->vert->index+1 << endl;
			return;
		}
		temp = temp -> next;
	}
    // you may only connect once forward because you don't want to cut off
    // other vertices from being connected later.
}

void Circ_list::check_backward()
{
	Node* temp = start->prev;
	while(temp != start)
	{
		if(!temp->vert->is_satisfied())
		{
			if(start->vert->needs(temp->vert->index))
			{
				// check if they should connect and connect them.
				start->vert->set((temp->vert->index), true);
				temp->vert->set((start->vert->index), true);
				// also remove all vertices between them.
				cout << "Removing between vertex " << start->vert->index+1 << " and vertex " << temp->vert->index+1 << endl;
				remove(temp, start);
				return;
			}
			cout << "Vertex "<< temp->vert->index+1<< " doesn't need Vertex " << start->vert->index+1 << endl;
			return;
		}
		temp = temp -> prev;
	}
}

void Circ_list::have_children(Vertex** vert_set, vector<int> perm)
{
    // for each element in the permutation
	for(int i = 0; i < perm.size(); i++)
	{
        // does start need that vertex?
        // this is redundant because the needs of the vertex might be smaller
        // after check_forward and check_backward
		if(start->vert->needs(perm[i]))
		{
			cout << "Vertex " << start->vert->index+1 
                << " needs vertex " << perm[i]+1 << endl;
	        // mark that a new vertex, perm[i],  is being added
            copies[perm[i]]++;
            // create that vertex and add it after start
			Vertex* temp_vert = new Vertex(vert_set[perm[i]]);
			Node* temp_node = new Node(temp_vert);
			add_to_list(temp_node, start);
			temp_vert->set((start->vert->index), true);
			start->vert->set(perm[i], true);
			// copy whatever vertex start pointed to after that vertex.
			// note that this vertex is not copied but linked, this is
			// to preserve the neighbors vector, containing what that
			// vertex needs.  Also, it is not marked in copies[] becuase
            // it is not really a new vertex in the graph, just a new node
            // in the circularly linked list.
			temp_node = new Node(start->vert);
			start->vert->increase_references();
			add_to_list(temp_node, start->next);
            // move past the vertex we just added
			start = start->next->next;
		}
	}	
	// increment start to the next unsaturated node
	while(start->vert->is_satisfied())
	{
		cout << "Vertex " << start->vert->index+1 << " is happy for now.\n";
		start = start->next;
	}
}

bool Circ_list::check_any_less_than(int max)
{
    for(int i = 0; i < num_verts; i++)
        if(copies[i]<=max)
            return false;
    return true;
}

bool Circ_list::check_any_greater_than(int min)
{
    for(int i = 0; i < num_verts; i++)
        if(copies[i]>min)
            return true;
    return false;
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
    delete [] copies;
}
