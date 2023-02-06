#include <vector>
#include <string>
#include <climits>
#include <queue>

struct Edge
{
    int target;
    int weight;
};

struct Node
{
    std::vector<Edge> adj;
    int dist = INT_MAX;
    int parent;
};

struct NodeDist
{
    int ind, dist;
    NodeDist(int i, int d)
    :ind(i),dist(d){}
};

bool operator<(NodeDist a, NodeDist b)
{
    return a.dist > b.dist;    
}

Node V[10001];

void dijkstra(int start)
{
    std::priority_queue<NodeDist> Q;
    V[start].dist = 0;
    V[start].parent = -1;
    Q.push(NodeDist(start, 0));
    while (!Q.empty())
    {
        NodeDist nd = Q.top(); Q.pop();
        int k = nd.ind;
        int d = nd.dist;
        if(V[k].dist < d) continue;
        for(Edge e: V[k].adj)
        {
            int new_dist = d + e.weight;
            if(new_dist < V[e.target].dist)
            {
                V[e.target].dist = new_dist;
                V[e.target].parent = k;
                Q.push(NodeDist(e.target, new_dist));
            }
        }
    }
}