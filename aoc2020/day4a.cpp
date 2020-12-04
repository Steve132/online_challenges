#include<iterator>
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<vector>
#include<unordered_map>
#include<map>
#include<sstream>

class Passport
{
public:
	std::map<std::string, std::string> fields;
	bool valid() const
	{
		return fields.count("byr") && fields.count("iyr") && fields.count("eyr") && fields.count("hgt") && fields.count("hcl") && fields.count("ecl") && fields.count("pid");
	}
};

std::istream& operator>>(std::istream& inp, Passport& p)
{
	std::string line;
	std::stringstream args;
	p = Passport();
	while(std::getline(inp,line))
	{
		if (line.size() == 0) break;
		args << line << " ";
	}
	std::vector<std::string> kvs((std::istream_iterator<std::string>(args)), std::istream_iterator<std::string>());
	for (auto kv : kvs)
	{
		size_t mp = kv.find(':');
		p.fields.emplace(kv.substr(0,mp),kv.substr(mp+1));
	}
	return inp;
}
std::ostream& operator<<(std::ostream& outp, const Passport& p)
{
	outp << "{";
	for (const auto& kv : p.fields)
	{
		outp << kv.first << ":" << kv.second << ",";
	}
	return outp << "}";
}

int main(int argc, char** argv)
{
	std::ifstream inp("../inputs/day4a.in");
	std::vector<Passport> all_passports((std::istream_iterator<Passport>(inp)), std::istream_iterator<Passport>());

	for (auto p : all_passports)
	{
		std::cout << p << "=" << p.valid() << std::endl;
	}
	std::cout << all_passports.size() << std::endl;
	std::cout << "Valid: " << std::count_if(all_passports.begin(), all_passports.end(), [](const Passport& p) { return p.valid(); });
	return 0;
}