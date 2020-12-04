#include<iostream>
#include "aoc.hpp"
#include <iterator>
#include <algorithm>
#include <stdexcept>

bool differs_by_one(const std::string& a,const std::string& b)
{
	if(a.size() != b.size()) 
	{
		throw std::invalid_argument("The strings must be the same size");
	}
	if(a==b) return false;
	auto m1=std::mismatch(a.begin(),a.end(),b.begin());
	auto m2=std::mismatch(m1.first+1,a.end(),m1.second+1);
	return m2.first == a.end() && m2.second == b.end();
}
int main(int argc,char** argv)
{
	auto input=aoc::load_input("day2",argc,argv);
	std::vector<std::string> all_ids((std::istream_iterator<std::string>(*input)),
									 std::istream_iterator<std::string>());
	
	for(auto& s1 : all_ids)
	for(auto& s2 : all_ids)
	{
		if(differs_by_one(s1,s2))
		{
			std::cout << s1 << "," << s2 << std::endl;
		}
	}

	return 0;
}
