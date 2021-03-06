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

struct NavCmd
{
	char action;
	int distance;
};

std::istream& operator>>(std::istream& inp, NavCmd& nc)
{
	inp >> nc.action >> nc.distance;
	return inp;
}

class Boat
{
public:
	int x, y;
	int vx,vy;
	Boat() :x(0), y(0), vx(10), vy(1)
	{}

	void step(const NavCmd& nc)
	{
		switch (nc.action)
		{
		case 'N': vy += nc.distance; break;
		case 'S': vy -= nc.distance; break;
		case 'E': vx += nc.distance; break;
		case 'W': vx -= nc.distance; break;
		case 'F': { x += vx * nc.distance; y += vy * nc.distance; break; }
		case 'R': turn(nc.distance / 90); break;
		case 'L': turn(-nc.distance / 90); break;
		default: std::cerr << "Improper cmd" << std::endl; break;
		};
	}
	void turn(int count)
	{
		count = count % 4;
		if (count < 0) count = 4 + count;
		for (int i = 0; i < count; i++)
		{
			int tx = vx;
			vx = vy;
			vy = -tx;
		}
	}
};

std::ostream& operator<<(std::ostream& outp, const Boat& b)
{
	return outp << b.x << "," << b.y << '@' << b.vx << "," << b.vy;
}

int main(int argc, char** argv)
{
	std::ifstream inp("../inputs/day12a.in");
	Boat boat;
	std::for_each((std::istream_iterator<NavCmd>(inp)), std::istream_iterator<NavCmd>(),
		[&boat](const NavCmd& nc) {
			boat.step(nc);
			std::cout << nc.action << nc.distance <<  " Ship is at: " << boat <<  std::endl;
		});
	std::cout << "Solution: " << std::abs(boat.x) + std::abs(boat.y) << std::endl;
	return 0;
}