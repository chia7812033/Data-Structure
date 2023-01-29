#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class BinarySearchTree;
class TreeNode
{
private:
    TreeNode *leftchild;
    TreeNode *rightchild;
    TreeNode *parent;
    int key;
    bool risThreaded;
    bool lisThreaded;

public:
    TreeNode() : leftchild(0), rightchild(0), parent(0), key(0), risThreaded(1), lisThreaded(1){};
    TreeNode(int a) : leftchild(0), rightchild(0), parent(0), key(a), risThreaded(1), lisThreaded(1){};

    friend class BinarySearchTree;
};

class BinarySearchTree
{
private:
    TreeNode *root;
    TreeNode *Leftmost(TreeNode *current);
    TreeNode *Successor(TreeNode *current);

public:
    BinarySearchTree() : root(0){};

    void InsertBST(int key);
    void InorderPrint(ofstream &out);
};

TreeNode *BinarySearchTree::Leftmost(TreeNode *current)
{
    while(current->lisThreaded == false)
        current = current->leftchild;

    return current;
}

TreeNode *BinarySearchTree::Successor(TreeNode *current)
{
    if (current->risThreaded)
    {
        return current->rightchild;
    }

    current = current->rightchild;
    current = Leftmost(current);

    return current;
}

void BinarySearchTree::InsertBST(int key)
{

    TreeNode *y = 0;
    TreeNode *x = 0;
    TreeNode *insert_node = new TreeNode(key);

    x = root;
    while (x != NULL)
    {
        y = x;
        if (insert_node->key < x->key)
        {
            if (x->lisThreaded == false)
                x = x->leftchild;
            else
                break;
        }
        else
        {
            if (x->risThreaded == false)
                x = x->rightchild;
            else
                break;
        }
    }

    insert_node->parent = y;

    if (y == NULL)
    {
        this->root = insert_node;
    }
    else if (insert_node->key < y->key)
    {
        insert_node->leftchild = y->leftchild;
        insert_node->rightchild = y;
        y->lisThreaded = false;
        y->leftchild = insert_node;
    }
    else
    {
        insert_node->leftchild = y;
        insert_node->rightchild = y->rightchild;
        y->risThreaded = false;
        y->rightchild = insert_node;
    }
}

void BinarySearchTree::InorderPrint(ofstream &out)
{
    TreeNode *current = new TreeNode;
    current = root;

    current = Leftmost(current);

    while(current != NULL)
    {
        out << current->key << endl;
        current = Successor(current);
    }
    
}

int main()
{
    ifstream infile;
    infile.open("7_24_input.txt");
    int number;
    BinarySearchTree T;

    while (infile >> number)
        T.InsertBST(number);

    ofstream outfile;
    outfile.open("7_24_output.txt");
    T.InorderPrint(outfile);
}
