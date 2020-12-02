#include<iterator>
#include<iostream>
#include<fstream>
#include<unordered_set>

int main(int argc, char** argv)
{
	std::ifstream inp("../inputs/day1a.in");
	std::unordered_set<std::int64_t> all_items((std::istream_iterator<std::int64_t>(inp)), std::istream_iterator<std::int64_t>());
	auto z = *std::find_if(all_items.begin(), all_items.end(), [&all_items](std::int64_t x)
		{
			return all_items.count(2020 - x) > 0;
		});
	std::cout << z * (2020ULL - z) << std::endl;
	return 0;
}