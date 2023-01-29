#include <iostream>
using namespace std;
void fibonacci(int nthNumber)
{
    long long previousprevious, previous = 0, current = 1;
    for (int i = 0; i <= nthNumber; i++)
    {
        cout << i << "\t" << current << endl;
        previousprevious = previous;
        previous = current;
        current = previousprevious + previous;
    }
}

int main()
{
    int n;
    cout << "Enter n: ";
    cin >> n;
    if (n >= 0)
        fibonacci(n);
    else
        cout << "Error!!!" << endl;

    return 0;
}