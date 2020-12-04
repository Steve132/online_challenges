#include "aoc.hpp"
#include <iostream>
#include <fstream>
#include<vector>
#include <string>

namespace aoc
{
std::shared_ptr<std::istream> load_input(const std::string& name,int argc,char** argv)
{
	std::vector<std::string> args(argv+1,argv+argc);
	if(args.size())
	{
		return std::make_shared<std::ifstream>(args[0]);
	}
	auto fr=std::make_shared<std::ifstream>((std::string("../../inputs/")+name+".in").c_str());
	if(*fr) 
	{
		return fr;
	}
	else
	{
		return std::shared_ptr<std::istream>(&std::cin,[](std::istream* p){});
	}
}
}
