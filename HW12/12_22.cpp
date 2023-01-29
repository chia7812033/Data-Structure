#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

void print(vector<int> &v)
{
    for (int i = 0; i < v.size(); i++)
        cout << setw(2) << v[i] << " ";
    cout << endl;
}

void shellSort(vector<int> &a)
{

    int gap = a.size();
    int i = 2;
    while (gap > 1)
    {
        gap = a.size() / i;
        cout << "increment = " << a.size() << " / " << i << " = " << gap << endl;
        for (int i = gap; i < a.size(); ++i)
        {
            int tmp = a[i]; 
            int j = i;
            for (; j >= gap && tmp < a[j - gap]; j -= gap)
                a[j] = a[j - gap];
            a[j] = tmp;
        }
        i++;
        print(a);
    }
}

int main()
{
    ifstream infile("12_22_input.txt");
    int n;
    vector<int> s;
    while (infile >> n)
        s.push_back(n);

    shellSort(s);

    return 0;
}