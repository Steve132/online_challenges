#include<iostream>
#include<iterator>
#include<fstream>
#include<numeric>



int addfuel(int a,int b)
{
	int total_fuel=0;
	int resulting_fuel=b/3-2;
	while(resulting_fuel > 0)
	{
		total_fuel+=resulting_fuel;
		resulting_fuel=resulting_fuel/3-2;
	}
	return a+total_fuel;
}

int main(int argc,char** argv)
{
	std::ifstream infile("../day1.in");
	auto be=std::istream_iterator<int>(infile);
	auto ed=std::istream_iterator<int>();

	std::cout << std::accumulate(be,ed,0,addfuel) << std::endl;
	return 0;
}
