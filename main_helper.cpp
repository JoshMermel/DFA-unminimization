#include <iostream>
#include <vector>
#include "vertex.h"

using namespace std;
// This is an implemention of the Johnson-Trotter algorithm written by Josh
// Mermelstein on 7/06/12

struct int_bool 
{
	int num;
	bool left;
	// this bool determines wheather the number is facing right or left
};

bool is_mobile(int_bool data[], int index, int arraysize)
{
	//return false if:
	//if the number is on the far left and is facing left
	if(index == 0 && data[index].left)
	{
		return false;
	}
	//or on the far right facing right
	if(index == arraysize-1 && !data[index].left)
	{
		return false;
	}
	//or facing left but smaller than its left neighbor
	if(data[index].left && data[index].num < data[index-1].num)
	{
		return false;
	}
	//or facing right but smaller than its right neighbor
	if(!data[index].left && data[index].num < data[index+1].num)
	{
		return false;
	}
	//if none of those things happened, return true.
	return true;
}

//the program ends when there are no "mobile" numbers.  This function checks
//for mobile numbers and returns true only if it finds them.
bool is_done(int_bool data[], int arraysize)
{
	for(int i = 0; i < arraysize; i++)
	{
		if(is_mobile(data, i, arraysize))
		{
			return false;
		}
	}
	return true;
}

// this implements a step of the algorithm which is to reverse the direction of
// a given number if it is bigger than the one that just switched.
void reverse(int_bool data[], int val, int arraysize)
{
	for(int i = 0; i < arraysize; i++)
	{
		if(data[i].num > val)
		{
			data[i].left = !data[i].left;
		}
	}
}

// swaps a vertex with the one it is pointing at.
// can cause seg-faults if used incorrectly (eg, if called on index 0 when
// index 0 is facing to the left)
void swap(int_bool data[], int index, int arraysize)
{
	if(data[index].left)
	{
		int_bool temp = data[index];
		data[index] = data[index-1];
		data[index-1] = temp;
	}
	else
	{
		int_bool temp = data[index];
		data[index] = data[index+1];
		data[index+1] = temp;
	}
}

// does precisely what the name suggests it will do.
int get_biggest_mobile_index(int_bool data[], int arraysize)
{
	int temp;
	for(int i = 0; i < arraysize; i++)
	{
		if(is_mobile(data, i, arraysize))
		{
			temp = i;
			break;
		}
	}
	for(int i = 0; i < arraysize; i++)
	{
		if(is_mobile(data, i, arraysize) && data[i].num > data[temp].num)
			temp = i;
	}

	return temp;
}

//this function is the crux of this set.  it reads in data from a vector and
//returns a vector of vectors listing every permutation of the numbers in the
//one that was passed it.  It requires the vector that was passed to it to be
//sorted.
vector<vector<int> > permute(vector<int> ordered)
{
	// read in data from ordered
	int_bool data[ordered.size()];
	for(int i = 0; i < ordered.size(); i++)
	{
		data[i].num = ordered[i];
		data[i].left = true;
	}
	//declare some temp variables
	int to_swap;
	int val;
	vector<int> vect;
	vector<vector<int> > permutations;
    // Without this step, the originally ordered list is omitted
    permutations.push_back(ordered);
	//while there exists a mobile integer
	while(!is_done(data, ordered.size()))
	{
  		//find the largest mobile integer k
		to_swap = get_biggest_mobile_index(data, ordered.size());
		val = data[to_swap].num;
  		//swap k and the adjacent integer it is looking at
		swap(data, to_swap, ordered.size());
  		//reverse the direction of all integers larger than k
		reverse(data, val, ordered.size());
		for(int i = 0; i < ordered.size(); i++)
		{
			// put the permutation in a temporary vector
			vect.push_back(data[i].num);
		}
		permutations.push_back(vect);
		vect.clear();
	}
	
	return permutations;
}

// contract the graph so that there are no dangling nodes and so the graph is as
// simple as possible.  Thus there should be no tails no nodes with degree two
// or less.  This does not affect the math as these nodes could be trvially
// added back in after the algrorithm's expansion
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

