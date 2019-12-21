#include<iostream>
#include<iterator>
#include<fstream>
#include<vector>
#include<sstream>
#include<array>
#include<unordered_map>
#include<map>
#include<set>
#include<algorithm>

typedef std::array<int,2> point2_t;
static bool operator<(point2_t a,point2_t b)
{
	return (a[0]!=b[0]) ? (a[0] < b[0]) : (a[1] < b[1]);
}
static int manhattan(point2_t v)
{
	return std::abs(v[0])+std::abs(v[1]);
}
struct ManhattanCmp
{
bool operator()(point2_t a,point2_t b) const
{
	return manhattan(a) < manhattan(b);
}
};
class Wire
{
public:
	class Direction
	{
	public:
		point2_t dirvec;
		int amount;
	};
	
	std::map<point2_t,int> gridpoints;
};

std::istream& operator>>(std::istream& inp,Wire::Direction& wp)
{
	static const std::unordered_map<char,point2_t> rlud{{'R',{1,0}},{'L',{-1,0}},{'U',{0,1}},{'D',{0,-1}}};
	char dir;
	int amount;
	inp >> dir >> amount;
	wp.amount=amount;
	wp.dirvec=rlud.at(dir);
	return inp;
}

std::istream& operator>>(std::istream& inp,Wire& w)
{
	std::string wireline;
	std::getline(inp,wireline);
	std::transform(wireline.begin(),wireline.end(),wireline.begin(),[](char ch){ return std::isalnum(ch) ? ch : ' ';});
	std::istringstream wlstream(wireline);
	auto be=std::istream_iterator<Wire::Direction>(wlstream);
	auto ed=std::istream_iterator<Wire::Direction>();
	std::vector<Wire::Direction> directions(be,ed);
	point2_t cur={0,0};
	int curscore=0;
	for(auto dir : directions)
	{
		for(int i=0;i<dir.amount;i++)
		{
			cur[0]+=dir.dirvec[0];cur[1]+=dir.dirvec[1];
			w.gridpoints.insert(std::make_pair(cur,++curscore));
		}
	}
	return inp;
}

int main(int argc,char** argv)
{
	std::ifstream infile("../day3.in");
	Wire A,B;
	infile >> A >> B;

	std::map<point2_t,int,ManhattanCmp> intersectpts;
	std::set_intersection(A.gridpoints.begin(),A.gridpoints.end(),B.gridpoints.begin(),B.gridpoints.end(),std::inserter(intersectpts,intersectpts.end()),
	[](const std::pair<point2_t,int>& a,const std::pair<point2_t,int>& b){ return a.first < b.first; }
	);

	
	std::vector<std::pair<point2_t,int>> order(intersectpts.begin(),intersectpts.end());
	
	std::cout << "A had " << A.gridpoints.size() << std::endl;
	std::cout << "B had " << B.gridpoints.size() << std::endl;
	std::cout << "I had " << intersectpts.size() << std::endl;
	
	for(auto o : order)
	{
		std::cout << o.first[0] << "," << o.first[1] << "(" << manhattan(o.first) << ")" << "steps: " << A.gridpoints[o.first]+B.gridpoints[o.first] << std::endl;
	}

	//std::cout << order[1][0] << "," << order[1][1] << std::endl;
	
	return 0;
}
