/****************************************************************
   PROGRAM:   Assignment 6
   AUTHOR:    Jeff Vinke
   CLASS:     CSCI 440, Section 1

   FUNCTION:  This is the driver for a hash table implimentation
   
   INPUT:     prog6.d_1
              prog6.d_2

   OUTPUT:    Inserted items, searched for items, printed tables
              and a sorted table at the end.
****************************************************************/
#include "Entry.h"
#include "hTable.h"

/****************************************************************
   FUNCTION:  Main
   ARGUMENTS: argc, argv
   RETURN:    0 assuming no error
   NOTE:      Main opens the file, and handles control over 
              inserting, searching for, or printing to the 
              hash table. After it has read in all the data
              it then prints out the sorted hash table that
              was sorted on the key field
****************************************************************/
int main(int argc, char **argv) {
   string buffer;                                               // input buffer
   Entry temp;                                                  // temp storage
   hTable x(TBL_SZ);                                            // table
   int ldig = 0,                                                // last pos of number
       fdesc = 0,                                               // begin of descr
       ldesc=0;                                                 // end of desc
   
   ifstream infile;                                             // instream var
   infile.open(argv[1], ifstream::in);                          // open file
   if (!infile) {                                               // failed? 
      cout << "\n\n ERROR! Cannot open file!";                  // display error
      exit(1);
   }
   
   cout << "   *** Hashing with linear probe assignment ***\n\n";
   
   while (getline(infile, buffer)) {
      switch (buffer[0]) {
         case 'A':
            ldig = buffer.find(':', 6);                         // find the next colon
            fdesc = ldig + 1;                                   // first description
            ldesc = buffer.find(':', fdesc);                    // find next colon

            temp.key = buffer.substr(2, 3);                     // get string
            temp.descript = buffer.substr(fdesc, (ldesc - fdesc)); // get description
            temp.number = atoi((buffer.substr(6,(ldig-6))).c_str());  // get number

            x.insert(temp);                                     // insert item
            break;
                    
         case 'S':
            temp.key = buffer.substr(2, 3);                     // grab key field
            x.search(temp.key);                                 // search for it
            break;

         case 'P':
            x.tablprnt();                                       // print table
            break;
      }
   }

   x.ptablprnt();                                               // print sorted table
   cout << "\n   *** end of program termination ***";
               
   infile.close();                                              // close file
   return 0;
}

