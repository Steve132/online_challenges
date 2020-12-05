#include<iterator>
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<vector>
#include<unordered_map>
#include<map>
#include<sstream>

inline size_t decode(char ch)
{
	switch (ch)
	{
	case 'R':
	case 'B':
		return 1;
	case 'L':
	case 'F':
		return 0;
	};
	return 0;
}
inline size_t decode(const std::string& str)
{
	size_t id = 0;
	for (auto ch : str)
	{
		id <<= 1;
		id |= decode(ch);
	}
	return id;
}

class Seat
{
public:
	size_t id;
	Seat(size_t tid=0) :id(tid) {}
	Seat(const std::string& st) :Seat(decode(st)) {}
};



std::istream& operator>>(std::istream& inp, Seat& s)
{
	std::string inv;
	inp >> inv;
	s = Seat(inv);
	return inp;
}


int main(int argc, char** argv)
{
	std::ifstream inp("../inputs/day5a.in");
	auto zm = std::max_element((std::istream_iterator<Seat>(inp)), std::istream_iterator<Seat>(),
		[](const Seat& a,const Seat& b)
		{
			return a.id < b.id;
		}
	);

	std::cout << "Max: " << zm->id << std::endl;

	return 0;
}