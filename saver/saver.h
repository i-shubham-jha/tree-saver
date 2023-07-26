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

    // function to store the children information in the children.dat file
    void storeChildren(T * root);

public:

    // function to begin saving of the tree on hdd
    void save(T * root);
};


// keeping all the definitions here only
// otherwise the functions are not compiled
// https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
inline void log(const std::string & str)
{
    std::cout << str << std::endl;
}

template <typename T>
void TreeSaver<T>::save(T * root)
{
    log("starting save function");
    count = 0;

    if(!root)
    {
        log("Tree does NOT exist\nExiting...");
        return;
    }

    // tree exists

    // first traversal for creating the map and storing the data of the nodes in nodes.dat file
    log("calling storeNodes function");
    storeNodes(root);
    log("storeNodes has returned");

    // but the children information still needs to be stored
    log("calling storeChildren function");
    storeChildren(root);
    log("storeChildren has returned");
}

template <typename T>
void TreeSaver<T>::storeNodes(T * root)
{
    std::ofstream fout; // for writing to "nodes" file

    // creating a hidden directory in the current directory to store both the files
    fout.open("nodes.dat");

    std::queue<T *> q; // for BFS

    log("starting first traversal");

    q.push(root);

    // standard BFS implementation
    while(!q.empty())
    {
        root = q.front();
        q.pop();

        count++; // one more node dealt with

        // creating entries for this node in the map
        hash.insert({root, count - 1}); // the index from BFS

        // adding this (count-1) th node to the nodes.dat file
        writeNode(fout, root );

        // adding its children in the queue
        if(root->left) q.push(root->left);
        if(root->right) q.push(root->right);
    }
    log("first traversal done");
    fout.close();
    return;
}

template <typename T>
void TreeSaver<T>::writeNode(std::ofstream & fout, T * nodeptr)
{
    T temp = *nodeptr;

    // won't store the actuall address in the file, just making them NULL
    temp.left = NULL;
    temp.right = NULL;

    fout.write((char * ) &temp, sizeof(temp) ); // all the data members of the OG node have been written to the hdd file nodes.dat
}

template <typename T>
void TreeSaver<T>::storeChildren(T * root)
{
    // need to bfs again, but this time check out the children
    // if NULL, store -1 in the file,
    // else find the ID/index of the chidlren using the map "hash"

    std::ofstream fout;

    fout.open("children.dat"); // a hidden file

    std::queue<T *> q;

    log("starting second traversal");

    q.push(root);

    // no need for knowing index of a node,
    // we are processing nodes in the same order so no need.

    while(!q.empty())
    {
        int size = q.size();

        while(size--)
        {
            root = q.front();
            q.pop();

            int lc = - 1, rc = -1;

            if(root->left)
            {
                lc = hash.find(root->left)->second;
                q.push(root->left);
            }
            // no need of else, lc is already -1, and we don't need to add lc in queue

            if(root->right)
            {
                rc = hash.find(root->right)->second;
                q.push(root->right);
            }

            // writing these children indices to the file

            fout << lc << " " << rc << "\n";
        }
    }
    log("second traversal done");
    fout.close();
}

