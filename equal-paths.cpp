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
  // Leaf Case Checker if Left and Right are Not Equal
  if (root->left != nullptr && root->right != nullptr){
    // Check if left subtree are equal
    if(treeSearch(root->left, leftSide) == false){
      return false;
    }
    // Check if right subtree are equal
    if (treeSearch(root->right, rightSide) == false){
      return false;
    }
    // Check if leaves on both sides are equal
    if (leftSide != rightSide){
      return false;
    }
    leaf = leftSide + 1;
    return true;
  }
  // Left Leaf Exists but not right
  if (root->left != nullptr){
    if (treeSearch(root->left, leftSide) == false){
      return false;
    }
    leaf = leftSide + 1;
  }
  // Right Leaf Exists but not left
  if (treeSearch(root->right, rightSide) == false){
    return false;
  }
  leaf = rightSide + 1;
  return true;
}


bool equalPaths(Node * root)
{
    // Add your code below
    int leafNodes = 0;
    return treeSearch(root, leafNodes);
}

