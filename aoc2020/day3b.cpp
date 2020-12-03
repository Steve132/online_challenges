#include<iterator>
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<vector>

class SkiHill
{
public:
	std::vector<std::string> data;
	size_t width() const 
	{
		return data[0].size();
	}
	size_t height() const 
	{
		return data.size(); 
	}
	bool tree(size_t r, size_t c) const
	{
		return data[r][c] == '#';
	}
};

std::istream& operator>>(std::istream& inp, SkiHill& hill)
{
	hill.data=std::vector<std::string>((std::istream_iterator<std::string>(inp)), std::istream_iterator<std::string>());
	return inp;
}

size_t count_trees(const SkiHill& hill, int rightshift,int downshift)
{
	size_t ntrees = 0;
	size_t cx = 0;
	for (size_t r = 0; r < hill.height(); r+=downshift)
	{
		if (hill.tree(r, cx)) ntrees++;
		cx = (cx + rightshift) % hill.width();
	}
	return ntrees;
}

int main(int argc, char** argv)
{
	std::ifstream inp("../inputs/day3a.in");
	SkiHill hill;
	inp >> hill;
	size_t c = 1;
	c *= count_trees(hill, 1, 1);
	c *= count_trees(hill, 3, 1);
	c *= count_trees(hill, 5, 1);
	c *= count_trees(hill, 7, 1);
	c *= count_trees(hill, 1, 2);

	std::cout << c << std::endl;
	return 0;
}