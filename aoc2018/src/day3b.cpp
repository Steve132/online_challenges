#include<iostream>
#include "aoc.hpp"
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <set>
#include <utility>

class Claim
{
public:
	size_t id;
	size_t x,y,w,h;
};

std::istream& operator>>(std::istream& inp,Claim& claim)
{
	char sep; //#123 @ 3,2: 5x4
	inp >> sep >> claim.id >> sep >> claim.x >> sep >> claim.y >> sep >> claim.w >> sep >> claim.h;
	return inp;
}

class Fabric
{
public:
	size_t width,height;
private:
	//slower, but whatever
	std::vector<size_t> patches;
	size_t index(size_t x,size_t y) const
	{
		return x*height+y;
	}
public:

	Fabric(size_t w,size_t h):width(w),height(h),patches(w*h,0)
	{}
	size_t count(size_t x,size_t y) const
	{
		return patches[index(x,y)];
	}
	void add(size_t x,size_t y)
	{
		if(x < width && y < height) patches[index(x,y)]++;
	}
	void add(const Claim& claim) //overload
	{
		for(size_t i=0;i<claim.w;i++)
		for(size_t j=0;j<claim.h;j++)
		{
			add(claim.x+i,claim.y+j);
		}
	}
	size_t count_overlaps(size_t x,size_t y,size_t w,size_t h) const
	{
		size_t noverlaps=0;
		for(size_t i=0;i<w;i++)
		for(size_t j=0;j<h;j++)
		{
			if(count(x+i,y+j) > 1)
			{
				noverlaps++;
			}
		}
		return noverlaps;
	}
	size_t count_overlaps() const
	{
		return count_overlaps(0,0,width,height);
	}
};

int main(int argc,char** argv)
{
	auto input=aoc::load_input("day3",argc,argv);
	std::vector<Claim> all_claims((std::istream_iterator<Claim>(*input)),
									 std::istream_iterator<Claim>());
	
	Fabric fabric(1000,1000);
	for(const Claim& claim : all_claims)
	{
		fabric.add(claim);
	}
	
	for(const Claim& claim : all_claims)
	{
		if(fabric.count_overlaps(claim.x,claim.y,claim.w,claim.h)==0)
		{
			std::cout << "Doesn't overlap: " << claim.id << std::endl;
		}
	}

	return 0;
}
