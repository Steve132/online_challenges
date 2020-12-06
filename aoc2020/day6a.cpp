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
	void intersect(const std::string& ln)
	{
		std::unordered_set<char> nxt(ln.begin(), ln.end());
		std::unordered_set<char> nw;
		for (char ch : allanswers)
		{
			if (nxt.count(ch)) nw.insert(ch);
		}
		allanswers = nw;
	}
};



std::istream& operator>>(std::istream& inp, PassengerGroup& p)
{

	std::cout << "Begin Group" << std::endl;
	std::string line;
	p = PassengerGroup();
	int tot = 0;
	while(std::getline(inp,line))
	{
		if (line.size() == 0) break;
		if (tot == 0)
		{
			p.allanswers = std::unordered_set<char>(line.begin(), line.end());
		}
		else
		{
			p.intersect(line);
		}
		tot++;
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