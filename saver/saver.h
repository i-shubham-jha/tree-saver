#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <queue>

// PLEASE ONLY PROVIDE TREE'S NODE STRUCTURE AS THE TEMPLATE TYPENAME
// THE LEFT AND RIGHT CHILDS SHOULD BE NAMED 'left' and 'right'
// and should be pointers to same structure
// make sure that the variables are publicly accessible

// a template so that any kind of tree could be saved
template <typename T> class TreeSaver
{
    // a map from addresses to node indices
    // used for storing the children information in children. file
    std::unordered_map< T *, int> hash;


    // function to traverse the tree in Level order
    // keep on saving the nodes in the file nodes.dat
    // as well as map the addresses to indices in hash
    void storeNodes(T * root);

    // just writes the node to the output file "nodes"
    void writeNode(std::ofstream & fout, T * nodeptr);

    // number of nodes which have been saved
    int count;

public:

    // function to begin saving of the tree on hdd
    void save(T * root);
};
