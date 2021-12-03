#include<iostream>
#include<fstream>
#include<iterator>
#include<algorithm>
#include<queue>

int main(int argc,char** argv) {
	//Lets do this the hard way where it actually
	//does it streaming.

	std::ifstream infile("../input1.in");
	auto beg=std::istream_iterator<int>(infile);
	auto end=std::istream_iterator<int>();

	int sum=0;
	std::queue<int> q;
	int total=std::count_if(beg,end,[&sum,&q](int x){
		int psum=sum;
		q.push(x);
		sum+=x;
		bool result=false;
		if(q.size() > 3)
		{
			sum-=q.front();
			q.pop();
			if(psum != 0) result=sum > psum;
		}
		std::cout << x << ":" << result << "(" << psum << "," << sum << ")" << std::endl;
		return result;
	});
	std::cout << "The total increases are: " << total << std::endl;

    return 0;
}
