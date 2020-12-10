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


size_t num_checker(size_t prefix, const std::vector<int64_t>& allnums)
{
	std::unordered_set<int64_t> current(allnums.begin(), allnums.begin() + prefix);

	for (size_t i = prefix; i < allnums.size(); i++)
	{
		bool valid = false;
		int64_t v = allnums[i];
		for (int64_t z : current)
		{
			if (current.count(v - z)) {
				valid = true;
			}
		}
		if (!valid) return i;

		current.erase(allnums[i - prefix]);
		current.insert(v);
	}
}


int main(int argc, char** argv)
{
	std::ifstream inp("../inputs/day9a.in");

	std::vector<int64_t> allnums((std::istream_iterator<int64_t>(inp)), std::istream_iterator<int64_t>());
	size_t i = num_checker(25, allnums);
	std::cout << i << ":" << allnums[i] << std::endl;
	return 0;
}