#include<iterator>
#include<iostream>
#include<fstream>
#include<unordered_set>



int main(int argc, char** argv)
{
	std::ifstream inp("../inputs/day1a.in");
	std::unordered_set<std::int64_t> all_items((std::istream_iterator<std::int64_t>(inp)), std::istream_iterator<std::int64_t>());
	for(int64_t z1 : all_items)
	for (int64_t z2 : all_items)
	{
		int64_t z3 = 2020 - z1 - z2;
		if (z1 != z2 && all_items.count(2020 - z1 - z2))
		{
			std::cout << (z1 * z2 * z3) << std::endl;
			return 0;
		}
	}
	return 0;
}