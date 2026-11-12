#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <iostream>
#endif

#include "equal-paths.h"
using namespace std;

bool treeSearch(Node* root, int& leaf);

// You may add any prototypes of helper functions here
bool treeSearch (Node* root, int& leaf)
{
  int leftSide = 0;
  int rightSide = 0;
  // Empty Tree
  if (root == nullptr){
    leaf = 0;
    return true;
  }
  // Both Left and Right subtree has no children left
  if(root->left == nullptr && root->right == nullptr){
    leaf = 0;
    return true;
  }
  // Leaf Checker
  if (root->left != nullptr && root->right != nullptr){
    if(treeSearch(root->left, leftSide) == false){
      return false;
    }
    if (treeSearch(root->right, rightSide) == false){
      return false;
    }
    if (leftSide != rightSide){
      return false
    }
    leaf = leftSide + 1;
    return true;
  }
}


bool equalPaths(Node * root)
{
    // Add your code below
    int leafNodes = 0;
    return treeSearch(root, leafNodes);
}

