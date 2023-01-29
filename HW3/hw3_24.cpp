#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
using namespace std;
class point
{
public:
    int x, y;
    int dir;

    point(int i, int j, int k)
    {
        x = i;
        y = j;
        dir = k;
    }
};
int **road;

int findExit(vector<vector<int>> maze, int x, int y, int lenx, int leny)
{
    int i = x, j = y;
    stack<point> route;
    point current(i, j, 0);
    route.push(current);
    road[j][i] = 1;
    cout << "(" << j << ", " << i << ")" << endl;

    int dir;
    while (!route.empty())
    {
        current = route.top();
        current.dir++;
        route.pop();
        route.push(current);
        dir = current.dir;
        i = current.x;
        j = current.y;
        if (i == 0 || i == lenx - 1 || y == 0 || y == leny - 1)
            return 1;
        if (dir == 1)
        {
            if (i + 1 < lenx && maze[j][i + 1] == 0 && road[j][i + 1] == 0)
            {
                point path(i + 1, j, 0);
                road[j][i + 1] = 1;
                route.push(path);
                cout << "(" << j << ", " << i + 1 << ")" << endl;
            }
        }
        else if (dir == 2)
        {
            if (j + 1 < leny && maze[j + 1][i] == 0 && road[j + 1][i] == 0)
            {
                point path(i, j + 1, 0);
                road[j + 1][i] = 1;
                route.push(path);
                cout << "(" << j + 1 << ", " << i << ")" << endl;
            }
        }
        else if (dir == 3)
        {
            if (i - 1 >= 0 && maze[j][i - 1] == 0 && road[j][i - 1] == 0)
            {
                point path(i - 1, j, 0);
                road[j][i - 1] = 1;
                route.push(path);
                cout << "(" << j << ", " << i - 1 << ")" << endl;
            }
        }
        else if (dir == 4)
        {
            if (j - 1 >= 0 && maze[j - 1][i] == 0 && road[j - 1][i] == 0)
            {
                point path(i, j - 1, 0);
                road[j - 1][i] = 1;
                route.push(path);
                cout << "(" << j - 1 << ", " << i << ")" << endl;
            }
        }
        else
        {
            route.pop();
            if (route.empty())
                return 0;
            current = route.top();
            cout << "(" << current.y << ", " << current.x << ")" << endl;
        }
    }

    return 0;
}

int main()
{
    ifstream infile;
    infile.open("HW3_24_inputFile.txt");
    vector<vector<int>> maze(1);
    string str;
    int i = 0, x;
    while (getline(infile, str))
    {
        maze.resize(i + 1);
        stringstream ss(str);
        while (ss >> x)
            maze[i].push_back(x);
        i++;
    }
    int start_x, start_y, lenx = maze[0].size(), leny = maze.size();


    road = new int *[lenx];
    for (i = 0; i < lenx; i++)
        road[i] = new int[leny];
    for (int i = 0; i < leny; i++)
        for (int j = 0; j < lenx; j++)
            road[i][j] = 0;


    cout << "Please input entrance spot : ";
    cin >> start_y >> start_x;
    if (start_x < 0 || start_y < 0 || start_x >= lenx || start_y >= leny)
        cout << "Invalid input";
    else if (maze[start_y][start_x])
        cout << "Invalid input";
    else
    {
        if (findExit(maze, start_x, start_y, lenx, leny))
            ;
        else
            cout << "Unable to reach";
    }
    return 0;
}