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

bool yearCheck(const std::string& s, size_t l, size_t u)
{
	try
	{
		size_t v = stoull(s);
		return v <= u && v >= l;
	}
	catch (const std::exception&)
	{
		return false;
	}
}

class Passport
{
public:
	std::unordered_map<std::string, std::string> fields;
	bool valid() const
	{
		if (!(fields.count("byr") && fields.count("iyr") && fields.count("eyr") && fields.count("hgt") && fields.count("hcl") && fields.count("ecl") && fields.count("pid")))
		{
			return false;
		}
		if (!yearCheck(fields.at("byr"), 1920, 2002)) return false;
		if (!yearCheck(fields.at("iyr"), 2010, 2020)) return false;
		if (!yearCheck(fields.at("eyr"), 2020, 2030)) return false;
		size_t pout;
		size_t h = std::stoull(fields.at("hgt"), &pout);
		std::string hsel = fields.at("hgt").substr(pout);
		
		if (hsel == "cm")
		{
			if ((h < 150 || h > 193)) return false;
		}
		else if (hsel == "in")
		{
			if((h < 59 || h > 76)) return false;
		}
		else
		{
			return false;
		}

		std::string hcl = fields.at("hcl");
		auto ishex = [](char ch) { return (ch <= '9' && ch >= '0') || (ch >= 'a' && ch <= 'f'); };
		if (hcl.size() != 7 || hcl[0] != '#' || !std::all_of(hcl.begin()+1, hcl.end(), ishex))
		{
			return false;
		}
		static const std::unordered_set<std::string> vecl{ "amb","blu","brn","gry","grn","hzl","oth" };
		if (!vecl.count(fields.at("ecl"))) return false;
		if (!std::all_of(fields.at("pid").begin(), fields.at("pid").end(), std::isdigit)) return false;
		if (fields.at("pid").size() != 9) return false;
		return true;
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

	std::cout << all_passports.size() << std::endl;
	std::cout << "Valid: " << std::count_if(all_passports.begin(), all_passports.end(), [](const Passport& p) { return p.valid(); });
	return 0;
}