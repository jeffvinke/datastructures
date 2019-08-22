/****************************************************************
   PROGRAM:   Assignment 4
   AUTHOR:    Jeff Vinke
   CLASS:     CSCI 440, Section 1

   FUNCTION:  This impliments a binary search tree

   INPUT:     none

   OUTPUT:    None
****************************************************************/
#ifndef __binstree_h__
#define __binstree_h__

#include "bintree.h"
#include "bintnode.h"

template <class T>
class binSTree : public binTree<T> {
   public:
      binSTree() { }
      ~binSTree() { }
      void insert(const T& val);                           // insert function
      void remove(const T& val);                           // remove node with value
      bool search(T& val, int& len) const;                 // search for value

   private:
      void removeC(binTNode<T>*& node);                    // remove by copy
      void findnode(const T& val);                         // locate node to delete
      bool search(binTNode<T>* p, T& val, int& len) const; // search for node with value
};

//FUNCTION:  Insert function
//ARGUMENTS: Value to insert
//RETURN:    Nothing
//NOTES:     Calls BST Insert function
template <class T>
void binSTree<T>::insert(const T& val) {
   binTree<T>::insert2(val);
}

//FUNCTION:  Remove
//ARGUMENTS: Value to remove
//RETURN:    Nothing
//NOTES:     Calls find node to find node to delete
//           Then findnode calls another function to remove it
template <class T>
void binSTree<T>::remove(const T& val) {
   findnode(val);
}

//FUNCTION:  Search function
//ARGUMENTS: Value to insert and length
//RETURN:    True or false
//NOTES:     Calls search with pointer to locate node
template <class T>
bool binSTree<T>::search(T& val, int& len) const {
   bool result = false;
   result = search(binTree<T>::root, val, len);
   return result;
}

//FUNCTION:  Findnode
//ARGUMENTS: Value to find
//RETURN:    Nothing
//NOTES:     Calls remove function to delete the node
template <class T>
void binSTree<T>::findnode(const T& val) {
   binTNode<T>* node = binTree<T>::root, *prev = 0;        // node = root, prev for holding previous val
   while (node != 0) {                                     // while node is not null
      if (node->value == val)                              // if nodes value is the one we want
         break;                                            // break, we got it
      prev = node;                                         // else set this node as previous
      if (node->value < val)                               // if the value is less
         node = node->right;                               // go right
      else node = node->left;                              // otherwise, go left
   }

   if (node != 0 && node->value == val)                    // if node is not null and we have the right value
      if (node == binTree<T>::root)                        // if the node to delete is root
         removeC(binTree<T>::root);                        // remove root
   
      else if (prev->left == node)                         // if the node we want is to the left
         removeC(prev->left);                              // remove left node
   
      else                                                 // else
         removeC(prev->right);                             // remove right
      
}


//FUNCTION:  RemoveC
//ARGUMENTS: Node to remove
//RETURN:    Nothing
//NOTES:     Removes by copying
template <class T>
void binSTree<T>::removeC(binTNode<T>*& node) {
   binTNode<T>* previous, *tmp = node;                     // previous node pointer and tmp node pointer
   if (node->right == 0)                                   // if no right child
      node = node->left;                                   // set node to left child
   
   else if (node->left == 0)                               // if no left child
      node = node->right;                                  // set node to right child

   else {                                                  // else
      tmp = node->left;                                    // set temp to left node
      previous = node;                                     // previous is current node
      while (tmp->right != 0) {                            // while right child not null
         previous = tmp;                                   // save the current node                               
         tmp = tmp->right;                                 // find where child is null
      }
      
      node->value = tmp->value;                            // copy value
      
      if (previous == node)                                
         previous->left = tmp->left;
      else previous->right = tmp->left;
   }
   delete tmp;                                             // delete node
}

//FUNCTION:  Search function
//ARGUMENTS: Node pointer, value to find, length
//RETURN:    True or false
//NOTES:     Finds the node if there
template <class T>
bool binSTree<T>::search(binTNode<T>* p, T& val, int& len) const {     
   static bool flag = false;

   if (p == 0) {                                           // if null
      flag = false;                                        // not found
   }

   else if (val < p->value) {                              // if val is less than
      ++len;                                               // incriment length
      search(p->left, val, len);                           // and go left
   }

   else if (val > p->value) {                              // if val is greater than
      ++len;                                               // incriment length
      search(p->right, val, len);                          // go right
   }

   else if (p->value == val) {                             // if value is found
      ++len;                                               // incriment the length
      flag =  true;                                        // set flag to return true
   }
   return flag;                                            // return result
}
#endif
