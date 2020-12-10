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


void subsequence_finder(int64_t target,const std::vector<int64_t>& allnums)
{
	std::vector<int64_t> sum_nums;
	std::partial_sum(allnums.begin(), allnums.end(), std::back_inserter(sum_nums));
	for (size_t j = 1; j < sum_nums.size(); j++)
	{
		for (size_t i = 0; i < j; i++)
		{
			if((sum_nums[j] - sum_nums[i]) == target && (j-i) > 1)
			{
				std::cout << "Found: " << allnums[i + 1] << "-" << allnums[j] << std::endl;
				auto be = allnums.begin() + i + 1; auto ed = allnums.begin() + j+1;
				auto mne = *std::min_element(be, ed);
				auto mxe = *std::max_element(be, ed);
				std::cout << "min: " << mne << std::endl;
				std::cout << "max: " << mxe << std::endl;
				std::cout << "tot: " << mne + mxe << std::endl;
			}
		}
	}
}


int main(int argc, char** argv)
{
	std::ifstream inp("../inputs/day9a.in");

	std::vector<int64_t> allnums((std::istream_iterator<int64_t>(inp)), std::istream_iterator<int64_t>());
	//subsequence_finder(756008079, allnums);
	subsequence_finder(756008079, allnums);

	return 0;
}