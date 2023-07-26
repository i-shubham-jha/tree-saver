#include "tree-saver.h"

struct Node
{
    int data;
    Node * left;
    Node * right;
};

int main ()
{
    Node * root = new Node;
    root->right = NULL;
    root->data = 0;

    Node * n2 = new Node;
    n2->left = NULL;
    n2->right = NULL;
    n2->data = 0;

    root->left = n2;

    TreeSaver<Node> ob;

    ob.save(root);
    puts("Jinda hai");
}
