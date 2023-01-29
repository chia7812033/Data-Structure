#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;

class Grade
{
public:
    int grade;
    Grade *next;
    Grade(int x)
    {
        grade = x;
        next = 0;
    }
};

class GradeList
{
public:
    Grade *first;
    GradeList() : first(0){};
    void setfirst()
    {
        first = 0;
    }
    void PrintList(string name);
    void push_grade(double);
};

void GradeList::PrintList(string name)
{
    double total = 0;
    int counter = 0;
    if (first == 0)
    {
        cout << "List is empty.\n";
        return;
    }

    Grade *current = first;
    string s = name + " ";
    while (current != 0)
    {
        counter++;
        total += current->grade;
        s += to_string(current->grade);
        s += " ";
        current = current->next;
    }
    cout << left << setw(20) << s;
    cout << "Average: " << total / counter << endl;
}

void GradeList::push_grade(double x)
{
    Grade *newNode = new Grade(x);

    if (first == 0)
    {
        first = newNode;
        return;
    }

    Grade *current = first;
    while (current->next != 0)
    {
        current = current->next;
    }
    current->next = newNode;
}

class ListNode;

class LinkedList
{
public:
    ListNode *first;
    LinkedList() : first(0){};
    void setfirst()
    {
        first = 0;
    }
    void PrintList();
    void Push_back(ListNode);
};

class ListNode
{

public:
    string name;
    GradeList grade;
    ListNode *next;
    ListNode() : name(""), next(0) { grade.setfirst(); }
    ListNode(string a) : name(a), next(0) { grade.setfirst(); }

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
        current->grade.PrintList(current->name);
        current = current->next;
    }
    cout << endl;
}

void LinkedList::Push_back(ListNode list)
{

    ListNode *newNode = new ListNode();
    (*newNode) = list;

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

int main()
{
    ifstream infile;
    infile.open("input.txt");
    string str;
    int g;
    LinkedList list;
    int times;
    while (getline(infile, str))
    {
        ListNode student(str);
        stringstream ss;
        student.grade.setfirst();
        times = 0;
        cout << "Input " << str << "'s scores: ";
        getline(cin, str);
        ss << str;
        while (ss >> g && times < 4)
        {
            student.grade.push_grade(g);
            times++;
        }
        list.Push_back(student);
    }
    cout << endl;
    list.PrintList();
}