/*
 * Circ_list, by Josh Mermelstein.
 * written 6/12/12
 * creates a circular doubly linked list of pointers to vertices
 * 
 * last edit 6/12/12
 */

#include <cmath>
#include "vertex"

using namespace std;

struct Node
{
	Vertex* vert;
	Node* next;
	Node* prev;
};

class Circ_list
{
	public:
		Circ_list();
			// the default constructor for the class

		void add_to_list(int a, Node* prior);
			// given an integer to add and a node after which to add it, this
			// function creates a new node and shuffles pointers to get it into
			// place

		void print_list(Node* begin);
			// given a start point, this function prints the list move forward
			// from there stopping when it returns to the start point.
			// ?add a paramter to signify direction?

	private:
		Node* start;
};
