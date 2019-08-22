
#ifndef __HTABLE_H_
#define __HTABLE_H_
#include "Entry.h"

// a class for an hash table

class hTable {
public:
    hTable(int =TBL_SZ);     // constructor
    ~hTable();               // destructor

    void insert(const Entry&);  // inserts an item in hash table
    void search(const string&); // searches for an item

    void tablprnt();    // prints hash table entries
    void ptablprnt();   // prints hash table entries in sorted order

private:
    int size,           // size of hash table
        psize;          // actual size of ptr table

    Entry*  table;      // ptr to hash table
    Entry** ptable;     // ptr to table of ptrs to hash table

    void sort();                // sorts pointer table
    int hash(const string&);    // hash function
};

#endif

