#include<iostream>
#include<fstream>
#include<iterator>
#include<algorithm>

struct bitstring{
	size_t bits;
	size_t length;

	bool operator[](size_t i) const{
		return (bits >> i) & 1;
	}
	struct bitwriter{
		bitstring& parent;
		size_t loc;
		operator bool(){ return parent[loc];}
		bitwriter& operator=(bool b){
			size_t msk=size_t(1) << loc;
			if(b) { parent.bits |= msk; }
			else  { parent.bits &= ~msk; }
			return *this;
		}
	};
	bitwriter operator[](size_t i){
		return bitwriter{*this,i};
	}
};

std::istream& operator>>(std::istream& inp,bitstring& bs) {
	std::string data;
	inp>>data;
	bitstring tmp{0,data.size()};
	for(size_t i=0;i<data.size();i++){
		tmp[i]=data[data.size()-i-1]=='1';
	}
	bs=tmp;
	return inp;
}
std::ostream& operator<<(std::ostream& inp,const bitstring& bs) {
	for(size_t i=0;i<bs.length;i++) {
		inp << (bs[bs.length-i-1] ? '1' : '0');
	}
	return inp;
}

int main(int argc,char** argv) {
	//Lets do this the hard way where it actually
	//does it streaming.

	std::ifstream infile("../input3.in");
	auto beg=std::istream_iterator<bitstring>(infile);
	auto end=std::istream_iterator<bitstring>();
	std::vector<size_t> counts;
	size_t total;
	std::for_each(beg,end,[&counts,&total](const bitstring& bs){
		if(counts.size() < bs.length) {
			counts.resize(bs.length,0);
		}
		for(unsigned i = 0; i < bs.length; i++) {
			counts[i]+=bs[i];
		}
		total++;
		std::cout << bs << std::endl;
	});
	bitstring most_common{0,counts.size()};
	for(unsigned i=0;i<counts.size();i++) {
		most_common[i] = (2*counts[i]) > total;
	}
	std::cout << most_common << std::endl;
	size_t least_common= (~most_common.bits) & ((size_t(1) << most_common.length)-1);
	std::cout << least_common << std::endl;
	std::cout << "the product:" << (most_common.bits * least_common) << std::endl;
    return 0;
}
