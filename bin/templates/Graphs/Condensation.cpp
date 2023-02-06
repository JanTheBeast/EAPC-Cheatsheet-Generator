#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

struct Node
{
    std::vector<int> adj;
    std::vector<int> adj_rev;
    std::vector<int> adj_scc;
    bool used;
    bool in_scc_graph;
};

Node V[100001];
std::vector<int> order, component;

void dfs1(int v)
{
    V[v].used = true;
    for(int u : V[v].adj)
    {
        if(!V[u].used) dfs1(u);
    }

    order.push_back(v);
}

void dfs2(int v)
{
    V[v].used = true;
    component.push_back(v);

    for(int u : V[v].adj_rev)
    {
        if(!V[u].used) dfs2(u);
    }  
}

void condensation(int n)
{
    for(int i = 1; i <= n; i++)
    {
        if(!V[i].used) dfs1(i);
    }

    for(int i = 1; i <= n; i++) V[i].used = false;
    
    std::reverse(order.begin(), order.end());

    std::vector<int> roots(n+1, 0);
    std::vector<int> root_nodes;

    for(int i : order)
    {
        if(!V[i].used) 
        {
            dfs2(i);

            int root = component.front();
            for (int u : component) roots[u] = root;
            V[root].in_scc_graph = true;

            component.clear();
        }
    }

    for(int i = 1; i <= n; i++)
    {
        for(int u : V[i].adj)
        {
            int root_i = roots[i];
            int root_u = roots[u];

            if (root_u != root_i)
                V[root_i].adj_scc.push_back(root_u);
        }
    }
}

void solution()
{
    int n, m;
    std::cin >> n >> m;

    for(int i = 1; i <= n; i++) 
    {
        V[i].adj.clear();
        V[i].adj_rev.clear();
        V[i].adj_scc.clear();
        V[i].used = false;
        V[i].in_scc_graph = false;
    }

    for(int i = 0; i < m; i++)
    {
        int x, y;
        std::cin >> x >> y;
        V[x].adj.push_back(y);
        V[y].adj_rev.push_back(x);
    }

    condensation(n);
}