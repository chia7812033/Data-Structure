#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>
using namespace std;

struct Edge{
    int from, to, weight;
    Edge(){};
    Edge(int u, int v, int w):from(u), to(v), weight(w){};
};

class Graph{
private:
    int num_vertex;
    vector<vector<int>> AdjMatrix;
public:
    void AddEdge(int from, int to, int weight);

    int MST();
    void GetSortedEdge(vector<struct Edge> &vec);
    friend int SetCollapsing(int *subset, int i);
    friend void UnionSet(int *subset, int x, int y);
    void resize(int size);
};
int SetCollapsing(int *subset, int i){  

    int root;  
    for (root = i; subset[root] >= 0; root = subset[root]);

    while (i != root) {
        int parent = subset[i];
        subset[i] = root;
        i = parent;
    }

    return root;
}
void UnionSet(int *subset, int x, int y){

    int xroot = SetCollapsing(subset, x),
        yroot = SetCollapsing(subset, y);

    if (subset[xroot] <= subset[yroot]) {      
        subset[xroot] += subset[yroot];
        subset[yroot] = xroot;
    }
    else {   
        subset[yroot] += subset[xroot];
        subset[xroot] = yroot;
    }
}
bool WeightComp(struct Edge e1, struct Edge e2){
    return (e1.weight < e2.weight);
}
void Graph::GetSortedEdge(vector<struct Edge> &edgearray){

    for (int i = 0; i < num_vertex-1; i++) {
        for (int j = i+1; j < num_vertex; j++) {
            if (AdjMatrix[i][j] != 0) {
                edgearray.push_back(Edge(i,j,AdjMatrix[i][j]));
            }
        }
    }
    sort(edgearray.begin(), edgearray.end(), WeightComp);
}
int Graph::MST(){

    struct Edge *edgeset = new struct Edge[num_vertex-1];
    int edgesetcount = 0;

    int subset[num_vertex];
    for (int i = 0; i < num_vertex; i++) {
        subset[i] = -1;
    }

    vector<struct Edge> increaseWeight;
    GetSortedEdge(increaseWeight);              

    for (int i = 0; i < increaseWeight.size(); i++) {
        if (SetCollapsing(subset, increaseWeight[i].from) != SetCollapsing(subset, increaseWeight[i].to)) {
            edgeset[edgesetcount++] = increaseWeight[i];
            UnionSet(subset, increaseWeight[i].from, increaseWeight[i].to);
        }
    }
    int sum = 0;
    for (int i = 0; i < num_vertex-1; i++) 
        sum += edgeset[i].weight;

    return sum;
}

void Graph::AddEdge(int from, int to, int weight){
    resize(from);
    resize(to);
    AdjMatrix[from-1][to-1] = weight;
}

void Graph::resize(int size)
{
    if (size > AdjMatrix.size())
    {
        AdjMatrix.resize(size);
        for (int i = 0; i < size; i++) 
        {
            AdjMatrix[i].resize(size);
        }
        num_vertex = size;
    }
    
}

int main(){

    Graph g;
    ifstream infile;
    string filename;
    getline(cin, filename);
    infile.open(filename);
    int from, to, weight;
    while (infile >> from >> to >> weight)
    {
        g.AddEdge(from, to, weight);
    }

    cout << g.MST();

    return 0;
}