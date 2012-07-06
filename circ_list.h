/*
 * Circ_list, by Josh Mermelstein and Michael James
 * written 6/12/12
 * creates a circular doubly linked list of pointers to vertices
 * 
 */

#ifndef MERMEL_CIRCLIST
#define MERMEL_CIRCLIST

#include <cmath>
#include "vertex.h"
#include "node.h"
#include <vector>

using namespace std;

class Circ_list
{
	public:
		Circ_list(Vertex* vert);
			// the default constructor for the class
		
		Circ_list(Circ_list* list);
			// copy constructor, goes through the list and makes a copy
			//PRECONDITIONS: The list has at least one element and no
			//	pointer points to NULL
						
		void start_list_with(Vertex* vert);
			// adding the first element to the list is slightly different
			// than adding later elements so there is a specialized function
			// for it. It should only be called once during the running of
			// this program

		void add_to_list(Node* to_add, Node* prior);
			// adds the node called to_add after the node call prior. 

		void print_list(Node* begin);
			// given a start point, this function prints the list move forward
			// from there stopping when it returns to the start point.
			// ?add a parameter to signify direction?

		void check_forward();
		void check_backward();
		Circ_list have_children(Vertex** vert_set, vector<int>  permutation);
			// these three functions should always be called in this order.
			// The first two check forward and backward for the first
			// non-saturated vertex and if it is one that can pair with the
			// vertex they are checking from does so.
			//
			// the third function then checks which of its requirements aren't
			// satisfied and creates appropriate vertices and adjusts the
			// circular linked list as appropriate.  It all adjusts the value
			// of the start pointer
            //
            // PRECONDITION: permutation is a vector full of ints which
            //      correspond with the index of the vertices that start needs.
            // POSTCONDITION: outputs the changed circ_list

		bool is_done();
			// checks if all vertices in the list are satisfied or not.

		void remove(Node* begin, Node* end);
			// given a Node to start at, a node to end at it removes all
			// nodes (forward direction) between the two references 
			//appropriately.  If you want to delete backward just
			// switch the order of the parameters.
		
		~Circ_list();
			// the destructor for circ_list.  This function is only called
			// after the program has successfully expanded a graph of if it
			// receives a signal to stop running (to prevent memory leaks)
		Node* start;
};

#endif
