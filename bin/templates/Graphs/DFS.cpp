#include <vector>
struct Node
{
    std::vector<int> adj;
    bool visited;
};

Node V[10001];

void dfs(int i)
{
    if(V[i].visited) return;
    V[i].visited = true;
    for(int k : V[i].adj) dfs(k);
}