#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
int exchange_times = 0;

void Print(vector<int> &array)
{
    for (int i = 0; i < array.size(); i++)
    {
        cout << setw(2) << array[i] << " ";
    }
    cout << endl;
}

void swap(int &p1, int &p2)
{
    int temp = p1;
    p1 = p2;
    p2 = temp;
    exchange_times += 3;
}

void reheap(vector<int> &array, int root, int length)
{

    int left = 2 * root,
        right = 2 * root + 1,
        largest;

    if (left <= length && array[left] > array[root])
        largest = left;
    else
        largest = root;

    if (right <= length && array[right] > array[largest])
        largest = right;

    if (largest != root)
    {
        swap(array[largest], array[root]);
        reheap(array, largest, length);
    }
}

void HeapSort(vector<int> &array)
{
    for (int i = (int)array.size() / 2; i >= 1; i--)
    {
        reheap(array, i, (int)array.size() - 1);
    }

    int size = (int)array.size() - 1;
    for (int i = (int)array.size() - 1; i >= 1; i--)
    {
        swap(array[0], array[i]);
        size--;
        reheap(array, 0, size);
    }
}

int main()
{

    vector<int> array = {47, 80, 42, 37, 45, 4, 52, 39, 65, 32, 54, 71, 82, 20, 99, 55, 30, 96, 2, 56};

    cout << "Unsorted array: ";
    Print(array);

    HeapSort(array);

    cout << "Sorted array:   ";
    Print(array);

    cout << "Total exchange times: " << exchange_times << endl;

    return 0;
}