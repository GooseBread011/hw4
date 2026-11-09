#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
bool treeSearch (Node* root, int& leafpath)
{
  if (root == nullptr){
    leafpath = 0;
    return true;
  }
  bool leftdir = root->left;
  bool rightdir = root->right;

}


bool equalPaths(Node * root)
{
    // Add your code below
    int leafpath = 0;
    treeSearch(root, leafpath);
    
}

