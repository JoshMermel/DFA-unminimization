/*
 * node, by Josh Mermelstein
 * Written 6/13/12
 * to be used as part of a circular doubly linked list.
 */

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
