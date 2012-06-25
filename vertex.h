#ifndef MERMEL_VERTEX
#define MERMEL_VERTEX

#include <vector>

using namespace std;

class Vertex
{
	public:
		Vertex(int my_index);
			// the constructor,
			// sets a bunch of data
		
		void increase_reference();
			// adds one to the number of references

		bool decrease_references();
			// subtracts one from the number of references and returns wheather
			// or not the number of references is bigger that 0

		int get_index();
			// a getter for the private variable, index

		bool is_needed(int index);
			// when passed an int representing an index, this function will
			// return true if the vertex that index represents is needed and
			// false if not.

		void set(int index, int val);
			// changes the vector of bools to reflect the addition of a new
			// edge.

		bool is_satisfied();
			// checks if a vertex is has all necessary connections.

	private:
		int index;
		vector<bool> neighbors;
		int references;
};


#endif
