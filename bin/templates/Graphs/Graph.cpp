#include <iostream>
#include <vector>

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

Node V[10001];

void read_edge()
{
    int n, d, c;
    std::cin >> n >> d >> c;
    for(int i = 0; i < d; i++)
    {
        int a, b, s;
        std::cin >> a >> b >> s;
        V[b].adj.push_back({a, s});
    }
}