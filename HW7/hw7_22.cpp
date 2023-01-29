#include <fstream>
#include <iostream>
#include <queue>
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
    string element;

public:
    TreeNode() : leftchild(0), rightchild(0), parent(0), key(0), element(""){};
    TreeNode(int a, string b) : leftchild(0), rightchild(0), parent(0), key(a), element(b){};

    int GetKey() { return key; }
    string GetElement() { return element; }

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

    TreeNode *Search(string name);
    void InsertBST(int key, string element);
    void InorderPrint();
    void Levelorder();
    void DeleteBST(string name);
};

TreeNode *BinarySearchTree::Search(string name)
{

    TreeNode *current = root;

    while (current != NULL && name != current->element)
    {

        if (name < current->element)
        {
            current = current->leftchild;
        }
        else
        {
            current = current->rightchild;
        }
    };
    if (current)
        cout << current->element << "\t0" << current->key << endl;
    else
        cout << name << " is not in the list" << endl;
    return current;
}

TreeNode *BinarySearchTree::Leftmost(TreeNode *current)
{
    while (current->leftchild != NULL)
    {
        current = current->leftchild;
    }
    return current;
}

TreeNode *BinarySearchTree::Successor(TreeNode *current)
{
    if (current->rightchild != NULL)
    {
        return Leftmost(current->rightchild);
    }

    TreeNode *successor = current->parent;
    while (successor != NULL && current == successor->rightchild)
    {
        current = successor;
        successor = successor->parent;
    }
    return successor;
}

void BinarySearchTree::InsertBST(int key, string element)
{

    TreeNode *y = 0;
    TreeNode *x = 0;
    TreeNode *insert_node = new TreeNode(key, element);

    x = root;
    while (x != NULL)
    {
        y = x;
        if (insert_node->element < x->element)
        {
            x = x->leftchild;
        }
        else
        {
            x = x->rightchild;
        }
    }

    insert_node->parent = y;

    if (y == NULL)
    {
        this->root = insert_node;
    }
    else if (insert_node->element < y->element)
    {
        y->leftchild = insert_node;
    }
    else
    {
        y->rightchild = insert_node;
    }
}

void BinarySearchTree::InorderPrint()
{
    TreeNode *current = new TreeNode;
    current = Leftmost(root);
    while (current)
    {
        cout << current->element << "\t0" << current->key << endl;
        current = Successor(current);
    }
}

void BinarySearchTree::DeleteBST(string name)
{

    TreeNode *delete_node = Search(name);
    if (delete_node == NULL)
    {
        std::cout << "data not found.\n";
        return;
    }

    TreeNode *y = 0;
    TreeNode *x = 0;

    if (delete_node->leftchild == NULL || delete_node->rightchild == NULL)
    {
        y = delete_node;
    }
    else
    {
        y = Successor(delete_node);
    }

    if (y->leftchild != NULL)
    {
        x = y->leftchild;
    }
    else
    {
        x = y->rightchild;
    }

    if (x != NULL)
    {
        x->parent = y->parent;
    }

    if (y->parent == NULL)
    {
        this->root = x;
    }
    else if (y == y->parent->leftchild)
    {
        y->parent->leftchild = x;
    }
    else
    {
        y->parent->rightchild = x;
    }

    if (y != delete_node)
    {
        delete_node->key = y->key;
        delete_node->element = y->element;
    }

    delete y;
    y = 0;
}

void BinarySearchTree::Levelorder()
{

    std::queue<TreeNode *> q;
    q.push(this->root);

    while (!q.empty())
    {

        TreeNode *current = q.front();
        q.pop();
        cout << current->element << "\t0" << current->key << endl;

        if (current->leftchild != NULL)
        {
            q.push(current->leftchild);
        }
        if (current->rightchild != NULL)
        {
            q.push(current->rightchild);
        }
    }
}

int main()
{

    ifstream infile;
    infile.open("HW7_22.txt");
    BinarySearchTree T;
    string name;
    int number, choice = -1;

    while (infile >> name >> number)
        T.InsertBST(number, name);

    while (choice != 5)
    {
        cout << "MENU" << endl
             << "1.Search, 2.Insert, 3.Delete, 4.Print list, 5.Quit" << endl
             << "Enter Your choice: ";
        cin >> choice;
        cout << endl;
        if (choice == 1)
        {
            cout << "Name:";
            cin >> name;
            T.Search(name);
        }
        else if (choice == 2)
        {
            cout << "Name:";
            cin >> name;
            cout << "Phone number:";
            cin >> number;
            T.InsertBST(number, name);
            T.Levelorder();
        }
        else if (choice == 3)
        {
            cout << "Name:";
            cin >> name;
            T.DeleteBST(name);
            T.Levelorder();
        }
        else if (choice == 4)
            T.Levelorder();
        cout << endl;
    }

    return 0;
}