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



int main(int argc, char** argv)
{
	std::ifstream inp("../inputs/day10a.in");

	std::vector<int> joltages((std::istream_iterator<int>(inp)), std::istream_iterator<int>());
	std::sort(joltages.begin(), joltages.end());
	joltages.push_back(joltages.back() + 3);
	std::vector<int> joltages2;
	std::adjacent_difference(joltages.begin(), joltages.end(),std::back_inserter(joltages2));
	std::unordered_multiset<int> jsets(joltages2.begin(), joltages2.end());

	for (auto zi : jsets)
	{
		std::cout << zi << ":" << jsets.count(zi) << std::endl;
	}

	return 0;
}