#include<iostream>
#include<fstream>
#include<iterator>
#include<algorithm>
#include<numeric>

struct submarine_vector_t
{
	int horizontal,depth;
	submarine_vector_t operator+(const submarine_vector_t& o)
	{
		return submarine_vector_t{horizontal+o.horizontal,depth+o.depth};
	}
};
std::ostream& operator<<(std::ostream& outp,const submarine_vector_t& subvec){
	return outp << "{" << subvec.horizontal << "," << subvec.depth << "}";
}
std::istream& operator>>(std::istream& inp,submarine_vector_t& subvec){
	std::string direction;
	int amount;
	inp >> direction >> amount;
	if(direction=="forward") subvec=submarine_vector_t{amount,0};
	else if(direction=="up") subvec=submarine_vector_t{0,-amount};
	else if(direction=="down") subvec=submarine_vector_t{0,amount};
	return inp;
}

int main(int argc,char** argv) {
	//Lets do this the hard way where it actually
	//does it streaming.

	std::ifstream infile("../input2.in");
	auto beg=std::istream_iterator<submarine_vector_t>(infile);
	auto end=std::istream_iterator<submarine_vector_t>();


	submarine_vector_t total=std::accumulate(beg,end,submarine_vector_t{});

	std::cout << "The result is: " << total << " and a final result:" <<
				 total.depth*total.horizontal << std::endl;

    return 0;
}
