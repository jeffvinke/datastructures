/****************************************************************
   PROGRAM:   Assignment 6
   AUTHOR:    Jeff Vinke
   CLASS:     CSCI 440, Section 1

   FUNCTION:  This impliments the hash table
   
   INPUT:     none

   OUTPUT:    none
****************************************************************/
#include "hTable.h"

#define w2 10
#define w1 260

/****************************************************************
   FUNCTION:  Constructor
   ARGUMENTS: table size
   RETURN:    Nothing
   NOTE:      The constructor creates the two tables and 
              initializes them. If one of them is not created
              an error message is printed
****************************************************************/
hTable::hTable(int tsize) { 
   table = new Entry[tsize];                                                   // create new table
   ptable = new Entry*[tsize];                                                 // create a pointer table
   
   if ((!table) || (!ptable)) {                                                // error creating? exit
         cout << "ERROR CREATING TABLES!\n";
         exit(1);
   }
   
   for (int i = 0; i < tsize; ++i ) {                                          // set up tables
      table[i].key = FREE;
      ptable[i] == NULL;
   }
    
   size = tsize;                                                               // set size to table size
   psize = 0;                                                                  // set ptable size to 0                                      
}

/****************************************************************
   FUNCTION:  Destructor
   ARGUMENTS: None
   RETURN:    Nothing
   NOTE:      This destroys the table and resets sizes
****************************************************************/
hTable::~hTable() { 
     Entry*  x1 = table;                                                       // temp vars for deletion
     Entry** x2 = ptable;

     delete [] x1;                                                             // delete table
     delete [] x2;                                                             // delete ptable

     size = 0;                                                                 // reset variables
     psize = 0;
}

/****************************************************************
   FUNCTION:  Insert
   ARGUMENTS: Object of type Entry to insert
   RETURN:    Nothing
   NOTE:      This function inserts an item into the table or   
              returns control back to main depending on these 
              critera:
              item exists? print error msg and return
              table full? print error msg and return
              slot full? use linear probe to find new slot
              else? insert the item into the table

              After a successful insert the next available ptable
              location will be set to point towards it.
****************************************************************/
void hTable::insert(const Entry& e) {

   int hkey = hash(e.key);
   int tempkey = hkey;

         
   if ((table[hkey].key != FREE) && (table[hkey].key != e.key)) { 
      if (hkey == size -1 )                                                    // if key is at max slot
         hkey = 0;                                                             // reset to 0
      
      while (table[++hkey].key != FREE) { 
         
         if (hkey == tempkey) {                                                // table is full
            cout << "insert: " << ":" << setw(3) << e.key << ":" <<            // print out error msg
               setw(4) << e.number << ":" <<  setw(24) << e.descript << 
               " : not inserted - table full!!!" << endl;
            return;
         }
         
         if (hkey >= size -1 )                                                 // if at max entry start over at 0
            hkey = 0;
      } 
      
   }
         
   else if (table[hkey].key == e.key) {                                        // if duplicate key, print message
      cout << "insert: " << ":" << setw(3) << e.key << ":" <<                  // then return
         setw(4) << e.number << ":" <<  setw(24) << e.descript << 
         " : not inserted - duplicate key!!!" << endl;
      return;
   }
   
   if (table[hkey].key == FREE) {                                              // insert the Entry
      
      table[hkey].number = e.number;                                           // copy over information
      table[hkey].descript = e.descript;
      table[hkey].key = e.key;  
      
      ptable[psize] = table + hkey;
      ++psize;
      
      cout << "insert: " << ":" << setw(3) << table[hkey].key << ":" <<
         setw(4) << table[hkey].number << ":" <<  setw(24) << table[hkey].descript << 
         " : entry = " << hkey << endl;
   }
}

/****************************************************************
   FUNCTION:  Insert
   ARGUMENTS: Vector, item to insert, compare function
   RETURN:    Nothing
   NOTE:      This function takes pushes the item on to the back
              of the vector and then calls the upheap function
              to recreate the heap.
****************************************************************/
void hTable::search(const string& s) {
   int hkey = hash(s);                                                      // get hash key
   int tempkey = hkey;                                                      // original hash location
      
   if (hkey == size -1 )                                                    // if key is at max slot
      hkey = 0;                                                             // reset to 0
   
   while (table[++hkey].key != s)  {
      if (hkey == tempkey) {                                                // table is full
         cout << "search: Key "<< s << " not in table!!\n";                 // print msg
         return;                                                            // return
      }

      if (hkey >= size -1 )                                                 // if at max entry start search
         hkey = 0;                                                          // over at 0
   }

   cout << "search: Key "<< s << " ==> number: " << setw(4) << table[hkey].number 
      << " - item: " << table[hkey].descript << endl; 
}


/****************************************************************
   FUNCTION:  tablprnt
   ARGUMENTS: None
   RETURN:    Nothing
   NOTE:      This function simply iterates through the table   
              printing out all the items that exist in the table
****************************************************************/
void hTable::tablprnt() { 
   cout << "\n\ntablprnt:\n";
   cout << "entry  key    number    description\n";

   for (int i = 0; i < size; ++i) {                                            // iterate through table
      int hkey = hash(table[i].key);                                           // printing out values
      if (table[i].key != FREE)
         cout << setw(4) << setiosflags(ios::right) << hkey << ":  " << setw(3) << table[i].key << "  -" <<
            setw(6) << table[i].number << "  -  " << table[i].descript << endl << endl;
   }
}

/****************************************************************
   FUNCTION:  ptablprnt
   ARGUMENTS: None
   RETURN:    Nothing
   NOTE:      This function calls sort() to sort the table. Then
              this function simply iterates through the ptable  
              printing out all the items in sorted order.     
****************************************************************/
void hTable::ptablprnt() { 
   sort();                                                                     // sort the array
   Entry temp;                                                                 // temp storage
   cout << "\n\nsortprnt:\n";
   cout << "   sorted hash table:\n";
   cout << "   key    number    description\n";
   
   for (int i=0;i < psize; ++i) {                                                 // iterate through, printing sortec items
      temp=*ptable[i];
      cout << "   " << setw(3) << temp.key << "  -" << setw(6) << temp.number 
         << "  -  " << temp.descript << endl;
   
   }  
}

/****************************************************************
   FUNCTION:  sort
   ARGUMENTS: None
   RETURN:    Nothing
   NOTE:      This function sorts the pointers which point to 
              the data in the table.
****************************************************************/
void hTable::sort() {

    int top=0,                                                                 // top item
        curr=0,                                                                // current item
        low=0;                                                                 // current lowest
    Entry t1,                                                                  // temp entry for sorting
          t2,                                                                  // same
          temp;                                                                // swap storage

    while (top < psize ) {
        curr=top + 1;                                                          // start at top pos + 1
        low=top;                                                               // top value is new lowest
        while( curr < psize) {
            t1=*ptable[curr];     
            t2=*ptable[low];
            
            if(t1.key < t2.key)                                                // if smaller then top
                low=curr;                                                      // we have new low value
           ++curr;                    
        }

        temp = *ptable[top];                                                   // swap the items
        *ptable[top] = *ptable[low]; 
        *ptable[low] = temp;
        ++top; 
    }
}

/****************************************************************
   FUNCTION:  hash  
   ARGUMENTS: string to hash
   RETURN:    hash
   NOTE:      This function takes a string of 3 characters and
              returns a hash for it. The constants are defined 
              at the top.
****************************************************************/
int hTable::hash(const string& s) { 
   int k1,                                                                     // key char 1
       k2,                                                                     // key char 2
       k3;                                                                     // key char 3

   k1 = s[0] - 'A';                                                            // place from 0-25
   k2 = s[1] - 'A';                                                            // place from 0-25
   k3 = s[2] - '0';                                                            // place to 0-10

   return (((w1 * k1) + (w2 * k2) + k3) % TBL_SZ);                             // return hash
}


