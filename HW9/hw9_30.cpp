/*
討論
reheap up 的 Big(O) 為 O(logn)
reheap down 的 Big(O) 為 O(logn)
*/
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void swap(int *x, int *y);

class Heap
{
    int *harr;     
    int capacity;  
    int heap_size; 
public:
    Heap(int capacity);
    void reheapDown(int, int &times);
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return (2 * i + 1); }
    int right(int i) { return (2 * i + 2); }
    int deleteRoot(int &times);
    void insertKey(int k);
    void insertKey_new(int k, int &times);
};

Heap::Heap(int cap)
{
    heap_size = 0;
    capacity = cap;
    harr = new int[cap];
}

void Heap::insertKey(int k)
{
    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;

    while (i != 0 && harr[parent(i)] < harr[i])
    {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}

void Heap::insertKey_new(int k, int &times)
{
    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;

    times++;
    while (i != 0 && harr[parent(i)] < harr[i])
    {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
        times++;
    }
}

int Heap::deleteRoot(int &times)
{
    if (heap_size <= 0)
        return INT_MAX;
    if (heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }

    int root = harr[0];
    harr[0] = harr[heap_size - 1];
    heap_size--;
    reheapDown(0, times);

    return root;
}

void Heap::reheapDown(int i, int &times)
{
    int l = left(i);
    int r = right(i);
    int large = i;
    if (l < heap_size && harr[l] > harr[i])
        large = l;
    if (r < heap_size && harr[r] > harr[large])
        large = r;
    times++;
    if (large != i)
    {
        swap(&harr[i], &harr[large]);
        reheapDown(large, times);
    }
}

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void readData(Heap &a, Heap &b, Heap &c, Heap &d, Heap &e)
{
    ifstream infile;
    infile.open("data.csv");
    string str;
    int n1, n2, n3, n4, n5;
    string s1, s2, s3, s4, s5;
    int i = 0;
    getline(infile, str);
    while (getline(infile, str))
    {
        if (i == 2000)
            break;
        stringstream ss;
        ss << str;
        getline(ss, s1, ',');
        getline(ss, s2, ',');
        getline(ss, s3, ',');
        getline(ss, s4, ',');
        getline(ss, s5, ',');
        n1 = atoi(s1.c_str());
        n2 = atoi(s2.c_str());
        n3 = atoi(s3.c_str());
        n4 = atoi(s4.c_str());
        n5 = atoi(s5.c_str());
        if (i < 100)
        {
            a.insertKey(n1);
            b.insertKey(n2);
            c.insertKey(n3);
            d.insertKey(n4);
            e.insertKey(n5);
        }
        else if (i < 200)
        {
            b.insertKey(n2);
            c.insertKey(n3);
            d.insertKey(n4);
            e.insertKey(n5);
        }
        else if (i < 500)
        {
            c.insertKey(n3);
            d.insertKey(n4);
            e.insertKey(n5);
        }
        else if (i < 1000)
        {
            d.insertKey(n4);
            e.insertKey(n5);
        }
        else
        {
            e.insertKey(n5);
        }
        i++;
    }
}

int main()
{
    srand(time(NULL));
    Heap a(100), b(200), c(500), d(1000), e(2500);
    readData(a, b, c, d, e);
    int up_times = 0, down_times = 0;
    int times = 300;
    for (int i = 0; i < times; i++)
    {
        e.deleteRoot(down_times);
        int n = rand() % 5000 + 1;
        e.insertKey_new(n, up_times);
    }
    cout << "reheap-up: " << up_times * 1.0 / times << endl;
    cout << "reheap-down: " << down_times * 1.0 / times;
}
