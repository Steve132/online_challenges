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


class PassengerGroup
{
public:
	std::unordered_set<char> allanswers;
};

std::istream& operator>>(std::istream& inp, PassengerGroup& p)
{
	std::string line;
	p = PassengerGroup();
	std::cout << "Begin Group" << std::endl;
	while(std::getline(inp,line))
	{
		if (line.size() == 0) break;
		std::cout << line << std::endl;
		p.allanswers.insert(line.begin(), line.end());
	}
	return inp;
}


int main(int argc, char** argv)
{
	std::ifstream inp("../inputs/day6a.in");
	std::vector<PassengerGroup> allgroups((std::istream_iterator<PassengerGroup>(inp)), std::istream_iterator<PassengerGroup>());
	std::cout << "N:" << allgroups.size() << std::endl;
	size_t count = std::accumulate(allgroups.begin(), allgroups.end(),0,
		[](size_t s, const PassengerGroup& pg)
		{
			return s + pg.allanswers.size();
		});
	std::cout << "Total sum:" << count << std::endl;

	
	return 0;
}