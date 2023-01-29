#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class HashChain_std
{
private:
    int size; 
    int count;

    vector<list<pair<string, string>>> table; 

    int PreHashing(string key_str);   
    int HashFunction(string key_str); 

public:
    HashChain_std(){};
    HashChain_std(int m) : size(m)
    {
        table.resize(size);
        count = 0; 
    }

    void Insert(pair<string, string> data);
    void Search(string key);
    void DisplayTable();
    void PrintEfficiency();
};

void HashChain_std::Search(string key_str)
{
    int index = HashFunction(key_str);
    for (list<pair<string, string>>::iterator itr = table[index].begin(); itr != table[index].end(); itr++)
    {
        if ((itr->first) == key_str)
        {
            cout << "Found part number " << key_str << " at home address ";
            cout << index << ", quantity: ";
            cout << itr->second << endl;
        }
    }
}

void HashChain_std::Insert(pair<string, string> data)
{
    int index = HashFunction(data.first);
    if (table[index].empty())
        count++;
    table[index].push_front(data);
}

int HashChain_std::PreHashing(string key_str)
{
    int exp = 7, 
        key_int = 0,
        p = 1;

    for (int i = (int)key_str.size() - 1; i >= 0; i--)
    {
        key_int += key_str[i] * p;
        p *= exp;
    }
    return key_int;
}

int HashChain_std::HashFunction(string key_str)
{
    return (PreHashing(key_str) % this->size); 
}

void HashChain_std::DisplayTable()
{

    cout << "Home addr\tPrime Area\tOverflow List" << endl;
    for (int i = 0; i < table.size(); i++)
    {
        cout << setw(13) << left << i << "\t";
        int a = 0;
        for (list<pair<string, string>>::iterator itr = table[i].begin(); itr != table[i].end(); itr++)
        {
            if (a > 1)
                cout << ",";
            if (itr == table[i].begin())
                cout << (*itr).first << "/" << setw(10) << (*itr).second << "\t";
            else
                cout << (*itr).first << "/" << (*itr).second;
            a++;
        }
        cout << endl;
    }
    cout << endl;
}

void HashChain_std::PrintEfficiency()
{
    cout << "Efficiency: " << endl;
    cout << "Percentage of Prime Area Filled: " << 1.0 * count / size * 100 << "%" << endl;
    int total = 0, counter = 0, max = 0;
    for (int i = 0; i < size; i++)
    {
        if (table[i].size() > 1)
        {
            total += table[i].size() - 1;
            counter++;
            if (table[i].size() - 1 > max)
                max = table[i].size() - 1;
        }
    }
    cout << "Average nodes in linked lists: " << (1.0 * total / counter) << endl;
    cout << "Longest linked list: " << max << endl;
}

int main()
{

    ifstream infile("13_19_input.txt");
    HashChain_std hash(13);
    string n1, n2;
    while (infile >> n1 >> n2)
        hash.Insert(make_pair(n1, n2));

    int q = -1;
    while (q != 4)
    {
        cout << "Please input command: ";
        cin >> q;
        if (q == 1)
        {
            cout << "Searching: ";
            string q;
            cin >> q;
            hash.Search(q);
        }
        else if (q == 2)
        {
            hash.PrintEfficiency();
        }
        else if (q == 3)
            hash.DisplayTable();
        else if (q == 4)
            cout << "Exit Program";
    }

    return 0;
}