#include<iostream>
#include "aoc.hpp"
#include <iterator>
#include <algorithm>
#include <numeric>
#include <cstdint>

int main(int argc,char** argv)
{
	system("pwd");
	auto input=aoc::load_input("day1",argc,argv);

	int current_frequency=std::accumulate((std::istream_iterator<int>(*input)),
						  std::istream_iterator<int>(),
						  0);
	
	std::cout << "The current frequency is: " << current_frequency << std::endl;
	
	return 0;
}
