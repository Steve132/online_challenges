#include<iostream>
#include "aoc.hpp"
#include <iterator>
#include <algorithm>
#include <numeric>
#include <cstdint>
#include <unordered_set>

int main(int argc,char** argv)
{
	auto input=aoc::load_input("day1",argc,argv);

	std::vector<int> all_deltas((std::istream_iterator<int>(*input)),
						  std::istream_iterator<int>());
	std::unordered_set<int> seen;
	int current_freq=0;
	for(size_t i=0;true;i=(i+1) % all_deltas.size())
	{
		current_freq+=all_deltas[i];
		if(seen.count(current_freq))
		{
			std::cout << "Found result: " << current_freq << std::endl;
			return 0;
		}
		else
		{
			seen.insert(current_freq);
		}
	}
	
	return 0;
}
