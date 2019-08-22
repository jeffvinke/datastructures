/****************************************************************
   PROGRAM:   Assignment 2
   AUTHOR:    Jeff Vinke
   CLASS:     CSCI 440, Section 1

   FUNCTION:  This program impliments a binary tree

   INPUT:     whatever is specified by driver program

   OUTPUT:    whatever is specified by driver program
****************************************************************/
#ifndef __BINTREE_H_
#define __BINTREE_H_

#include <iostream>
#include <iomanip>
#include "bintnode.h"
#include <string>
#include <queue>
using std::cin;
using std::cout;
using std::endl;
using std::setw;
using std::string;
using std::queue;

template <class T> class binTree {
   public:
      binTree() { root = NULL; }                           // default constructor 
      bool empty() const;                                  // checks if tree is empty
      int size() const;                                    // finds # of nodes
      int height() const;                                  // finds the height
      int leaves() const;                                  // finds the number of leaves
      int width() const;                                   // finds the width of the tree

      void insert1(const T& val);                          // inserts node in shortest subtree
      void insert2(const T& val);                          // inserts node in bin search tree
      void clear();                                        // destroys tree

      
      // tree traversal functions
      void inOrder(void (*)(T&));                          // inorder traversal
      void preOrder(void (*)(T&));                         // preorder traversal
      void postOrder(void (*)(T&));                        // postorder traversal
      void levelOrder(void (*)(T&));                       // level by level traversal

      binTree(const binTree<T>&);                          // copy constructor
      binTree& operator=(const binTree<T>&)  ;             // assignment operator
      ~binTree();                                          //destructor

   protected:
      binTNode<T>* root;                                   //root of tree

   private:
      // tree maintenance
      void r_insert(binTNode<T> *&p, const T& val);        // insert 1 helper
      void r_insert2(binTNode<T> *&p, const T& val);       // insert 2 helper
      void destroyTree(binTNode<T>* p);                    // destroy tree
      void r_copy(binTNode<T>*& copy, binTNode<T>* other);
      
      // tree orders
      void r_inorder(void (*f)(T&), binTNode<T>* p);       // inorder helper
      void r_preorder(void (*f)(T&), binTNode<T>* p);      // preorder helper
      void r_postorder(void (*f)(T&), binTNode<T>* p);     // postorder helper
      void level(void (*f)(T&), binTNode<T>* p);           // level order helper

      // tree characteristics
      int r_max(binTNode<T>* p) const;                     // max height helper
      int r_size(binTNode<T>* p) const;                    // returns number of nodes
      int r_leaves(binTNode<T>* p) const;                  // returns leaf number

};

      
//FUNCTION:  Constructor for binary tree
//ARGUMENTS: A tree to copy
//RETURN:    Nothing
//NOTES:     None
template <class T>
binTree<T>::binTree(const binTree<T>& other) { 
   if (other.root == NULL)                                 // if tree is null
      root = NULL;                                         // copyied tree is null
   else
      r_copy(root, other.root);                            // copy the tree
}

//FUNCTION:  r_copy
//ARGUMENTS: tree to be copied and new tree
//RETURN:    nothing
//NOTES:     creates a copy of a teww
template <class T>
void binTree<T>::r_copy(binTNode<T>*& copy, binTNode<T>* other) {
   if (other == NULL)                                      // if tree is null then
      copy = NULL;                                         // set other tree to null
   else {                                                  // otherwise
      copy = new binTNode<T>;                              // create new node
      copy->value = other->value;                          // copy value
      r_copy(copy->left, other->left);                     // copy left
      r_copy(copy->right, other->right);                   // copy right
   }
}


//FUNCTION:  Assignment operator
//ARGUMENTS: Tree to be copied
//RETURN:    *this
//NOTES:     The assignment operator is overloaded to allow for entire
//           trees to be copied
template <class T>     
binTree<T>& binTree<T>::operator=(const binTree<T>& other) {
   if (this != &other) {                                   // if this tree is unique
      if (root != NULL)
      destroyTree(root);                                   // clear other tree
      
      if (other.root == NULL)                              // if other tree is null
         root = NULL;                                      // this is null
      else 
         r_copy(root, other.root);                         // copy tree
   }
   return *this;
}


//FUNCTION:  destroyTree
//ARGUMENTS: a pointer to a node
//RETURN:    nothing
//NOTES:     this starts with a node and destroys all subnodes
template <class T>
void binTree<T>::destroyTree(binTNode<T> *p) {
   if (p == NULL)                                          // if tree is null, return
      return; 
   
      destroyTree(p->left);                                // destroy left
      destroyTree(p->right);                               // destroy right
      p->left = p->right = NULL;                           // set left and right ptrs to null
      delete p;                                            // delete node
      p = NULL;
}


//FUNCTION:  destructor
//ARGUMENTS: none
//RETURN:    nothing
//NOTES:     calls celar to destroy the tree
template <class T>
binTree<T>::~binTree() {
   clear();                                                // destroys tree
}


//FUNCTION:  empty
//ARGUMENTS: none
//RETURN:    true or false
//NOTES:     returns whether or not tree is empty
template <class T>
bool binTree<T>::empty() const { 
   return (root == NULL);                                  // root null? it's empty
}


//FUNCTION:  size
//ARGUMENTS: none 
//RETURN:    size of tree
//NOTES:     calls r_size to recursively calc size of tree
template <class T>
int binTree<T>::size() const { 
   return  r_size(root);                                   // return size of tree
}

//FUNCTION:  height
//ARGUMENTS: none
//RETURN:    0 or max height of tree
//NOTES:     recursively calculates the height
//           of a tree and then returns the max
template <class T>
int binTree<T>::height() const { 
   if (root != NULL) {
      int lmax = 0,                                        // right max var holder
          rmax = 0;                                        // left max var holder
      lmax = r_max(root->left);                            // get left max
      rmax = r_max(root->right);                           // get right max
      if (rmax > lmax) return rmax + 1;                    // return whichever path
      return lmax + 1;                                     // is longer
   }
   return 0;
}


//FUNCTION:  leaves
//ARGUMENTS: none
//RETURN:    true or false
//NOTES:     calls r_leaves to calc number of leaves 
//           then returns it
template <class T>
int binTree<T>::leaves() const { 
   return r_leaves(root);                                  // return leave count
}

//FUNCTION:  width
//ARGUMENTS: none
//RETURN:    width of tree
//NOTES:     returns the width of the tree
template <class T>
int binTree<T>::width() const { 
    queue<binTNode<T>*> q1,q2;                             // queue for nodes
    binTNode<T>* p = root,*temp;                           // pointer to root and temp pointer
    int width=0, max=0;                                    // working and max width
    
    q1.push(p);                                            // push root on queue
    while (!q1.empty() ||  !q2.empty()) {
       while (!q1.empty()) {                               // while queue is not empty
          p = q1.front();                                  // p top item
          q1.pop();                                        // pop q1's top
          
          if (p != NULL) {                                 // while p is not null
             ++width;                                      //incriment width
             q2.push(p->left);                             // push left and right 
             q2.push(p->right);                            // on the queue
          }
       }
       
       while (!q2.empty()) {
          temp = q2.front();                               // temp -> top item in q2
          q2.pop();                                        // pop q2's top item
          q1.push(temp);                                   // q2's top item in q1
       }
       
       if (width > max)                                    // check to see if width > max
          max=width;                                       
       
       width=0;                                            // set for next level
    }
    return max;                                            // return width
}

//FUNCTION:  insert1
//ARGUMENTS: item to be inserted
//RETURN:    nothing
//NOTES:     calls r_insert1 to insert item
template <class T>
void binTree<T>::insert1(const T& item) { 
   r_insert(root, item);                                   // create root node
}


//FUNCTION:  r_insert1
//ARGUMENTS: pointer to node, value to be inserted
//RETURN:    nothing
//NOTES:     looks for the smalles subtree and inserts
//           the new node there
template <class T>
void binTree<T>::r_insert(binTNode<T> *&p, const T& val) {
   int lmax = 0, rmax = 0;                                 // left and right max vals
   if (p == NULL) {                                        // if null, create new node
      p = new binTNode<T>(val);                            // p points to new node
   }
   else {
      lmax = r_max(p->left);                               // get left max
      rmax = r_max(p->right);                              // get right max
      if (rmax < lmax)                                     // if right max > left max
         r_insert(p->right, val);                          // look for insertion spot in right path
      else                                                 // otherwise 
         r_insert(p->left, val);                           // insert it in the left path
   }
}


//FUNCTION:  insert2
//ARGUMENTS: item to be inserted
//RETURN:    Nothing
//NOTES:     calls r_insert2 to insert item
template <class T>
void binTree<T>::insert2(const T& item) { 
   r_insert2(root, item);                                  // have r_insert2 insert node
}

//FUNCTION:  r_insert2
//ARGUMENTS: pointer to node, value of item
//RETURN:    nothing
//NOTES:     inserts the node based upon value
//           less then goes left, greater right
template <class T>
void binTree<T>::r_insert2(binTNode<T> *&p, const T& val) {
   if (p == NULL) {                                        // if root is null
      p = new binTNode<T>(val);                            // create it
   }

   else { 
      if (val < p->value)                                  // if val is less then nodes value
         r_insert2(p->left, val);                          // insert left
      else                                                 // otherwise
         r_insert2(p->right, val);                         // insert right
   }
}

//FUNCTION:  clear
//ARGUMENTS: none
//RETURN:    nothing
//NOTES:     calls destroyTree to destroy the tree 
template <class T>
void binTree<T>::clear() { 
   destroyTree(root);                                      // destroys tree
   root = NULL;                                            // make sure root is null
}

//FUNCTION:  r_max
//ARGUMENTS: pointer to node
//RETURN:    height of tree
//NOTES:     recursively calcs height and retuns it
template <class T>
int binTree<T>::r_max(binTNode<T>* p) const {
   int r = 0, l = 0;                                       // right and left totals
   if (p == NULL)                                          // if tree null, return 0
      return 0;                                            
   else {                                                  // otherwise
      l = r_max(p->left);                                  // get left max
      r = r_max(p->right);                                 // get right max
      if (l > r) r = 0;                                    // if left > right, set right to zero
      else l = 0;                                          // otherwise set left to zero
   }
   
   return 1 + r + l;                                       // return the longest path + current node
}

//FUNCTION:  inOrder
//ARGUMENTS: a function pointer
//RETURN:    nothing
//NOTES:     call r_inorder print the tree inorder
template <class T>
void binTree<T>::inOrder(void (*f) (T&)) {
   r_inorder(f, root);                                     // have r_inorder print nodes inorder
}

//FUNCTION:  r_inorder
//ARGUMENTS: print function, pointer to node
//RETURN:    nothing
//NOTES:     prints the tree inorder
template <class T>
void binTree<T>::r_inorder(void (*f)(T&), binTNode<T>* p) {
   if (p != NULL) {                                        // if the tree is null, disregard
      r_inorder(f, p->left);                               // go to leftmost subnode
      f(p->value);                                         // print node value
      r_inorder(f, p->right);                              // go to rightmost subnode
   }
}

//FUNCTION:  levelorder
//ARGUMENTS: a function pointer
//RETURN:    nothing
//NOTES:     call r_level print the tree in level order
template <class T>
void binTree<T>::levelOrder(void (*f) (T&)) {
   level(f, root);                                       // print tree in level order
}

//FUNCTION:  level
//ARGUMENTS: print function, pointer to node
//RETURN:    nothing
//NOTES:     prints subsequent levels from node n until end
//           of the tree
template <class T>
void binTree<T>::level(void (*f)(T&), binTNode<T>* p) {
   queue<binTNode<T>*> wq;                                 // queue of pointers
   if (p != NULL) {                                        // while not null
      wq.push(p);                                          // push root on queue
      while (!wq.empty()) {                                // while queue is not empty
         p = wq.front();                                   // p = front item
         wq.pop();                                         // pop front item
         f(p->value);                                      // print previously front item
         
         if (p->left != NULL)                              // if left exists
            wq.push(p->left);                              // push it on queue
         if (p->right != NULL)                             // if right exists
            wq.push(p->right);                             // push it on queue
      }
   }
}

//FUNCTION:  postOrder
//ARGUMENTS: a function pointer
//RETURN:    nothing
//NOTES:     call r_postorder print the tree postorder
template <class T>
void binTree<T>::postOrder(void (*f) (T&)) {
   r_postorder(f, root);                                   // print nodes in postorder
}

//FUNCTION:  r_postorder
//ARGUMENTS: print function, pointer to node
//RETURN:    nothing
//NOTES:     prints the tree postorder
template <class T>
void binTree<T>::r_postorder(void (*f)(T&), binTNode<T>* p) {
   if (p != NULL) {                                        // if tree is not null
      r_postorder(f, p->left);                             // go leftmost subnode
      r_postorder(f, p->right);                            // go rightmost subnode
      f(p->value);                                         // print value
   }
}

//FUNCTION:  preorder
//ARGUMENTS: a function pointer
//RETURN:    nothing
//NOTES:     call r_preorder print the tree preorder
template <class T>
void binTree<T>::preOrder(void (*f) (T&)) {
   r_preorder(f, root);                                    // print nodes in preorder
}

//FUNCTION:  r_preorder
//ARGUMENTS: print function, pointer to node
//RETURN:    nothing
//NOTES:     prints the tree preorder
template <class T>
void binTree<T>::r_preorder(void (*f)(T&), binTNode<T>* p) {
   if (p != NULL) {                                        // if tree is not null
      f(p->value);                                         // print node value
      r_preorder(f, p->left);                              // go leftmost node
      r_preorder(f, p->right);                             // go rightmost node
   }
}


//FUNCTION:  r_size 
//ARGUMENTS: pointer to node
//RETURN:    0 or size of tree
//NOTES:     calcs and returns the total size
template <class T>
int binTree<T>::r_size(binTNode<T>* p) const {
   int left = 0, right = 0;                                // left and right node counts
   if (p != NULL) {                                        // if tree is not null
      left = r_size(p->left);                              // left nodes
      right = r_size(p->right);                            // right nodes
      return 1 + left + right;                             // return left + right + self
   }                                                       // else, 
   return 0;                                               // return 0
}

//FUNCTION:  r_leaves
//ARGUMENTS: pointer to node
//RETURN:    number of leaves
//NOTES:     cals the number of leaves and returns it
template <class T>
int binTree<T>::r_leaves(binTNode<T>* p) const {
   int left = 0, right = 0;
   if (p == NULL)                                          // no node?
      return 0;                                            // return
   
   if (p->left == NULL && p->right == NULL)
      return 1 + left + right;                             // incriment count
   
   else {
      left = r_leaves(p->left);                            // left nodes
      right = r_leaves(p->right);                          // right nodes
      return left + right;                                 // return running total
   }
}

#endif
