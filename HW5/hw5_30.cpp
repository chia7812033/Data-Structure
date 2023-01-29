#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class ListNode;

class LinkedList
{
public:
    ListNode *first;
    LinkedList() : first(0){};
    void PrintList();
    void Push_front(int x);;
};

class ListNode
{
public:
    int coef;
    ListNode *next;
    ListNode() : coef(0), next(0){};
    ListNode(int a) : coef(a), next(0){};

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
        cout << current->coef;
        current = current->next;
    }
    cout << endl;
}

void LinkedList::Push_front(int x)
{

    ListNode *newNode = new ListNode(x);
    newNode->next = first;
    first = newNode;
}

void readData(LinkedList &p1, LinkedList &p2)
{
    string str, str1, str2;
    stringstream ss;
    getline(cin, str);
    int pos = str.find_first_of(" ");
    str1 = str.substr(0, pos);
    str2 = str.substr(pos + 1, str.length() - pos - 1);
    int n;
    while (str1 != "")
    {
        ss << str1.substr(0, 1);
        str1 = str1.substr(1);
        ss >> n;
        p1.Push_front(n);

        ss.str("");
        ss.clear();
    }
    while (str2 != "")
    {
        ss << str2.substr(0, 1);
        str2 = str2.substr(1);
        ss >> n;
        p2.Push_front(n);

        ss.str("");
        ss.clear();
    }
}

void addition(LinkedList &p1, LinkedList &p2, LinkedList &p)
{
    ListNode *current1 = p1.first, *current2 = p2.first;
    int carry = 0, n;
    while (current1 && current2)
    {
        n = current1->coef + current2->coef + carry;
        carry = n / 10;
        p.Push_front(n % 10);
        current1 = current1->next;
        current2 = current2->next;
    }
    while (current1 || current2)
    {
        if (current1)
        {
            n = current1->coef + carry;
            carry = n / 10;
            p.Push_front(n % 10);
            current1 = current1->next;
        }
        if (current2)
        {
            n = current2->coef + carry;
            carry = n / 10;
            p.Push_front(n % 10);
            current2 = current2->next;
        }
    }
    if (carry > 0)
        p.Push_front(carry);
}

int main()
{
    LinkedList n1, n2, result;

    readData(n1, n2); 
    addition(n1, n2, result);

    result.PrintList();
}