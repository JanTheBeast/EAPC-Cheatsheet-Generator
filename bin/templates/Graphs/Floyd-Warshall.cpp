#include <utility>

int d[100][100];
int N, M;

void floydwarshall()
{
    for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                // Overflow possible
                d[i][j] = 1000000000;
        
    for(int i = 0; i < N; i++) d[i][i] = 0;

    // Set d[a][b] to weight of edge a--b
    for(int i = 0; i < M; i++) 

    // Floyd-warshall
    for(int k = 0; k < N; k++)
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
}