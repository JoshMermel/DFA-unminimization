/*
 * Circ_list, by Josh Mermelstein.
 * written 6/12/12
 * creates a circular doubly linked list of pointers to vertices
 * 
 * issue: main has a master set of verticies denoting what each vertex has and
 * wants.  We can't point to those objects because we will need copies of them
 * as they were.
 * solution: copy constructor?
 * 
 */

#ifndef MERMEL_CIRCLIST
#define MERMEL_CIRCLIST

#include <cmath>
#include "vertex.h"
#include "node.h"

using namespace std;

class Circ_list
{
	public:
		Circ_list();
			// the default constructor for the class
		
		void start_list_with(Vertex* vert);
			// adding the first element to the list is sleightly different
			// than adding later elements so there is a specialized function
			// for it.

		void add_to_list(int a, Node* prior);
			// given an integer to add and a node after which to add it, this
			// function creates a new node and shuffles pointers to get it into
			// place

		void print_list(Node* begin);
			// given a start point, this function prints the list move forward
			// from there stopping when it returns to the start point.
			// ?add a paramter to signify direction?

		void check_forward();
		void check_backward();
		void have_children();
			// these three functions should always be called in this order.
			// The first two check forward and backward for the first
			// non-saturated vertex and if it is one that can pair with the
			// vertex they are checking from does so.
			//
			// the third function then checks which of its requirements aren't
			// satisfied and creates appropriate vertices and adjusts the
			// circular linked list as appropriate.  It all adjusts the value
			// of the start pointer

		bool is_done();
			// checks if all verices in the list are satisfied or not.

		void remove(Node* begin, Node* end,);
			// given a Node to start at, a node to end at it removes all
			// nodes (forward direction) between the two references 
			//appropriately.  If you want to delete backward just
			// switch the order of the parameters.
			
	private:
		Node* start;
};

#endif
