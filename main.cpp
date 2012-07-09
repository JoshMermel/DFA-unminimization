#include <iostream>
#include <fstream>
#include <csignal>
#include <pthread.h>
#include <stdlib.h>
#include <vector>
#include "permute.cpp"
#include "circ_list.h"
#include "argbottle.h"

using namespace std;

void graphContract(Vertex** vert_set, int num_verts);
void* recurser(void* b);
void signalHandler(int signum);

//Global variables so that signalHandler can do its work right.
int num_vertices;
Vertex** vert_set;
Circ_list* clist_ptr;
bool found = false;
pthread_mutex_t mutex_var = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_var = PTHREAD_COND_INITIALIZER;

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
	signal(SIGINT, signalHandler);
	signal(SIGTERM, signalHandler);

	ifstream myfile(argv[2]);
	if(!myfile.is_open())
	{
		cout << "BAD FILENAME, HAVE SOME CAKE\n";
	}
	// determine how many vertices there are
	myfile >> num_vertices;
	// purges a newline from the stream
	myfile.get();

	// create an array to store them
	vert_set = new Vertex*[num_vertices];
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
		while(temp!='\n')
		{
			temp_string = "";
			temp = myfile.get();
			//r read until you see a space
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

	// declare the circular doubly linked list and put the vertex whose index
	// is the same as the enviromental variable first into it to start it

	clist_ptr = new Circ_list(vert_set[atoi(argv[1])-1]);

	clist_ptr->print_list(clist_ptr->start);


	/*while(!my_list.is_done())
	  {

	// check forward and backward of the vertex to see if it want to
	// connect to the nearest non-saturated neighber and vice versa
	my_list.print_list(my_list.start);
	my_list.check_forward();
	my_list.print_list(my_list.start);
	my_list.check_backward();			
	// now look at what it is missing and create those nodes
	my_list.print_list(my_list.start);
	//perm = permute(vert_set);
	my_list.have_children(vert_set, perm);
	}*/
    
	//pthread_t recurse;
	Argbottle *bottle = new Argbottle();
	bottle->clist = clist_ptr;
	bottle->vset = new Vertex*[num_vertices];
	for(int i = 0; i < num_vertices; i++)
	{
		bottle->vset[i] = new Vertex(vert_set[i]);
	}
	//pthread_create(&recurse, NULL, recurser, (void*)bottle);
	//pthread_join(recurse, NULL);
	recurser((void*)bottle);

	//delete some dynamically allocated memory
	//unfinished?
	cout << "I win!\n";
	for(int i=0;i<num_vertices;i++)
	{
		delete vert_set[i];	
	}
	delete [] vert_set;
	delete clist_ptr;
	delete bottle;
	return 0;

	cout << "flow got to the end of main - past the while loop\n";
	exit(1);
}
// conract the graph so that there are no dangling nodes and so the graph is
// as simple as possible.  Thus there should be no tails no nodes with degree
// two or less.  This does not affect the math as these nodes could be trvially
// added back in after the algrorithm's expansion
void graphContract(Vertex** vert_set, int num_verts)
{
	for(int i=0; i<num_verts; i++)
	{
		int degreecount=0;
		for(int j=0;j<num_verts;j++)
		{
			if(vert_set[i]->neighbors[j]==0)
				degreecount++;
		}
		if(degreecount==2)
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
			cout << "2) Contracting and connecting vertex " << vprev+1 <<
					", vertex " << i+1 << ", and vertex " 
					<< vnext+1 << endl;
		}
		if(degreecount==1)
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
// The idea is that recurser will spawn off copies of itself with different
// permutations of possible orderings to try.  A wining branch will return 
// true and collapse everything.  Note that we are not dealing with pointers
// this is so that when the program forks, each fork will have its own memory.
// PRECONDITION: bottle is already setup and this function is called as a thread.
// POSTCONDITION: many many copies of the circ_list will exist in memory
void* recurser(void* b)
{
	((Argbottle*)b)->clist->print_list(((Argbottle*)b)->clist->start);
    	if(found)
    	{
        	//delete ((Argbottle*)b)->clist;
		cout << "I WAS KILLED BY BREAD.\n";
        	pthread_exit(0);
    	}
	if(((Argbottle *)b)->clist->is_done())
	{
		found = true;
		//delete ((Argbottle*)b)->clist;
		cout << "I FOUND AZTEC GOLD\n";
		pthread_cond_signal(&condition_var);
        	return (void*) b;
	}
	// This should be the list of vertexs that clists's start vertex needs,
	// in lexigraphic order.
	vector<int> myvector;
	for(int k = 0; k < ((Argbottle*)b)->clist->start->vert->neighbors.size(); k++)
	{
		// check if it needs a vertex
		if(((Argbottle*)b)->clist->start->vert->is_needed(k))
		{
			myvector.push_back(k);
		}
	}
    	// this is where the permuter goes.  The logic should go:
    	// for each permutation have children as a different thread.
	vector< vector<int> > permutations = permute(myvector);
	cout << "permutations done\nThere are " << permutations.size() << " permutations.\n";
     	pthread_t fork1[permutations.size()];
	for(int i=0; i < permutations.size(); i++)
	{
     		if(found) {cout << "OH LOOK, A PUPPY\n";pthread_exit(0);}
		//make the copies
     		Argbottle* bottle = new Argbottle();
     		bottle->clist = new Circ_list(((Argbottle *)b)->clist);
		bottle->vset = new Vertex*[num_vertices];
		for(int j = 0; j < num_vertices; j++)
		{
			bottle->vset[j] = new Vertex(((Argbottle*) b)->vset[j]);
		}
     		//run the checks
     		bottle->clist->check_forward();
     		bottle->clist->check_backward();
     		bottle->clist = bottle->clist->have_children(bottle->vset, permutations[i]);
		//cout << "forking\n" << endl;
     		pthread_create(&fork1[i],NULL,recurser, bottle);	
	}
	// The program must wait.
	pthread_cond_wait(&condition_var, &mutex_var);
	cout << "I WAS A GOOD LITTLE THREAD\n";
	pthread_exit(0);
}

void signalHandler(int signum)
{
	cout << "CAUGHT INTERRUPT [" << signum << "], QUITTING..." << endl;
	for(int i=0;i<num_vertices;i++)
	{
		delete vert_set[i];	
	}
	delete [] vert_set;
	clist_ptr->~Circ_list();
	exit(signum);
}
