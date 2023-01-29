#include <iostream>
#include <vector>
#include <list>
#include <utility> 
#include <fstream>
using namespace std;

const int Max_Distance = 1000;
class Graph_SP{            
private:
    int num_vertex;
    vector<list<pair<int,int>>> AdjList;
    vector<int> predecessor, distance;
public:
    Graph_SP():num_vertex(0){};
    Graph_SP(int n):num_vertex(n){
        AdjList.resize(num_vertex);
    }
    void AddEdge(int from, int to, int weight);
    void resize(int size);

    void Relax(int X, int Y, int weight);    
    int BellmanFord(int Start, int end);        
};

int Graph_SP::BellmanFord(int Start, int end){

    distance.resize(num_vertex);
    predecessor.resize(num_vertex);

    for (int i = 0; i < num_vertex; i++) {
        distance[i] = Max_Distance;
        predecessor[i] = -1;
    }
    distance[Start] = 0;

    for (int i = 0; i < num_vertex-1; i++) {                
        for (int j = 0 ; j < num_vertex; j++) {             
            for (list<pair<int,int> >::iterator itr = AdjList[j].begin();
                 itr != AdjList[j].end(); itr++) {          
                Relax(j, (*itr).first, (*itr).second);
            }
        }
    }

    return distance[end];
}


void Graph_SP::Relax(int from, int to, int weight){

    if (distance[to] > distance[from] + weight) {
        distance[to] = distance[from] + weight;
        predecessor[to] = from;
    }
}
void Graph_SP::AddEdge(int from, int to, int weight){
    resize(from);
    resize(to);
    AdjList[from-1].push_back(std::make_pair(to-1,weight));
    AdjList[to-1].push_back(std::make_pair(from-1,weight));
}

void Graph_SP::resize(int size)
{
    if (size > AdjList.size())
    {
        AdjList.resize(size);
        num_vertex = size;
    }
    
}

int main(){

    Graph_SP g;
    ifstream infile;
    infile.open("graph.txt");
    int from, to, weight;
    while (infile >> from >> to >> weight)
    {
        g.AddEdge(from, to, weight);
    }

    int start, end;
    cout << "請輸入起點城市 : ";
    while (cin >> start)
    {
        cout << "請輸入終點城市 : ";
        cin >> end;
        cout << "最短距離為 : " << g.BellmanFord(start-1, end-1) << endl;
        cout << "------------------\n";
        cout << "請輸入起點城市 : ";
    }

    return 0;
}