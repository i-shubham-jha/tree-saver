#include "saver.h"

void log(const std::string & str)
{
    std::cout << str << std::endl;
}

template <typename T>
void TreeSaver<T>::save(T * root)
{
    count = 0;

    if(!root)
    {
        log("Tree does NOT exist\nExiting...");
        return;
    }

    // tree exists

    // first traversal for creating the map and storing the data of the nodes in nodes.dat file
    storeNodes(root);
}

template <typename T>
void TreeSaver<T>::storeNodes(T * root)
{
    std::ofstream fout; // for writing to "nodes" file

    // creating a hidden directory in the current directory to store both the files
    fout.open("./.tree-saver-files/nodes.dat");

    std::queue<T *> q; // for BFS

    log("starting traversal of tree");

    q.push(root);

    // standard BFS implementation
    while(!q.empty())
    {
        int size = q.size();

        while(size--)
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
    temp->left = NULL;
    temp->right = NULL;

    fout.write((char * ) &temp, sizeof(temp) ); // all the data members of the OG node have been written to the hdd file nodes.dat
}




