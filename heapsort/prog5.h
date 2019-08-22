#ifndef __prog5_h_
#define __prog5_h_
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <fstream>
#include <iomanip>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::less;
using std::greater;
using std::ifstream;
using std::setw;

#define D1 "./data/prog5.d1"
#define D2 "./data/prog5.d2"
#define D3 "./data/prog5.d3"

#define INT_SZ 4    // width of an integer
#define FLT_SZ 7    // width of a floating-pt number
#define STR_SZ 12   // width of a string object

#define INT_LN 15   // no of integers on a single line
#define FLT_LN 9    // no of floating-pt numbers on a single line
#define STR_LN 5    // no of string objects on a single line

// function prototypes
template<class T, class Pred> 
void insert(vector<T>&, const T&, Pred);

template<class T, class Pred> 
T remove(vector<T>&, Pred);

template<class T, class Pred> 
void upheap(vector<T>&, int, Pred);

template<class T, class Pred> 
void downheap(vector<T>&, int, Pred);

template<class T, class Pred>
void get_list(vector<T>&, const char*, Pred);

template<class T, class Pred>
void print_list(vector<T>&, const int, const int, Pred);

#endif

