#include <iostream>
#include <vector>

struct Edge
{
    int target;
    int capacity;
    int flow;
    Edge* back;

    Edge(int t, int c)
    :target(t), capacity(c){}
};

struct Node
{
    std::vector<Edge*> adj;
    bool visited = false;
    Edge* parent;
    int flow;
};

Node V[500];

int augment(int i, int t)
{
    if(V[i].visited) return 0;
    V[i].visited = true;
    if(i == t) return INT_MAX;
    for(Edge* e : V[i].adj) {
        if(e->capacity - e->flow <= 0) continue;
        int f = augment(e->target, t);
        if(f > 0) {
            f = std::min(f, e->capacity - e->flow);
            V[e->target].parent = e->back;
            return f;
        }
    }
    return 0;
}

int max_flow(int s, int t, int n)
{
    int total_flow = 0;
    for(int i = 0; i < n; i++)
    {
        for(Edge* e : V[i].adj) e->flow = 0;
    }

    while(true)
    {
        for(int i = 0; i < n; i++)
        {
            V[i].visited = false; V[i].parent = nullptr;
        }

        int flow = augment(s, t);
        if(flow == 0) break;
        total_flow += flow;
        int x = t;
        while(x != s)
        {
            V[x].parent->flow -= flow;
            V[x].parent->back->flow += flow;
            x = V[x].parent->target;
        }
    }
    
    return total_flow;
}

int main()
{
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;

    for(int i = 0; i < n; i++)
    {
        V[i].adj.clear();
        V[i].visited = false;
    }

    for(int i = 0; i < m; i++)
    {
        int a, b, c;
        std::cin >> a >> b >> c;
        Edge* e1 = new Edge(b, c);
        // Zero if directed
        Edge* e2 = new Edge(a, 0);
        e1->back = e2;
        e2->back = e1;
        V[a].adj.push_back(e1);
        V[b].adj.push_back(e2);
    }

    std::cout << max_flow(s, t, n);

    return 0;
}