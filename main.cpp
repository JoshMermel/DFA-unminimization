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
	char temp;
	string temp_string;
    // purge a remaining newline
	getline(myfile,temp_string);

    // handle kernel signals
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

	// create an array to store them
	Vertex** vert_set = new Vertex*[num_vertices];
    for(int i = 0; i < num_vertices; i++)
    {
		// create an object to hold the data
		vert_set[i] = new Vertex(i, num_vertices);
    }
	
    // for each vertex
	for(int i = 0; i < num_vertices; i++)
	{
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
				//concatenate newly read chars onto temp_string
				temp_string += temp;
				temp = myfile.get();
			}
		// set the vertex to know that it needs what was just found
		vert_set[i]->set(atoi(temp_string.c_str())-1, 0);
        vert_set[atoi(temp_string.c_str())-1]->set(i, 0);
		}
	}
	graphContract(vert_set, num_vertices);
	myfile.close();

	// declare the circular doubly linked list->and put the vertex whose index
	// is the same as the first argument into it to start it
	Circ_list* my_list = new Circ_list(vert_set[atoi(argv[1])-1]);
    // read the bound from the second argument
    int bound = atoi(argv[2]);
    // start recursing, if it all works, good.
    if(recurser(my_list, vert_set, num_vertices, 0, bound))
        cout << "Fruit smoothie time\n";
    else
	    cout << "The tree yielded nothing\n";
    delete my_list;
    for(int i=0; i<num_vertices; i++)
        delete vert_set[i];
    delete [] vert_set;
	return 0;
}

bool recurser(Circ_list* clist, Vertex** vert_set, int num_vertices, int level, int bound)
{
    // if any vertex is used more than bound times then reject.
    if(clist->check_any_greater_than(bound))
    {
        cout << "INCONCEIVABLE: " << level << "!\n\n";
        return false;
    }

    // create the list of permutations of the vertices that clist->start needs
    vector<int> myvector;
    for(int i=0; i < num_vertices; i++)
        if(clist->start->vert->needs(i))
            myvector.push_back(i);
    vector< vector<int> > permutations = permute(myvector);
    int psize = permutations.size();

    // for each permutation...
    for(int i = 0; i < psize ;i++)
    {
        // make copies of each instance variable
        Circ_list* list = new Circ_list(clist);
        Vertex** vset = new Vertex*[num_vertices];
        for(int j=0; j < num_vertices; j++)
            vset[j] = new Vertex(vert_set[j]);

        // run the algorithm on the newly copied variables
        // for the current permutation
		list->have_children(vset, permutations[i]);
        list->print_list(list->start);
        list->check_forward();
        list->print_list(list->start);
        list->check_backward();
        list->print_list(list->start);
        if(list->is_done())
        {
            cout << "(^_^)\n" ;
            // clean up the copied instance variables
            delete list;
            for(int j=0; j<num_vertices; j++)
                delete vset[j];
            delete [] vset;
            return true;
        }
        bool tmp = recurser(list, vset, num_vertices, level+1, bound); //loop
        // clean up the copied instance variables, and get ready to try again.
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
	    
