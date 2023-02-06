#include <vector>
#include <queue>

struct Edge
{
    int target;
    int weight;
};

struct Node
{
    std::vector<Edge> adj;
    bool in_tree;
};

struct NodeWeight
{
    int i, w, p;
    NodeWeight(int i, int w, int p)
    :i(i),w(w),p(p){}
};

bool operator<(NodeWeight a, NodeWeight b)
{
    return a.w > b.w; // reverse for min-heap
}

Node V[10001];

void prim(int N)
{
    std::vector<NodeWeight> L;
    std::priority_queue<NodeWeight> Q;
    for(int i = 0; i < N; i++) Q.push({i, INT_MAX, -1});

    while(!Q.empty())
    {
        NodeWeight nw = Q.top(); Q.pop();
        int k = nw.i;
        if(V[k].in_tree) continue;
        V[k].in_tree = true;
        L.push_back(nw);
        for(Edge e : V[k].adj)
        {
            if(V[e.target].in_tree) continue;
            Q.push({e.target, e.weight, k});
        }
    }
}