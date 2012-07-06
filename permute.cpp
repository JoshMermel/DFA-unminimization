#include <iostream>
using namespace std;
// this is an implemention of the Johnson Trotter algorithm
const int arraysize = 0;

struct bloop 
{
	int num;
	bool left;
};

bool is_done(bloop data[]);
bool is_mobile(bloop data[], int index);
int get_biggest_mobile_index(bloop data[]);
void swap(bloop data[], int index);
void reverse(bloop data[], int val);
void printarray(bloop data[]);

int main()
{
	bloop data[arraysize];
	for(int i = 0; i < arraysize; i++)
	{
		data[i].num = i;
		data[i].left = true;
	}
	printarray(data);
	int to_swap;
	int val;
	vector<int> vect;
	vector<vector<int>> permutations;
	//while there exists a mobile integer
	while(!is_done(data))
	{
  		//find the largest mobile integer k
		to_swap = get_biggest_mobile_index(data);
		val = data[to_swap].num;
  		//swap k and the adjacent integer it is looking at
		swap(data, to_swap);
  		//reverse the direction of all integers larger than k
		reverse(data, val);
		printarray(data);
		for(int i = 0; i < arraysize; i++)
		{
			vect.push_back(i);
		}
		permutations.push_back(vect);
	}
	
	return 0;
}

void reverse(bloop data[], int val)
{
	for(int i = 0; i < arraysize; i++)
	{
		if(data[i].num > val)
		{
			data[i].left = !data[i].left;
		}
	}
}

void swap(bloop data[], int index)
{
	if(data[index].left)
	{
		bloop temp = data[index];
		data[index] = data[index-1];
		data[index-1] = temp;
	}
	else
	{
		bloop temp = data[index];
		data[index] = data[index+1];
		data[index+1] = temp;
	}
}

bool is_mobile(bloop data[], int index)
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

bool is_done(bloop data[])
{
	for(int i = 0; i < arraysize; i++)
	{
		if(is_mobile(data, i))
		{
			return false;
		}
	}
	cout << "done!\n";
	return true;
}

int get_biggest_mobile_index(bloop data[])
{
	int temp;
	for(int i = 0; i < arraysize; i++)
	{
		if(is_mobile(data, i))
		{
			temp = i;
			break;
		}
	}
	for(int i = 0; i < arraysize; i++)
	{
		if(is_mobile(data, i) && data[i].num > data[temp].num)
			temp = i;
	}

	return temp;
}

void printarray(bloop data[])
{
	for(int i = 0; i < arraysize; i++)
	{
		cout << data[i].num+1 << ' ';
	}
	cout << endl;
}
