#include <iostream>
#include <queue>
#include <list>
#include <stack>
using namespace std;

class Graph{
    int V;
    list<int>*adj;
    void TSrec(int v, bool vis[], stack<int>&stackk);
    void DFSrec(int v, bool vis[]);
public:
    Graph (int V);
    void addEdge(int v, int w);
    void TS();
    void DFS();
};

Graph::Graph(int V){
    this -> V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w){
    adj[v].push_back(w);
}

void Graph::TSrec(int v, bool vis[], stack<int>&stackk){
    vis[v] = true;
    list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i){
        if(!vis[*i])
            TSrec(*i, vis, stackk);
        stackk.push(v);
    }
}

void Graph::DFSrec(int v, bool vis[]){
    // set current node as visited
    vis[v] = true;
    cout << v << " ";
    // recursive for all adj nodes
    list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i)
        if(!vis[*i])
            DFSrec(*i, vis);
}

void Graph::DFS(){
    bool *vis = new bool[V];
    for(int i = 0; i < V; ++i)
        vis[i] = false;
    for(int i = 0; i < V; ++i)
        if(!vis[i])
            DFSrec(V, vis);
}

int main()
{
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
    cout << "TS starting from ";
    g.DFS();
    return 0;
}
