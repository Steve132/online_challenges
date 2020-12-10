#include<iterator>
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<vector>
#include<unordered_map>
#include<map>
#include<sstream>
#include<unordered_set>
#include<numeric>
#include<utility>
#include<tuple>
#include<optional>


uint64_t ways_to_get_to(const std::vector<int>& joltages)
{
	std::vector<uint64_t> ways_count(joltages.back()+1,0);
	ways_count[0] = 1;
	for (size_t i = 0; i < joltages.size(); i++)
	{
		int J = joltages[i];
		for (int j = J - 1; j >= 0 && j >= J-3; j--)
		{
			ways_count[J] += ways_count[j];
		}
		std::cout << J << ":" << ways_count[J] << std::endl;
	}
	return 0;
}



int main(int argc, char** argv)
{
	std::ifstream inp("../inputs/day10a.in");

	std::vector<int> joltages((std::istream_iterator<int>(inp)), std::istream_iterator<int>());
	std::sort(joltages.begin(), joltages.end());
	joltages.push_back(joltages.back() + 3);

	ways_to_get_to(joltages);
	return 0;
}