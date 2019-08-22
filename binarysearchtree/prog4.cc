/****************************************************************
   PROGRAM:   Assignment 4
   AUTHOR:    Jeff Vinke
   CLASS:     CSCI 440, Section 1

   FUNCTION:  This impliments a binary search tree

   INPUT:     none

   OUTPUT:    None
****************************************************************/
#include "bintree.h"
#include "binstree.h"
#include <iomanip>
using std::showpoint;
using std::setprecision;
using std::fixed;

#define N 1000;                                            // max number value


//FUNCTION:  print_vals
//ARGUMENTS: Item to print out
//RETURN:    Nothing
//NOTES:     Prints items in rows of 16
static int counter=0;                                      // item counter
template<class T> 
void print_vals(T& x)
{  
   
   if (counter < 16) {                                     // if not 16th item
      cout << setw(4) << x;                                // print out item
      ++counter;                                           // incriment counter
    }
    else {
        cout << endl << setw(4) << x;                      // newline, then print 1st item
        counter = 1;                                       // reset counter
    }
}


//FUNCTION:  main
//ARGUMENTS: None
//RETURN:    0
//NOTES:     This is where the magic happens!
int main() {
   int n = -1,                                             // number of random nums to generate
       i = 0,                                              // loop counter
       success = 0,                                        // total search sucesses
       len = 0;                                            // average search length
   float successRatio,                                     // percentage of search to fail
         averageLen;                                       // average search length */
   binSTree<int> tree;                                     // create tree to hold ints
   srand(1);                                               // seed random number generator
  
   while (n < 0 || n > 1000) {                             // make sure # is in range
      cout << "How many nodes do you want in binary search tree ? ";
      cin >> n;                                            // get number of elements
   }
   
   int a[n];                                               // create array to hold values
   for (i = 0; i < n; ++i) {                               // create/insert n numbers
      a[i] = rand() % N;                                   // random # from 1 to N - 1
      tree.insert(a[i]);                                   // insert item
   }
   
   cout << "\n\nbinSTree:\n"                               // print tree specs
      << "\tno of nodes    = " << setw(2) << tree.size()
      << "\n\tno of leaves   = " << setw(2) << tree.leaves()
      << "\n\theight of tree = " << setw(2) << tree.height()
      << "\n\twidth of tree  = " << setw(2) << tree.width()
      << endl;

   for (i = 0; i < n; ++i) {                               // search tree
      if (tree.search(a[i],len))                           // for the values initially generated
         ++success;                                        // if they exist, update counter
   }

   successRatio = ((float)success / n) * 100;              // calc success ratio
   cout << endl << endl << "Ratio of successful searches for 'binSTree' is " << showpoint    
      << setprecision(2) << fixed << successRatio << " %";
   averageLen = (float)len / n;                            // calc average length
   cout << endl << "Average search length for 'binSTree' is  " << showpoint    
      << setprecision(2) << fixed << averageLen << endl;

   cout << endl << "The elements of 'binSTree' in inOrder:" << endl << endl;
   tree.inOrder(print_vals);                               // print out tree 

   for (i = 0; i < n; ++i) {                               // traverse array
      if (a[i] > 3)                                        // if greater then 3
         for (int x = 2; x < a[i] / 2; ++x) {              // test up to half its value
            if (a[i] % x == 0)                             // if remainder is 0
               tree.remove(a[i]);                          // prime, remove it
         }
      else if (a[i] < 3)                                   // if its 0-3
         tree.remove(a[i]);                                // remove it because its evil
   }
 
   counter = 0;
   cout << "\n\nbinSTree:\n"                               // print tree specs
      << "\tno of nodes    = " << setw(2) << tree.size()
      << "\n\tno of leaves   = " << setw(2) << tree.leaves()
      << "\n\theight of tree = " << setw(2) << tree.height()
      << "\n\twidth of tree  = " << setw(2) << tree.width()
      << endl;
   
   success = 0;                                            // reset counter 
   len = 0;                                                // reset counter 
   
   for (i = 0; i < n; ++i) {                               // search tree
      if (tree.search(a[i],len))                           // for the values initially generated
         ++success;                                        // if they exist, update counter
   }

   successRatio = ((float) success / n) * 100;              // calc success ratio
   cout << endl << endl << "Ratio of successful searches for 'binSTree' is " << showpoint    
      << setprecision(2) << fixed << successRatio << " %";

   averageLen = (float) len / n;                            // calc average length
   cout << endl << "Average search length for 'binSTree' is  " << showpoint    
      << setprecision(2) << fixed << averageLen << endl;

   cout << endl << "The elements of 'binSTree' in inOrder:" << endl << endl;
   tree.inOrder(print_vals);                               // print out tree 
   cout << endl << endl;                                   // blank line, for fun. 

   return 0;
}
