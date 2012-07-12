#include "argbottle.h"

Argbottle::Argbottle()
{
	clist=NULL;
	vset=NULL;
    output="";
}

Argbottle::~Argbottle()
{
    if(clist!=NULL)
        delete clist;
	if(vset!=NULL)
	{
		for(int i=0; i < vset[0]->size; i++)
			delete vset[i];
		delete [] vset;
	}
}
