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

struct Sequence
{
	std::vector<int> data;
};

std::istream& operator>>(std::istream& inp, Sequence& s)
{
	std::string line;
	std::getline(inp, line);
	std::replace(line.begin(), line.end(), ',', ' ');
	std::istringstream iss(line);
	s.data = std::vector<int>((std::istream_iterator<int>(iss)), std::istream_iterator<int>());
	return inp;
}

struct SpeakContext
{
	std::unordered_map<uint64_t, uint64_t> last_turn;
	std::unordered_map<uint64_t, uint64_t> first_turn;
	uint64_t current_turn;
	uint64_t last_number;

	bool insert(uint64_t t) //returns true if was first
	{
		last_turn[t] = current_turn;
		last_number = t;
		if (!first_turn.count(t))
		{
			first_turn[t] = current_turn;
			return true;
		}
		return false;

	}
	SpeakContext(const Sequence& seq) :current_turn(1)
	{
		for (int z : seq.data)
		{
			last_turn[z] = current_turn++;
			last_number = z;
		}
	}
	uint64_t turn()
	{
		uint64_t spoken=0;

		return last_number;
	}
};


int main(int argc, char** argv)
{
	std::ifstream inp("../inputs/day15a-t.in");
	Sequence seq;
	inp >> seq;

	SpeakContext sc(seq);
	while (sc.current_turn < 11)
	{
		std::cout << "[" << sc.current_turn << "]:" << sc.last_number << std::endl;
		sc.turn();
	}

	return 0;
}