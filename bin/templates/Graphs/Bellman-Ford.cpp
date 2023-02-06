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

void bellmanford(int start, int N)
{
    V[start].dist = 0;
    for(int k = 0; k < N-1; k++) {
        for(int i = 0; i < N; i++) {
            for(Edge e : V[i].adj) {
                int new_dist = V[i].dist + e.weight;
                if(new_dist < V[e.target].dist) {
                    V[e.target].dist = new_dist;
                    V[e.target].parent = i;
                }
            }
        }
    }

    // To find negative cycles, run another iteration
    // if any distance change, negative cycle found
}