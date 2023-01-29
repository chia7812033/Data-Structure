#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
using namespace std;

class Node
{
public:
    char value;
    int freq;
    Node *leftchild;
    Node *rightchild;

    Node(char _val, int _freq, Node *lchild, Node *rchild)
    {
        value = _val;
        freq = _freq;
        leftchild = lchild;
        rightchild = rchild;
    }
};

map<char, int> freq;
deque<Node *> forest;

bool comp(Node *a, Node *b)
{
    return a->freq < b->freq;
}

void printCode(Node *ptr, string s, map<char, string> &code)
{
    if (ptr->leftchild == NULL || ptr->rightchild == NULL)
    {
        string a;
        a.push_back(ptr->value);
        code[a[0]] = s;
        return;
    }
    if (ptr->leftchild)
        printCode(ptr->leftchild, string(s + "0"), code);
    if (ptr->rightchild)
        printCode(ptr->rightchild, string(s + "1"), code);
}

string turnToCode(string str, map<char, string> code)
{
    int len = str.length();
    string result = "";
	char ch;
    for (int i = 0; i < len; i++)
    {
        ch = str[i];
        result += code[ch];
    }
    return result;
}

string turnToString(string str, Node *root)
{
	int len = str.length();
	Node *current = root;
    string result = "";
    for (int i = 0; i <= len; i++)
	{
		if (current->value != '#')
        {
            result += current->value;
			current = root;
        }
		if (str[i] == '0')
		{
			current = current->leftchild;
		}
		else
		{
			current = current->rightchild;
		}
	}
    return result;
}

int main()
{
    ifstream infile;
    infile.open("Hw6.txt");
    char c;
    int times;
    map<char, string> haf_code;
    while (infile >> c >> times)
        freq[c] = times;

    for (map<char, int>::iterator it = freq.begin(); it != freq.end(); it++)
        forest.push_back(new Node((*it).first, (*it).second, NULL, NULL));

    for (int i = 0; i < freq.size() - 1; i++)
    {
        sort(forest.begin(), forest.end(), comp);
        Node *a = forest.front();
        forest.pop_front();
        Node *b = forest.front();
        forest.pop_front();
        Node *parentNode = new Node('#', a->freq + b->freq, a, b);
        forest.push_back(parentNode);
    }
    printCode(forest.front(), string(""), haf_code);
	for (map<char, string>::iterator it = haf_code.begin(); it != haf_code.end(); it++)
        cout << "'" << it->first << "': " << it->second << endl; 
    infile.close();

    string str;
    getline(cin, str);
    transform(str.begin(), str.end(), str.begin(), ::toupper); 
    printf("%s\n", turnToCode(str, haf_code).c_str());
    
    getline(cin, str);
    printf("%s\n", turnToString(str, forest.front()).c_str());
    return 0;
}
