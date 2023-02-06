#include <vector>

double area(std::vector<std::pair<int,int>> poly) 
{
    double result = 0;
    for(int i = 0; i < poly.size()-1; i++) {
        result += poly[i].first*poly[i+1].second - poly[i+1].first*poly[i].second;
    }

    return result;
}