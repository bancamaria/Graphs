#include <iostream>
#include <list>
#include <stack>
#include <climits>
#define INF INT_MAX
using namespace std;

class adjListNode
{
    int v, w;
public:
    adjListNode(int vertex, int weight){v = vertex; w = weight;}
    int getV() {return v;}
    int getW() {return w;}
};


class Graph
{
    int V;
    list<adjListNode>*adj;
    void topologicalSortUtil(int v, bool vis[], stack<int>&Stack);
public:
    Graph(int V);
    void addEdge(int u, int v, int w);
    void shortestPath(int s);
};


Graph::Graph(int V) {
    this->V = V;
    adj = new list<adjListNode>[V];
}
void Graph::addEdge(int u, int v, int w){
    adjListNode node(v, w);
    adj[u].push_back(node); // add v to u's list
}
void Graph::topologicalSortUtil(int v, bool vis[], stack<int>&Stack){
    vis[v] = true; //current node is visited
    list<adjListNode>::iterator i; // recur for all the vertices adjacent to this vertex
    for(i = adj[v].begin(); i != adj[v].end(); ++i){
            adjListNode node = *i;
            if(!vis[node.getV()])
                topologicalSortUtil(node.getV(), vis, Stack);
    }
    Stack.push(v);
}


// SHORTEST PATH FROM GIVEN VERTEX
void Graph::shortestPath(int s){
    stack<int>Stack;
    int dist[V];
    bool *visited = new bool[V]; // mark all vertices as not visited
    for(int i = 0; i < V; i++)
        if(!visited[i])
        topologicalSortUtil(i, visited, Stack);

    // set source as 0 and the rest of vertices infinite
    dist[s] = 0;
    for(int i = 0; i < V; i++)
        dist[i] = INF;

    // process vertices in topological order
    while(Stack.empty() == false){
        int u = Stack.top(); // get the next element
        Stack.pop();

        list<adjListNode>::iterator i; // update distances of all adjacent vertices
        if(dist[u] != INF){
            for(int i = adj[u].begin(); i != adj[u].end(); ++i)
                if(dist[i->getV()]) > dist[u] + i->getW();
                    dist[i->getV()] = dist[u] + i->getW();
        }
    }

    for(int i = 0; i < n; i++)
        if(dist[i] == INF) cout << "INF ";
            else cout << dist[i] << " ";
}

int main()
{
    Graph g(6);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 3, 6);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 4, 4);
    g.addEdge(2, 5, 2);
    g.addEdge(2, 3, 7);
    g.addEdge(3, 4, -1);
    g.addEdge(4, 5, -2);

    int s = 1;
    cout << "Following are shortest distances from source " << s <<" n";
    g.shortestPath(s);

    return 0;
}





