#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <iostream>
#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
bool treeSearch (Node* root, int& leaf)
{
  // Empty Tree
  if (root == nullptr){
    leaf = 0;
    return true;
  }
  // No Children Checker
  if (root->left == nullptr && root->right == nullptr){
    leaf = 0;
    return true;
  }

  // Path Direction Variables
  int leftSide = 0;
  int rightSide = 0;

  // Search the left and right trees 
  if (root->left != nullptr && root->right != nullptr){
    // Check the left side
    if (treeSearch(root->left, leftSide) == false){
      return false;
    }
    if (treeSearch(root->right, rightSide) == false){
      return false;
    }
    // If left side != right side
    if (leftSide != rightSide){
      return false;
    }

}


bool equalPaths(Node * root)
{
    // Add your code below
    int leafNodes = 0;
    return treeSearch(root, leafNodes);
    
}

