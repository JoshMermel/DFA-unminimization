//
// Argument Bottle by Michael James
// created 7/6/12
// This is to be used with the recursion function in main.
// This will help with memory management and threading.
//

#ifndef ARGBOTTLE
#define ARGBOTTLE

#include <string>
#include "circ_list.h"
#include "vertex.h"

class Argbottle
{
	public:
	Circ_list* clist;
	Vertex** vset;
    string output;
	Argbottle();
	~Argbottle();
};

#endif
