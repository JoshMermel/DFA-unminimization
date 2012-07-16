#include "circ_list.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <csignal>
#include "main_helper.cpp"

using namespace std;

void graphContract(Vertex** vert_set, int num_verts);
void signalHandler(int signum);
bool recurser(Circ_list* clist, Vertex** vset, int num_vertices, int level);

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
        exit(-2);
	}
	// determine how many vertices there are
	int num_vertices;
	myfile >> num_vertices;
	cout << num_vertices << endl;
	// purges a newline from the stream
	// THERE IS A PROBLEM HERE, IT WORKS FOR K_5 
	// BUT REQUIRES ANOTHER PURGE FOR GOLDNER
	//myfile.get();
	char temp;
	string temp_string;

	getline(myfile,temp_string);

	// create an array to store them
	Vertex** vert_set = new Vertex*[num_vertices];
	// read them into that array
		
	// for each vertex
	for(int i = 0; i < num_vertices; i++)
	{
		// create an object to hold the data
		vert_set[i] = new Vertex(i, num_vertices);
		// read until you see a newline
		// this is a garbage value to be rewritten by the following loop
		temp = 'b';
		while(temp!='\n')
		{
			temp_string = "";
			temp = myfile.get();
			//read until you see a space
			while(temp!=' ' && temp!= '\n')
			{
				//concatonate newly read chars onto temp_string
				temp_string += temp;
				temp = myfile.get();
			}
		// set the vertex to know that it needs what was just found
		vert_set[i]->set(atoi(temp_string.c_str())-1, 0);
		}
	}
	graphContract(vert_set, num_vertices);
	myfile.close();

	// declare the circular doubly linked list->and put the vertex whose index
	// is the same as the enviromental variable first into it to start it
	
	Circ_list* my_list = new Circ_list(vert_set[atoi(argv[1])-1]);

    if(recurser(my_list, vert_set, num_vertices, 0))
    {
        cout << "Fruit smoothie time\n";
    }
    else
	    cout << "The tree yielded no fruits\n";
    delete my_list;
    for(int i=0; i<num_vertices; i++)
        delete vert_set[i];
    delete [] vert_set;
	exit(0);
}

bool recurser(Circ_list* clist, Vertex** vert_set, int num_vertices, int level)
{
    // limit to n^2 levels
    if(level>num_vertices*num_vertices)
    {
        cout << "INCONCEIVABLE!\n";
        return false;
    }

    vector<int> myvector;
    for(int i=0; i < num_vertices; i++)
        if(clist->start->vert->needs(i))
            myvector.push_back(i);
    
    vector< vector<int> > permutations = permute(myvector);
    int psize = permutations.size();

    for(int i = 0; i < psize ;i++)
    {
        Circ_list* list = new Circ_list(clist);
        Vertex** vset = new Vertex*[num_vertices];
        for(int j=0; j < num_vertices; j++)
            vset[j] = new Vertex(vert_set[j]);

        list->check_forward();
        list->print_list(list->start);
        list->check_backward();
        list->print_list(list->start);
        if(list->is_done())
        {
            cout << "(^_^)\n";
            return true;
        }
        list->have_children(vset, permutations[i]);
        list->print_list(list->start);
        
        cout << "recurse\n";
        bool tmp = recurser(list, vset, num_vertices, level+1); //loop
        delete list;
        for(int j=0; j<num_vertices; j++)
            delete vset[j];
        delete [] vset;
        if(tmp)
            return true;
    }
    return false;
}

void signalHandler(int signum)
{
	cout << "CAUGHT INTERRUPT [" << signum << "], QUITTING..." << endl;
/*	for(int i=0;i<num_vertices;i++)
	{
		delete vert_set[i];	
	}
	delete [] vert_set;
	clist->ptr->~Circ_list();*/
	exit(signum);
}  
	    
