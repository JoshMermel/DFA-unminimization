#include "circ_list.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <csignal>
#include "main_helper.cpp"

using namespace std;

void graphContract(Vertex** vert_set, int num_verts);
void signalHandler(int signum);
bool recurser(Circ_list* clist, Vertex** vset, int num_vertices, int level, int bound);

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		cout << "The program takes in 3 parameters: the start vertex number, ";
		cout << "the bound (no vertex will be less than this when it stops a ";
        cout << "recursion), then the location of the graph file. The 1st ";
        cout << "vertex is number 1. Do not be confused that under the hood";
        cout << "we start with 0\n";
		return -1;
	}

	ifstream myfile(argv[3]);
	if(!myfile.is_open())
	{
		cout << "BAD FILENAME, HAVE SOME CAKE\n";
        return -2;
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
    int bound = atoi(argv[2]);
    if(recurser(my_list, vert_set, num_vertices, 0, bound))
    {
        cout << "Fruit smoothie time\n";
    }
    else
	    cout << "The tree yielded no fruits\n";
    delete my_list;
    for(int i=0; i<num_vertices; i++)
        delete vert_set[i];
    delete [] vert_set;
	return 0;
}

bool recurser(Circ_list* clist, Vertex** vert_set, int num_vertices, int level, int bound)
{
    // limit to n^2 levels
    if(clist->check_any_greater_than(bound))
    {
        cout << "INCONCEIVABLE: " << level << "!\n";
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
        bool tmp = false;
        Circ_list* list = new Circ_list(clist);
        Vertex** vset = new Vertex*[num_vertices];
        for(int j=0; j < num_vertices; j++)
            vset[j] = new Vertex(vert_set[j]);

		list->have_children(vset, permutations[i]);
        list->print_list(list->start);
        list->check_forward();
        list->print_list(list->start);
        list->check_backward();
        list->print_list(list->start);
        if(list->is_done())
        {
            cout << "(^_^)\n" ;
            delete list;
            for(int j=0; j<num_vertices; j++)
                delete vset[j];
            delete [] vset;
            return true;
        }
        tmp = recurser(list, vset, num_vertices, level+1, bound); //loop
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
	    
