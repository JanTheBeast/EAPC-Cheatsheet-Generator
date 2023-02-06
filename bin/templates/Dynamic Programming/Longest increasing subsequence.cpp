#include <vector>
#include <algorithm>

int table[100001];
int values[100001];

int long_inc_subseq(std::vector<int> nums)
{
	std::vector<int> dp;
	for (int i : nums) 
    {
        // To have longest non-decreasing subsequence use std::upper_bound()
		int pos = std::lower_bound(dp.begin(), dp.end(), i) - dp.begin();
		if (pos == dp.size()) dp.push_back(i);
		else dp[pos] = i;
	}

	return dp.size();
}