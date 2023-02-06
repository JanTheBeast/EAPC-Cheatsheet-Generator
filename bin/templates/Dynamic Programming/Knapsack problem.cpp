#include <iostream>
#include <vector>

int table[1001][1001];
int weight[1001];
int value[1001];

void knapsack()
{
    int N, W;
    std::cin >> N >> W;

    for(int i = 1; i <= N; i++) std::cin >> weight[i] >> value[i];

    for(int i = 0; i <= N; ++i)
    {
        for(int w = 0; w <= W; ++w)
        {
            if(i == 0 || w == 0) table[i][w] = 0;
            else if(weight[i] > w) table[i][w] = table[i - 1][w];
            else
            {
                table[i][w] = std::max(table[i-1][w], table[i-1][w-weight[i]] + value[i]);
            }
        }
    }

    int result = table[N][W];
    
    int w = W;
    std::vector<int> stuff;
    for (int i = N; i > 0 && result > 0; i--) 
    {
        if (result == table[i-1][w]) continue;   
        else 
        {
            stuff.push_back(i);
            result -= value[i];
            w -= weight[i];
        }
    }

    std::cout << table[N][W] << std::endl;
    std::cout << stuff.size() << std::endl;
    for(int i = 0; i < stuff.size(); i++) std::cout << stuff[i] << ' ';
    std::cout << std::endl;
}