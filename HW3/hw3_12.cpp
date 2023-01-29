#include <fstream>
#include <iostream>
#include <stack>
#include <string.h>
using namespace std;
bool findUnpaired(string a)
{
    stack<int> s;
    int line = 1;
    bool valid = 1;
    for (int i = 0; i < a.length(); i++)
    {
        if (a[i] == '\n')
            line++;
        if (a[i] == '{')
            s.push(line);
        else if (a[i] == '}')
        {
            if (s.empty())
            {
                cout << "closing brace in line " << line << " is unmatched" << endl;
                valid = false;
            }
            else
                s.pop();
        }
    }

    while (!s.empty())
    {
        line = s.top();
        cout << "opening brace in line " << line << " is unmatched" << endl;
        s.pop();
        valid = false;
    }
    return valid;
}

int main()
{
    string filename;
    cout << "Please input a file name : " << endl;
    cin >> filename;
    ifstream infile;
    infile.open(filename);
    string content{
        istreambuf_iterator<char>(infile),
        istreambuf_iterator<char>()};
    if (findUnpaired(content))
        cout << "Valid" << endl;

    return 0;
}