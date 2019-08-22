/****************************************************************
   PROGRAM:   Assignment 3
   AUTHOR:    Jeff Vinke
   CLASS:     CSCI 440, Section 1

   FUNCTION:  This is the node for the binary tree implimentation

   INPUT:     none

   OUTPUT:    None
****************************************************************/

#ifndef __BINTNODE_H_
#define __BINTNODE_H_

template <class T> class binTree;
template <class T> class binTNode {
   friend class binTree<T>;
   
   public: 
      binTNode(const T& =T (), binTNode<T>* =0, binTNode<T>* =0);
   
   private:
      T value;                                             // value of node
      binTNode<T> *left, *right;                           // left and right ptrs
};

//FUNCTION:  Constructor for node
//ARGUMENTS: value, left pointer, right pointer
//RETURN:    Nothing
//NOTES:     None
template <class T>      
binTNode<T>::binTNode(const T& val, binTNode<T>* lleft, binTNode<T>* lright) {
   value = val;                                            // value of node
   left = lleft;                                           // left pointer
   right = lright;                                         // right pointer
}
#endif
