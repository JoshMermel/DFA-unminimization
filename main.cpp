#include "circ_list.h"
#include <iostream>
#include <fstream>
#include <csignal>

#define FIRST 9
using namespace std;

void graphContract(Vertex** vert_set, int num_verts);
bool recurser(Circ_list* list, Vertex** vert_set);
void signalHandler(int signum);
vector<int> permute(Vertex** vert_set);

//Global variables so that signalHandler can do its work right.
int num_vertices;
Vertex** vert_set;
Circ_list* clist_ptr;

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		cout << "This program takes in 2 parameters: the start vertex number ";
		cout << "and then the location of the graph file.  The 1st vertex is ";
		cout << "number 1.  Do not be confused that under the hood we start ";
		cout << "with 0\n";
	}
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    ifstream myfile(argv[2]);
    cout << argv[2] << endl;
    if(myfile.is_open())
    {
            // determine how many vertices there are
            
            string line;
            getline(myfile,line);
            num_vertices=atoi(line.c_str());
            // purges a newline from the stream
            //cin.get();

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
                // The range is adjusted so that the last number is excluded.
                for (int j = 1; j < num_vertices-1; j++) 
                {
                    getline(myfile, temp_string, ' ');
                    vert_set[i]->set(atoi(temp_string.c_str())-1,0);
                    temp_string="";
                }
                // This must be done so that getline can take the last char in
				//the line.  It is delineated with a \n, so getline must be
				//able to handle that
                getline(myfile, temp_string);
                vert_set[i]->set(atoi(temp_string.c_str())-1,0);
                temp_string="";
			
            
        }
	graphContract(vert_set, num_vertices);
    myfile.close();
    }
    else
    {
        cout << "BAD FILENAME.  HAVE A NICE DAY AND SOME CAKE." << endl;
        exit(-2);
    }


	// declare the circular doubly linked list and put the vertex whose index
	// is the same as the enviromental variable first into it to start it
	
	Circ_list my_list(vert_set[atoi(argv[1])-1]);
    	clist_ptr=&my_list;

	my_list.print_list(my_list.start);

	vector<int> perm;

	while(!my_list.is_done())
	{
		
		// check forward and backward of the vertex to see if it want to
		// connect to the nearest non-saturated neighber and vice versa
		my_list.print_list(my_list.start);
		my_list.check_forward();
		my_list.print_list(my_list.start);
		my_list.check_backward();			
		// now look at what it is missing and create those nodes
		my_list.print_list(my_list.start);
		perm = permute(vert_set);
		my_list.have_children(vert_set, perm);
	}
	//delete some dynamically allocated memory
	cout << "I win!\n";
	for(int i=0;i<num_vertices;i++)
	{
		delete vert_set[i];	
	}
	delete [] vert_set;
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
					", vertex " << i+1 << ", and vertex " << vnext+1 << endl;
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
// true and collapse everything.
bool recurser(Circ_list* list, Vertex** vert_set)
{
	
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

vector<int> permute(Vertex** vert_set)
{
	
}
