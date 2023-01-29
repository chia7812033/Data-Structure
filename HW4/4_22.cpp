#include <iomanip>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
void process(ifstream &inf);
class Customer
{
public:
    int number;
    int wait;
    int service;
    int arrival;
    int clock;
};

int main()
{
    ifstream inf;
    inf.open("4_22.txt");
    process(inf);
}

void process(ifstream &inf)
{
    int minute = 0, service_time, number = 0, current_wait = 0;
    bool call;
    int total_wait = 0, total_service = 0, max_size = 0, total_idle = 0;
    queue<Customer> list;
    Customer customer;
    cout << "Clock    Call     Arrival  Wait     Start    Service  Queue" << endl;
    cout << "time     number   time     time     time     time     size" << endl;
    while (inf >> call >> service_time)
    {
        if (call)
        {
            number++;
            customer.number = number;
            customer.wait = current_wait;
            total_wait += current_wait;
            customer.service = service_time;
            total_service += service_time;
            customer.arrival = minute;
            customer.clock = minute + current_wait + service_time - 1;
            current_wait += service_time;
            list.push(customer);
        }
        if (!list.empty() && list.front().clock == minute)
        {
            // cout << left << setw(9) << list.front().arrival + list.front().wait + list.front().service - 1;
            cout << left << setw(9) << minute;
            cout << left << setw(9) << list.front().number;
            cout << left << setw(9) << list.front().arrival;
            cout << left << setw(9) << list.front().wait;
            cout << left << setw(9) << minute - list.front().service + 1;
            cout << left << setw(9) << list.front().service;
            list.pop();
            cout << left << setw(9) << list.size();
            if (list.size() > max_size)
                max_size = list.size();
            cout << endl;
        }
        minute++;
        if (current_wait > 0)
            current_wait--;
        else
            total_idle++;
    }
    cout << "Total calls: " << number << endl;
    cout << "Total idle time: " << total_idle << endl;
    cout << "Total wait time: " << total_wait << endl;
    cout << "Total service time: " << total_service << endl;
    cout << "Maximum queue size: " << max_size << endl;
    cout << "Average wait time: " << 1.0 * total_wait / number << endl;
    cout << "Average service time:" << 1.0 * total_service / number << endl;
}