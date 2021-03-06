#ifndef MERMEL_VERTEX
#define MERMEL_VERTEX

using namespace std;

class Vertex
{
	public:
		Vertex(int my_index, int num_vertices);
			// the constructor,
			// sets a bunch of data
		
		Vertex(Vertex* vert);
			// copy constuctor for Vertex
        
        ~Vertex();
            // destructor
	
		void increase_references();
			// adds one to the number of references

		bool decrease_references();
			// subtracts one from the number of references and returns wheather
			// or not the number of references is bigger that 0

		int get_references();
			// a getter for the private variable, references

		bool needs(int index);
			// when passed an int representing an index, this function will
			// return true if the vertex that index represents is needed and
			// false if not.

		void set(int index, bool val);
			// changes the vector of bools to reflect the addition of a new
			// edge.

		bool is_satisfied();
			// checks if a vertex is has all necessary connections.

		void bit_print();
			// prints the bitset for a given vertex

		int index;
        int size;
		bool* neighbors;
       private:
		int references;
};


#endif
