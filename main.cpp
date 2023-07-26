#include "./saver/saver.h"

struct Node
{
    int data;
    Node * left;
    Node * right;
};

int main ()
{
    Node * root = new Node;
    root->left = NULL;
    root->right = NULL;
    root->data = 0;

    TreeSaver<Node> ob;

    ob.save(root);
    puts("Jinda hai");
}
