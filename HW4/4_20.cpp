#include <fstream>
#include <iostream>
#include <queue>
#include <regex>
#include <sstream>
using namespace std;
void prefixCalculation(queue<string> &);
bool isValid(string, string, string);
string calculate(string, string, string);
void printAnswer(string);

int main(int argc, char **argv)
{
    ifstream inf;
    inf.open(argv[1]);
    queue<string> q1;
    string str;
    int counter = 0;
    while (getline(inf, str))
    {
        counter++;
        stringstream ss;
        ss << str;
        while (ss >> str)
            q1.push(str);
        cout << "case " << counter << ": ";
        prefixCalculation(q1);
    }

    inf.close();
}

void prefixCalculation(queue<string> &q)
{
    string ope, str_a, str_b, result;
    queue<string> q2, tmp;
    stringstream ss;
    double answer;
    while (q.size() > 0)
    {
        tmp = q;
        if (q.size() == 1 && q2.size() == 0)
        {
            ss << q.front();
            ss >> answer;
            cout << answer << endl;
            return;
        }
        else if (q.size() <= 2 && q2.size() > 0)
        {
            q2.push(q.front());
            q.pop();
        }
        else
        {
            ope = q.front();
            q.pop();
            str_a = q.front();
            q.pop();
            str_b = q.front();
            q.pop();
            // cout << ope << " " << str_a << " " << str_b << endl;
            if (isValid(ope, str_a, str_b))
            {
                result = calculate(ope, str_a, str_b);
                q2.push(result);
            }
            else
            {
                q2.push(ope);
                tmp.pop();
                q = tmp;
            }
        }
        if (q.size() == 0)
        {
            prefixCalculation(q2);
        }
    }
}

bool isValid(string s1, string s2, string s3)
{
    if (s1 == "+" || s1 == "-" || s1 == "*" || s1 == "/")
        if (regex_match(s2, regex("^(-?\\d+)(\\.\\d+)?$")))
            if (regex_match(s3, regex("^(-?\\d+)(\\.\\d+)?$")))
                return true;
    return false;
}

string calculate(string ope, string str_a, string str_b)
{
    double a = 0, b = 0, result = 0;
    stringstream ss;
    ss << (str_a + " " + str_b);
    ss >> a;
    ss >> b;

    if (ope == "+")
        result = a + b;
    else if (ope == "-")
        result = a - b;
    else if (ope == "*")
        result = a * b;
    else if (ope == "/")
        result = a / b;
    string n;
    n = to_string(result);

    return n;
}

void printAnswer(string)
{

}