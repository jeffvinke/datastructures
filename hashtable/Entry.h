#ifndef H_ENTRY
#define H_ENTRY

#define ID_SZ    3      // size of a key
#define ITEM_SZ 24      // max size for item description 
#define TBL_SZ  31      // default size for hash table
#define FREE   "$$$"    // indicates an empty spot in hash table

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::setw;
using std::setiosflags;
using std::left;
using std::right;
using std::resetiosflags;
using std::ios;

// definition of an entry in hash table

struct Entry {
     string key;        // key for an item
     string descript;   // description of an item
     int number;        // no of copies of an item
};

#endif

