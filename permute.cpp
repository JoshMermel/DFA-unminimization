#include <iostream>
#include <vector>
using namespace std;
// this is an implemention of the Johnson Trotter algorithm
const int arraysize = 0;

struct int_bool 
{
	int num;
	bool left;
};

bool is_done(int_bool data[], int arraysize);
bool is_mobile(int_bool data[], int index, int arraysize);
int get_biggest_mobile_index(int_bool data[], int arraysize);
void swap(int_bool data[], int index, int arraysize);
void reverse(int_bool data[], int val, int arraysize);
vector<vector<int> > permute(vector<int> ordered);

vector<vector<int> > permute(vector<int> ordered)
{
	
	int_bool data[ordered.size()];
	for(int i = 0; i < arraysize; i++)
	{
		data[i].num = i;
		data[i].left = true;
	}
	int to_swap;
	int val;
	vector<int> vect;
	vector<vector<int> > permutations;
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
		for(int i = 0; i < arraysize; i++)
		{
			vect.push_back(i);
		}
		permutations.push_back(vect);
	}
	
	return permutations;
}

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

bool is_mobile(int_bool data[], int index, int arraysize)
{
	if(index == 0 && data[index].left)
	{
		return false;
	}
	if(index == arraysize-1 && !data[index].left)
	{
		return false;
	}
	if(data[index].left && data[index].num < data[index-1].num)
	{
		return false;
	}
	if(!data[index].left && data[index].num < data[index+1].num)
	{
		return false;
	}
	return true;
}

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
