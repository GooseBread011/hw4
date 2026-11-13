#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    int height( AVLNode<Key, Value>* n) const;
    void rbalance( AVLNode<Key, Value>* n);
    void rleft( AVLNode<Key, Value>* n);
    void rright( AVLNode<Key,Value>* n);


};
// Helper to determine height of tree
template <class Key, class Value>
int AVLTree< Key, Value>::height(AVLNode<Key, Value>* n)
{
  // Empty Tree Case
  if (n == NULL){
    return 0;
  }
  // Trees for left and right
  int leftTree = height(n->getLeft());
  int rightTree = height(n->getRight());

  // Check Left Tree Height
  if (leftTree > rightTree){
    return leftTree + 1;
  }
  // Else Check Right
  return rightTree + 1;
}

// Helper for Rotate Left
template <class Key, class Value>
void AVLTree<Key, Value>::rleft(AVLNode<Key, Value>* n)
{
  AVLNode<Key, Value>* parent = n->getParent();
  AVLNode<Key, Value>* tempR = n->getRight();
  AVLNode<Key, Value>* tempL = tempR->getLeft();
  // Change the Root and keep it the same
  if (parent == NULL){
    this->root_ = tempR;
  }
  else if (parent->getLeft() == n){
    parent->setLeft(tempR);
  }
  else {
    parent->setRight(tempR);
  }
  tempR->setParent(parent);
  // Rotate Left
  tempR->setLeft(n);
  n->setParent(tempR);
  n->setRight(tempL);
  if (tempL != NULL){
    tempL->setParent(n);
  }
}

// Helper for Rotate Right
template <class Key, class Value>
void AVLTree<Key, Value>::rright(AVLNode<Key, Value>* n)
{
  AVLNode<Key, Value>* parent = n->getParent();
  AVLNode<Key, Value>* tempL = n->getLeft();
  AVLNode<Key, Value>* tempR = tempL->getRight();
  // Change the Root and keep it the same
  if (parent == NULL){
    this->root_ = tempL;
  }
  else if (parent->getLeft() == n){
    parent->setLeft(tempL);
  }
  else {
    parent->setRight(tempL);
  }
  tempL->setParent(parent);
  // Rotate Right
  tempL->setRight(n);
  n->setParent(tempL);
  n->setLeft(tempR);
  if (tempR != NULL){
    tempR->setParent(n);
  }
}

// Helper to Rebalance tree
template<class Key, class Value>
void AVLTree<Key, Value>::rbalance(AVLNode<Key, Value>* n)
{
  // While the tree still has leaves
  while (n != NULL){
    // Balance Factor
    int balanceFactor = height(n->getRight()) - height(n->getLeft());
    
    // If Right Tree is Heavy
    if (balanceFactor > 1){
      AVLNode<Key, Value>* rheavy = n->getRight();
      // Rotate right
      if (height(rheavy->getLeft()) > height(rheavy->getRight())){
        rright(rheavy);
      }
      // Rotate Left balance
      rleft(n);
    }
    // Left Side is Heavy
    else if (balanceFactor < -1){
      AVLNode<Key, Value>* lHeavy = n->getLeft();
      if (height(lHeavy->getRight()) > height(lHeavy->getLeft())){
        rleft(lHeavy);
      } 
      rright(n);
    }
    // After Rotation
    if (balanceFactor < -1 || balanceFactor > 1){
      AVLNode<Key, Value>* tempRoot = n->getParent();
      n->setBalance(height(n->getRight()) - height(n->getLeft()));
      tempRoot->setBalance(height(tempRoot->getRight()) - height(tempRoot->getLeft()));
      n = tempRoot->getParent();
    }
    // No rotation needed
    else {
      n->setBalance(balanceFactor);
      n = n->getParent();
    }
  }
}


/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    // Empty Tree
    if (this->root_ == NULL){
      this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
      return;
    }
    // Loop through tree
    while(true){
      if(new_item.first < curr->getKey()){
        // Insert Node into left if Null
        if (curr->getLeft() == NULL){
          curr->setLeft(new AVLNode<Key, Value>(new_item.first, new_item.second, curr));
          return;
        }
        curr = curr->getLeft();
      }
      else if (curr->getKey() < new_item.first){
        // Insert Node into Right if NULL
        if(curr->getRight() == NULL){
          curr->setRight(new AVLNode<Key, Value>(new_item.first, new_item.second, curr));
          return;
        }
        curr = curr->getRight();
      }
      else {
        // Overwrite current value
        curr->setValue(new_item.second);
        return;
      }
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    Node<Key, Value>* n = internalFind(key);
    // Empty Tree, No Node
    if (n == NULL){
      return;
    }
    // Swap with predecessor
    if (n->getLeft() != NULL && n->getRight() != NULL){
      nodeSwap(n, predecessor(n));
    }
    Node<Key, Value>* child = NULL;
    Node<Key,Value>* parent = n->getParent();
    //Update Child
    if (n->getLeft() != NULL){
      child = n->getLeft();
    }
    else {
      child = n->getRight();
    }
    // Set New Parent
    if (child != NULL){
      child->setParent(parent);
    }
    // Update root and Parent if needed
    if (parent == NULL){
      root_ = child;
    }
    else if (parent->getLeft() == n){
      parent->setLeft(child);
    }
    else {
      parent->setRight(child);
    }
    delete n;
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
