/****************************************************************
   PROGRAM:   Assignment 5
   AUTHOR:    Jeff Vinke
   CLASS:     CSCI 440, Section 1

   FUNCTION:  This program impliments a heap sort
   
   INPUT:     prog5.d1
              prog5.d2
              prog5.d3

   OUTPUT:    Selected ascending/descending sorts
****************************************************************/
#include "prog5.h"

int main()
{
    vector<int>    v1(1);   // a heap of integers
    vector<float>  v2(1);   // a heap of floating-pt numbers
    vector<string> v3(1);   // a heap of string objects

    // print header message
    cout << "\t\t\t*** CSCI 440: Program 5 - Output ***\n\n";

    // sort and print first list

    cout << "first list - ascending order:\n\n";
    get_list(v1, D1, less<int>());
    print_list(v1, INT_SZ, INT_LN, less<int>());
    cout << endl;
    
    cout << "first list - descending order:\n\n";
    get_list(v1, D1, greater<int>());
    print_list(v1, INT_SZ, INT_LN, greater<int>());
    cout << endl;

    // sort and print second list
  
    cout << "second list - ascending order:\n\n";
    get_list(v2, D2, less<float>());
    print_list(v2, FLT_SZ, FLT_LN, less<float>());
    cout << endl;

    cout << "second list - descending order:\n\n";
    get_list(v2, D2, greater<float>());
    print_list(v2, FLT_SZ, FLT_LN, greater<float>());
    cout << endl;

    // sort and print third list

    cout << "third list - ascending order:\n\n";
    get_list(v3, D3, less<string>());
    print_list(v3, STR_SZ, STR_LN, less<string>());
    cout << endl;

    cout << "third list - descending order:\n\n";
    get_list(v3, D3, greater<string>());
    print_list(v3, STR_SZ, STR_LN, greater<string>());
    cout << endl;
  
    // print termination message
    cout << "\t\t\t*** end of program execution ***\n\n";

    return 0;
}

/****************************************************************
   FUNCTION:  Insert
   ARGUMENTS: Vector, item to insert, compare function
   RETURN:    Nothing
   NOTE:      This function takes pushes the item on to the back
              of the vector and then calls the upheap function
              to recreate the heap.
****************************************************************/
template<class T, class Pred> 
void insert(vector<T>& v, const T& item, Pred compare) {
   v.push_back(item);
   upheap(v, v.size() - 1, compare);
}

/****************************************************************
   FUNCTION:  Remove               
   ARGUMENTS: Vector, item to insert, compare function
   RETURN:    Item removed
   NOTE:      This function saves the first item in heap to a
              temp function, then replaces it with the last item
              in the heap. The downheap function is called and 
              the removed value is returned.
****************************************************************/
template<class T, class Pred> 
T remove(vector<T>& v, Pred compare)  {
   T tmp = v[1];                                                // tmp = first element
   v[1] = v.back();                                             // first element = back elemnt
   v.pop_back();                                                // pop back element
   downheap(v, 1, compare);                                     // downheap
   return tmp;                                                  // return value
}

/****************************************************************
   FUNCTION:  Upheap                              
   ARGUMENTS: Vector, index of item, compare function
   RETURN:    Nothing
   NOTE:      This function take the node just inserted and 
              checks to make sure it and its predicessors are in
              agreement with the type of heap. 
****************************************************************/
template<class T, class Pred> 
void upheap(vector<T>& v, int position, Pred compare) {
   T temp;                                                      // temp variable
   bool done = false;                                           // done checking?
   int parent;                                                  // parent node
   while ((position / 2 > 0) && (!done)) {                      // while the parent exists
      parent = position / 2;                                    // get the parent
      
      if (compare(v[position], v[parent])) {                    // compare node to parent
         temp = v[parent];                                      // swap the parent
         v[parent] = v[position];                               // and the child
         v[position] = temp;
         position = parent;
      }
      
      else {
         done = true;                                           // otherwise, we're done
      }
   }
}

/****************************************************************
   FUNCTION:  Downheap             
   ARGUMENTS: Vector, index of item, compare function
   RETURN:    Nothing
   NOTE:        
****************************************************************/
template<class T, class Pred> 
void downheap(vector<T>& v, int position, Pred compare) {
   T tmp;                                                       // temp variable
   int child;                                                   // child index
   bool done = false;                                           // done checking?
   while ((position * 2 < v.size()) && (!done)) {               // while the child exists
      if (position * 2 == v.size() -1)                          
         child = position * 2;                                  // child is last element
      else if (compare(v[position*2], v[position*2+1]))         // otherwise compare children
         child = position *2;                                   // its left child
      else 
         child = position*2 +1;                                 // its right child

      if (compare(v[child], v[position])) {                     // compare greatest child
         tmp = v[position];                                     // swap if needed
         v[position] = v[child];
         v[child] = tmp;
         position = child;
      }
      else
         done = true;                                           // set done flag
   }
}

/****************************************************************
   FUNCTION:  get_list
   ARGUMENTS: Vector, file pointer, compare function
   RETURN:    Nothing
   NOTE:      This function reads in file until eof calling 
              insert function to insert the data
****************************************************************/
template<class T, class Pred>
void get_list(vector<T>& v, const char* fp, Pred compare) {
   ifstream infile;                                             // instream var
   T tmp;                                                       // temp var for input
   infile.open(fp, ifstream::in);                               // open file
   if (!infile) {                                               // failed? 
      cout << "\n\n ERROR! Cannot open file!";                  // display error
      exit(1);
   }
   while (infile >> tmp) {                                      // otherwise
      insert(v,tmp, compare);                                   // insert it
   }
   infile.close();                                          
}

/****************************************************************
   FUNCTION:  print_list
   ARGUMENTS: Vector, width, items per line, compare function
   RETURN:    Nothing
   NOTE:      This function prints out the items in the heap
              at n items per line.
****************************************************************/
template<class T, class Pred>
void print_list(vector<T>& v, const int w, const int line, Pred compare) {
   int size = v.size();
   for (int i = 1; i < size; ++i) {
      cout << setw(w+2) << remove(v,compare);
      if (i % line == 0 ) cout << endl;
   }
}


