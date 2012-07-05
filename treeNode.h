//
//  treeNode.h
//  
//
//  Created by Michael James on 7/4/12.
//  Copyright 2012 Tufts University. All rights reserved.
//

#ifndef tree_h
#define tree_h

#include "circ_list.h"
#include <vector>

using namespace std;

class treeNode
{
public:
    treeNode(Circ_list* list);
    //PRECONDITION: none
    //POSTCONDITION: One node is made with the list as its data.
    //NOTE: This should be the root and should only be called once.
    
    treeNode(treeNode* t);
    //PRECONDITION: t must be valid 
    //POSTCONDITION: This will be used as a copy constructor
    
    void addChild(treeNode* t);
    //PRECONDITION: none
    //POSTCONDITION:
    
    treeNode* removeChild(treeNode* t);
    //PRECONDITION: treeNode must have at least one child
    //POSTCONDITION: returns the removed child
    
    ~treeNode();
    //PRECONDITION: 
    //POSTCONDITION:
    
    vector<Circ_list*> children;
    treeNode* parent;
    
private:
};


#endif
