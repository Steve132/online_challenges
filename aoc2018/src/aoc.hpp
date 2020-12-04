#ifndef AOC_HPP
#define AOC_HPP

#include<memory>
#include<iosfwd>

namespace aoc
{
	std::shared_ptr<std::istream> load_input(const std::string& name,int argc,char** argv);
}

#endif
