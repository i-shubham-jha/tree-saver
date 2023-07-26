#include <iostream>
#include <istream>

template <typename T> class TreeRetriever
{

public:
    T * retrieve(); // function to retrieve the tree
};


// including the implementations using tpp file
// normal cpp file won't work
#include "retriever.tpp"
