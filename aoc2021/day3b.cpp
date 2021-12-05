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
		operator bool(){ return (parent.bits >> loc) & 1;}
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

bitstring filter_find(std::vector<bitstring> bsv,bool most)
{
	for(size_t i=0;bsv.size() != 1;i++)
	{
		for(size_t bi=0;bi<bsv.size();bi++)
		{
			//std::cout << bsv[bi] << std::endl;
		}
		size_t total=std::count_if(bsv.begin(),bsv.end(),
			[i](const bitstring& bs) {
				return bs[bs.length-i-1];
			});
		bool common=(2*total) >= bsv.size();
		common = common == most;
		bsv.erase(std::remove_if(bsv.begin(),bsv.end(),
			[i,most,common](const bitstring& bs) {
				return (bs[bs.length-i-1]!=common);
			}
		),bsv.end());

	}
	return bsv[0];
}

int main(int argc,char** argv) {
	//Lets do this the hard way where it actually
	//does it streaming.

	std::ifstream infile("../input3.in");
	auto beg=std::istream_iterator<bitstring>(infile);
	auto end=std::istream_iterator<bitstring>();
	std::vector<bitstring> alldata(beg,end);
	bitstring oxygen_rating=filter_find(alldata,true);
	bitstring co2_rating=filter_find(alldata,false);
	std::cout << "O2: " << oxygen_rating << std::endl;
	std::cout << "CO2: " << co2_rating << std::endl;
	std::cout << "Combined Rating: " << co2_rating.bits*oxygen_rating.bits << std::endl;
	return 0;
}
