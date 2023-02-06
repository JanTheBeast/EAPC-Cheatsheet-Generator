#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <queue>
#include <cmath>

struct Edge
{
    int target;
    int weight;
};

struct Node
{
    double x, y;
    std::vector<Edge> adj;
    std::vector<int> children;
    bool in_tree = false;
    bool visited = false;
};

struct NodeWeight
{
    int i, w, p;
    NodeWeight(int i, int w, int p)
    :i(i),w(w),p(p){}
};

bool operator<(NodeWeight a, NodeWeight b)
{
    return a.w > b.w;    
}

Node V[1000];

std::vector<NodeWeight> prim(int N)
{
    std::vector<NodeWeight> L;
    std::priority_queue<NodeWeight> Q;
    Q.push({0, INT_MAX, -1});

    while(!Q.empty())
    {
        NodeWeight nw = Q.top(); Q.pop();
        int k = nw.i;
        if(V[k].in_tree) continue;
        V[k].in_tree = true;
        if(nw.p != -1) V[nw.p].children.push_back(nw.i);
        L.push_back(nw);
        for(Edge e : V[k].adj)
        {
            if(V[e.target].in_tree) continue;
            Q.push({e.target, e.weight, k});
        }
    }

    return L;
}

void dfs(int start)
{
    if(!V[start].visited) std::cout << start << std::endl;
    V[start].visited = true;
    for(int i : V[start].children) if(!V[i].visited) dfs(i);
}

int main()
{
    int N;
    std::cin >> N;

    for(int i = 0; i < N; i++) std::cin >> V[i].x >> V[i].y;

    for(int i = 0; i < N; i++)
    {
        for(int j = i + 1; j < N; j++)
        {
            int dist = std::round(std::sqrt((V[i].x-V[j].x) * (V[i].x-V[j].x) + (V[i].y-V[j].y) * (V[i].y-V[j].y)));
            V[i].adj.push_back({j, dist});
            V[j].adj.push_back({i, dist});
        }
    }

    std::vector<NodeWeight> MST = prim(N);
    dfs(0);

    return 0;
}