#include<iostream>
#include<fstream>
#include<iterator>
#include<algorithm>

int main(int argc,char** argv) {
	//Lets do this the hard way where it actually
	//does it streaming.

	std::ifstream infile("../input1.in");
	auto beg=std::istream_iterator<int>(infile);
	auto end=std::istream_iterator<int>();

	int prev=*(beg++);
	int total=std::count_if(beg,end,[&prev](int x){
		bool result=x > prev;
		prev=x;
		return result;
	});
	std::cout << "The total increases are: " << total << std::endl;

    return 0;
}
