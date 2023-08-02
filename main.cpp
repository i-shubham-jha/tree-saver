#include "tree-saver.h"

struct node
{
    int data1;
    float data2;
    node * left, * right;
};

node * createNode(int a, double b)
{
    node * t = new node;
    t->data1 = a;
    t->data2 = b;
    t->left = t->right = NULL;
    return t;
}

int main ()
{
    // this is just a simple demo

    node * root = createNode(2, 5.282);

    root->left = createNode(5, 40.162 );

    root->right = createNode(676, 3838.873 );

    TreeSaver<node> obj1;
    obj1.save(root);

    free(root->left);
    free(root->right);
    free(root);

    TreeRetriever<node> obj2;
    root = obj2.retrieve();

    printf("root: %d, %f\n", root->data1, root->data2);

    node * temp = root->left;
    root = root->right;
    printf("LC: %d, %f\n", temp->data1, temp->data2);
    printf("root: %d, %f\n", root->data1, root->data2);
}
