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

		void start_list_with(Vertex* vert);
			// adding the first element to the list is slightly different
			// than adding later elements so there is a specialized function
			// for it.

		void add_to_list(Node* to_add, Node* prior);
			// adds the node called to_add after the node call prior. 

		void print_list(Node* begin);
			// given a start point, this function prints the list move forward
			// from there stopping when it returns to the start point.
			// ?add a paramter to signify direction?

		void check_forward();
		void check_backward();
		void have_children(Vertex** vert_set, vector<int> perm);
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

        bool check_any_less_than(int max);
            // checks if all elements in copies have a number greater than max

        bool check_any_greater_than(int min);
            // checks if ANY element in copies has a number greater than min

		void remove(Node* begin, Node* end);
			// given a Node to start at, a node to end at it removes all
			// nodes (forward direction) between the two references 
			//appropriately.  If you want to delete backward just
			// switch the order of the parameters.
		~Circ_list();
		Node* start;
        int* copies;
            // There will be no way to decrement this because when a vertex
            // is placed in the graph, it will not be removed.  This is on
            // the mathematical level, and not the algorithmic level.
        int num_verts;
};

#endif
