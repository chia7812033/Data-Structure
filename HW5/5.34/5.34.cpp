#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
using namespace std;

struct Node
{
    string code;
    string name;
    double price;
    double amount;
    int share_held;
    Node *prev;
    Node *next;
};

class Doubly_Linked_List
{
    Node *front; 
    Node *end;   
public:
    Doubly_Linked_List()
    {
        front = NULL;
        end = NULL;
    }
    void insertAtTheBegin(string, string, double, double, int);
    void forwawrd_print();
    void backward_print();
    void bubbleSort1();
    void bubbleSort2();
};

void Doubly_Linked_List::insertAtTheBegin(string code,
                                          string name,
                                          double price,
                                          double amount,
                                          int share_held)
{
    struct Node *ptr1 = new Node;
    ptr1->code = code;
    ptr1->name = name;
    ptr1->price = price;
    ptr1->amount = amount;
    ptr1->share_held = share_held;
    ptr1->prev = NULL;
    ptr1->next = front;
    if (front == NULL)
        end = ptr1;
    else
        front->prev = ptr1;
    front = ptr1;
}

void Doubly_Linked_List::forwawrd_print()
{
    struct Node *temp = front;
    cout << endl;
    while (temp != NULL)
    {
        cout << temp->code << " "
             << temp->name << " "
             << temp->price << " "
             << temp->amount << " "
             << temp->share_held << endl;
        temp = temp->next;
    }
}

void Doubly_Linked_List::backward_print()
{
    Node *temp;
    temp = end;
    while (temp != NULL)
    {
        cout << temp->code << " "
             << temp->name << " "
             << temp->price << " "
             << temp->amount << " "
             << temp->share_held << endl;
        temp = temp->prev;
    }
}

void Doubly_Linked_List::bubbleSort1()
{
    int swapped;
    struct Node *ptr1;
    struct Node *lptr = NULL;

    if (front == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = front;

        while (ptr1->next != lptr)
        {
            if (atoi(ptr1->code.c_str()) > atoi(ptr1->next->code.c_str()))
            {
                swap(ptr1->code, ptr1->next->code);
                swap(ptr1->name, ptr1->next->name);
                swap(ptr1->price, ptr1->next->price);
                swap(ptr1->amount, ptr1->next->amount);
                swap(ptr1->share_held, ptr1->next->share_held);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void Doubly_Linked_List::bubbleSort2()
{
    int swapped;
    struct Node *ptr1;
    struct Node *lptr = NULL;

    if (front == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = front;

        while (ptr1->next != lptr)
        {
            if (ptr1->amount - ptr1->price * ptr1->share_held > ptr1->next->amount - ptr1->next->price * ptr1->next->share_held)
            {
                swap(ptr1->code, ptr1->next->code);
                swap(ptr1->name, ptr1->next->name);
                swap(ptr1->price, ptr1->next->price);
                swap(ptr1->amount, ptr1->next->amount);
                swap(ptr1->share_held, ptr1->next->share_held);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

int main()
{
    ifstream infile;
    infile.open("stock.txt");
    string str, code, name;
    double price, amount;
    int held;
    Doubly_Linked_List list1, list2;
    stringstream ss;
    while (getline(infile, str))
    {
        ss << str;
        ss >> code >> name >> price >> amount >> held;
        list1.insertAtTheBegin(code, name, price, amount, held);
        list2.insertAtTheBegin(code, name, price, amount, held);

        ss.str("");
        ss.clear();
    }

    list1.bubbleSort1();
    list2.bubbleSort2();

    int option;
    cout << "1. print by code forward" << endl
         << "2. print by code backward" << endl
         << "3. print by gain forward" << endl
         << "4. print by code backward" << endl;
    cin >> option;
    if (option == 1)
        list1.forwawrd_print();
    else if (option == 2)
        list1.backward_print();
    else if (option == 3)
        list2.forwawrd_print();
    else if (option == 4)
        list2.backward_print();

    return 0;
}