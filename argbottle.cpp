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
}
