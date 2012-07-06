#include "circ_list.h"
#include <iostream>
#include <fstream>
using namespace std;

void graphContract(Vertex** vert_set, int num_verts);

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		cout << "This program takes in 2 parameters: the start vertex number ";
		cout << "and then the location of the graph file. The 1st vertex is ";
		cout << "number 1. Do not be confused that under the hood we start ";
		cout << "with 0\n";
		exit(-1);
	}

	ifstream myfile(argv[2]);
	if(!myfile.is_open())
	{
		cout << "BAD FILENAME, HAVE SOME CAKE\n";
	}
	// determine how many vertices there are
	int num_vertices;
	myfile >> num_vertices;
	// purges a newline from the stream
	myfile.get();

	// create an array to store them
	Vertex** vert_set = new Vertex*[num_vertices];
	// read them into that array
	char temp;
	string temp_string;
	
	// for each vertex
	for(int i = 0; i < num_vertices; i++)
	{
		// create an object to hold the data
		vert_set[i] = new Vertex(i, num_vertices);
		// read until you see a newline
		//this is a garbage value to be rewritten by the following loop
		temp = 'b';
		while(1)
		{
			temp_string = "";
			if(temp == '\n')
				break;
			temp = myfile.get();
			//r read until you see a space
			while(1)
			{
				if(temp == ' ' || temp=='\n')
					break;
				//concatonate newly read chars onto temp_string
				temp_string += temp;
				temp = myfile.get();
			}
			// set the vertex to know that it needs what was just found
			vert_set[i]->set(atoi(temp_string.c_str())-1, 0);
		}
			
	}
	
	graphContract(vert_set, num_vertices);


	// declare the circular doubly linked list and put the vertex whose index
	// is the same as the enviromental variable first into it to start it
	
	Circ_list my_list(vert_set[atoi(argv[1])-1]);

	while(true)
	{
		
		// check forward and backward of the vertex to see if it want to
		// connect to the nearest non-saturated neighber and vice versa
		my_list.print_list(my_list.start);
		my_list.check_forward();
		my_list.print_list(my_list.start);
		my_list.check_backward();
		// check if we are done
		if(my_list.is_done())
		{
			//delete some dynamically allocated memory
			cout << "I win!\n";
			for(int i=0;i<num_vertices;i++)
			{
				delete vert_set[i];	
			}
			delete [] vert_set;
			return 0;
		}
		// now look at what it is missing and create those nodes
		my_list.print_list(my_list.start);
		my_list.have_children(vert_set);
	}

	cout << "flow got to the end of main - past the while loop\n";
	exit(1);
}
//conract the graph so that there are no dangling nodes and so the graph is as simple as possible.  Thus there should be no tails no nodes with degree two or less.  This does not affect the math as these nodes could be trvially added back in after the algrorithm's expansion
void graphContract(Vertex** vert_set, int num_verts)
{
	for(int i=0; i<num_verts; i++)
	{
		int boolcount=0;
		for(int j=0;j<num_verts;j++)
		{
			if(vert_set[i]->neighbors[j]==0)
				boolcount++;
		}
		if(boolcount==2)
		{
			int vprev=0,vnext=0;
			for(vprev; vprev<num_verts; vprev++)
				if(vert_set[i]->neighbors[vprev]==0) break;
			vnext=vprev+1;
			for(vnext; vnext<num_verts; vnext++)
				if(vert_set[i]->neighbors[vnext]==0) break;
			vert_set[vprev]->set(i,1); //perhaps "muting" will suffice for now
			vert_set[i]->set(vprev,1);
			vert_set[vnext]->set(i,1);
			vert_set[i]->set(vprev,1);
			//must reconnect
			vert_set[vprev]->set(vnext,0);
			vert_set[vnext]->set(vprev,0);
			cout << "2) Contracting and connecting vertex " << vprev+1 << ", vertex " << i+1 << ", and vertex " << vnext+1 << endl;
		}
		if(boolcount==1)
		{
			int k=0;
			for(k;k<num_verts;k++)
				if(vert_set[i]->neighbors[k]==0) break;
			vert_set[k]->set(i,1);
			vert_set[i]->set(k,1);
			cout <<"1) Contracting vertex "<< k+1 << " and vertex " << i+1 <<endl;
		}
	}
}

