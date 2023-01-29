#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

class ListNode;

class LinkedList
{
public:
    ListNode *first;
    LinkedList() : first(0){};
    void PrintList();
    void Push_back(int c, int e);
    void Delete(int x);
};

class ListNode
{
public:
    int cof;
    int exp;
    ListNode *next;
    ListNode() : cof(0), exp(0), next(0){};
    ListNode(int a, int b) : cof(a), exp(b), next(0){};

    friend class LinkedList;
};

void LinkedList::PrintList()
{

    if (first == 0)
    {
        cout << "List is empty.\n";
        return;
    }

    ListNode *current = first;
    while (current != 0)
    {
        cout << current->cof << "\t" << current->exp << endl;
        current = current->next;
    }
    cout << endl;
}

void LinkedList::Push_back(int c, int e)
{

    ListNode *newNode = new ListNode(c, e);

    if (first == 0)
    {
        first = newNode;
        return;
    }

    ListNode *current = first;
    while (current->next != 0)
    {
        current = current->next;
    }
    current->next = newNode;
}

void LinkedList::Delete(int x)
{

    ListNode *current = first,
             *previous = 0;
    for (int i = 0; i < x; i++)
    {
        previous = current;
        current = current->next;
    }

    if (current == 0)
    {
        std::cout << "There is no " << x << " in list.\n";
    }
    else if (current == first)
    {
        first = current->next;
        delete current;
        current = 0;
    }
    else
    {
        previous->next = current->next;
        delete current;
        current = 0;
    }
}

void readData(LinkedList &p, ifstream &infile)
{
    int cof = -1, exp = -1;
    string str;
    stringstream ss;
    while ((cof != 0 || exp != 0) && getline(infile, str))
    {
        ss << str;
        ss >> cof >> exp;
        if (cof != 0)
            p.Push_back(cof, exp);

        ss.str("");
        ss.clear();
    }
}

void addition(LinkedList &p1, LinkedList &p2, LinkedList &p)
{
    ListNode *current1 = p1.first, *current2 = p2.first;
    while (current1 && current2)
    {
        if (current1->exp > current2->exp)
        {
            p.Push_back(current1->cof, current1->exp);
            current1 = current1->next;
        }

        else if (current1->exp < current2->exp)
        {
            p.Push_back(current2->cof, current2->exp);
            current2 = current2->next;
        }

        else
        {
            p.Push_back(current1->cof + current2->cof, current1->exp);
            current1 = current1->next;
            current2 = current2->next;
        }
    }
    while(current1 || current2) 
    { 
        if(current1) 
        { 
            p.Push_back(current1->cof, current1->exp);
            current1 = current1->next; 
        } 
        if(current2) 
        {
            p.Push_back(current2->cof, current2->exp);
            current2 = current2->next; 
        }  
    } 
    current1 = p.first;
    int counter = 0;
    while (current1->next)
    {
        if (!current1->cof)
        {
            p.Delete(counter);
        }
        counter++;
        current1 = current1->next;
    }
}

void subtraction(LinkedList &p1, LinkedList &p2, LinkedList &p)
{
    ListNode *current1 = p1.first, *current2 = p2.first;
    while (current1 && current2)
    {
        if (current1->exp > current2->exp)
        {
            p.Push_back(current1->cof, current1->exp);
            current1 = current1->next;
        }

        else if (current1->exp < current2->exp)
        {
            p.Push_back(-1 * current2->cof, current2->exp);
            current2 = current2->next;
        }

        else
        {
            p.Push_back(current1->cof - current2->cof, current1->exp);
            current1 = current1->next;
            current2 = current2->next;
        }
    }
    while(current1 || current2) 
    { 
        if(current1) 
        { 
            p.Push_back(current1->cof, current1->exp);
            current1 = current1->next; 
        } 
        if(current2) 
        {
            p.Push_back(-1 * current2->cof, current2->exp);
            current2 = current2->next; 
        }  
    }
    current1 = p.first;
    int counter = 0;
    while (current1->next)
    {
        if (!current1->cof)
        {
            p.Delete(counter);
        }
        counter++;
        current1 = current1->next;
    }
}

int main()
{
    ifstream infile;
    infile.open("test.txt");
    LinkedList p1, p2, result;
    int option;

    readData(p1, infile);
    readData(p2, infile);

    cout << "select (1)Add or (2)Subtracts: ";
    cin >> option;
    if (option == 1)
        addition(p1, p2, result);
    else if (option == 2)
        subtraction(p1, p2, result);
    result.PrintList();
}