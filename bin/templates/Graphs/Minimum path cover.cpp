#include <iostream>
#include <vector>

struct Node
{
    std::vector<int> adj;
    bool visited = false;
    int match = -1;
};

Node A[100001];
Node B[100001];

bool augment(int i, int n)
{
    if(A[i].visited) return false;
    A[i].visited = true;
    for(int j : A[i].adj)
    {
        if(B[j].match == -1 || augment(B[j].match, n))
        {
            B[j].match = i;
            return true;
        }
    }

    return false;
}

int matching(int n)
{
    for(int i = 1; i <= n; i++) B[i].match = -1;
    int M = 0;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++) A[j].visited = false;
        if(augment(i, n)) M++;
    }

    return M;
}

void solution()
{
    int n, m;
    std::cin >> n >> m;

    for(int i = 1; i <= n; i++) A[i].adj.clear();

    for(int i = 0; i < m; i++)
    {
        int x, y;
        std::cin >> x >> y;
        A[x].adj.push_back(y);
    }

    std::cout << n - matching(n) << std::endl;
}