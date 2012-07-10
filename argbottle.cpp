#include "argbottle.h"

Argbottle::Argbottle()
{
	clist=NULL;
	vset=NULL;
}

Argbottle::~Argbottle()
{
    	if(clist!=NULL)
    		delete clist;
	if(vset!=NULL)
	{
		for(int i=0; i < vset[0]->neighbors.size(); i++)
			delete vset[i];
		delete [] vset;
	}
}
