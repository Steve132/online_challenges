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

struct BusSchedule
{
public:
	std::unordered_set<size_t> all_busses;
	size_t findnext_prod(size_t timestamp) const
	{
		size_t nxtbus = 0;
		size_t mnwait = ~(size_t)0;
		for (size_t b : all_busses)
		{
			size_t cwait = timestamp % b;
			if (cwait != 0) cwait = b - cwait;
			if (cwait < mnwait)
			{
				mnwait = cwait;
				nxtbus = b;
			}
		}
		return nxtbus*mnwait;
	}
};

std::istream& operator>>(std::istream& inp, BusSchedule& bs)
{
	while (std::isspace(inp.peek()))
	{
		inp.ignore();
	}
	std::string wholething;
	getline(inp, wholething);
	std::istringstream iss(wholething);
	std::string item;
	while (getline(iss, item,','))
	{
		if (item != "x") bs.all_busses.insert(atoll(item.c_str()));

	}
	return inp;
}


int main(int argc, char** argv)
{
	std::ifstream inp("../inputs/day13a.in");
	BusSchedule bs;
	size_t timestamp;
	inp >> timestamp >> bs;

	std::cout << "The next bus prod is: " << bs.findnext_prod(timestamp) << std::endl;

	return 0;
}