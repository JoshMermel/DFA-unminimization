//
//  tree.h
//  
//
//  Created by Michael James on 7/4/12.
//  Copyright 2012 Tufts University. All rights reserved.
//

#ifndef tree_h
#define tree_h

#include "circ_list.h"
#include <vector>

class TreeNode
{
public:
    TreeNode();
    TreeNode(Tree t);
    add(circ_list* list);
    remove(circ_list* list);
    graft(circ_list* list);
    prune(circ_list* list);
    ~treeNode();
    
    vector<circ_list*> children;
    
private:
}


#endif
