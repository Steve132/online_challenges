#include<iostream>
#include "aoc.hpp"
#include <iterator>
#include <algorithm>
#include <unordered_set>

bool check_letter_count_n(const std::string& s,int n)
{
	std::unordered_multiset<char> sset(s.begin(),s.end());
	for(char ch : s)
	{
		if(sset.count(ch)==n) return true;
	}
	return false;
}


int main(int argc,char** argv)
{
	auto input=aoc::load_input("day2",argc,argv);
	std::vector<std::string> all_ids((std::istream_iterator<std::string>(*input)),
									 std::istream_iterator<std::string>());
	
	std::cout << "Count 3:" << std::count_if(all_ids.begin(),all_ids.end(),[](const std::string& s)
	{
		return check_letter_count_n(s,3);
	});
	std::cout << "Count 2:" << std::count_if(all_ids.begin(),all_ids.end(),[](const std::string& s)
	{
		return check_letter_count_n(s,2);
	});
	return 0;
}
