#include<iterator>
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<vector>

class Policy
{
public:
	int first,second;
	char character;
	bool valid(const std::string& pw) const
	{
		return (pw[first-1] == character) ^ (pw[second-1] == character);
	}
};

std::istream& operator>>(std::istream& inp, Policy& p)
{
	inp >> p.first;
	inp.ignore();
	inp >> p.second;
	inp >> p.character;
	return inp;
}

struct Problem
{
	Policy policy;
	std::string password;
};

std::istream& operator>>(std::istream& inp, Problem& p)
{
	inp >> p.policy;
	inp.ignore();
	inp >> p.password;
	return inp;
}

int main(int argc, char** argv)
{
	std::ifstream inp("../inputs/day2a.in");
	std::vector<Problem> all_items((std::istream_iterator<Problem>(inp)), std::istream_iterator<Problem>());
	std::cout << std::count_if(all_items.begin(), all_items.end(), [](const Problem& p) {
		return p.policy.valid(p.password);
	});
	return 0;
}