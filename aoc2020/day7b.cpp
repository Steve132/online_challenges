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
#include<numeric>
#include<utility>
#include<tuple>
#include<optional>


struct Bag : public std::tuple<std::string, std::string>
{
	using parent_t = std::tuple<std::string, std::string>;
	using parent_t::parent_t;
};
namespace std {
	template<> struct hash<Bag> {
		std::size_t operator()(Bag const& s) const noexcept
		{
			std::size_t h1 = std::hash<std::string>{}(std::get<0>(s));
			std::size_t h2 = std::hash<std::string>{}(std::get<1>(s));
			return h1 ^ (h2 << 1); // or use boost::hash_combine
		}
	};
}

std::istream& operator>>(std::istream& inp, Bag& b)
{
	std::string bags;
	return inp >> std::get<0>(b) >> std::get<1>(b) >> bags;
}
std::ostream& operator<<(std::ostream& outp, Bag& b)
{
	return outp << std::get<0>(b) << "_" << std::get<1>(b);
}
struct BagRule
{
	Bag src;
	std::unordered_map<Bag, unsigned int> dst_bags;
};

std::istream& operator>>(std::istream& inp, BagRule& br)
{
	std::string line="";
	br = BagRule();
	while (inp && line.size() == 0)
	{
		std::getline(inp, line);
	}
	if (!inp) return inp;
	std::istringstream inpl(line);
	std::string contains;
	inpl >> br.src >> contains;
	static const Bag no_other("no", "other");
	static const Bag blank("", "");
	while (inpl)
	{
		unsigned int amount;
		Bag dst;
		inpl >> amount >> dst;
		if(inpl && (dst != no_other) && (dst != blank)) br.dst_bags[dst] = amount;
	}
	return inp;
}


void DFS_internal(
	std::unordered_map<Bag, std::optional<unsigned int>>& hit_target,
	const std::unordered_map<Bag, BagRule>& brules,
	const Bag& current)
{
	std::optional<unsigned int>& ht = hit_target[current];
	if (ht)
	{
		return;
	}

	ht = 1;
	
	for (const auto& dst : brules.at(current).dst_bags)
	{
		DFS_internal(hit_target, brules, dst.first);
		std::optional<unsigned int>& ht2 = hit_target[dst.first];
		ht.value() += ht2.value()*dst.second;
	}
}

std::unordered_map<Bag,unsigned int> DFS(const std::vector<BagRule>& brvec,const Bag& target)
{
	std::unordered_map<Bag, BagRule> brules;
	std::unordered_map<Bag, std::optional<unsigned int>> hit_target;
	for (const auto& br : brvec) brules[br.src] = br;
	//hit_target[target] = true;

	for (const auto& br : brvec)
	{
		DFS_internal(hit_target, brules, br.src);
	}

	
	std::unordered_map<Bag, unsigned int> hit_out;
	for (const auto& h : hit_target)
	{
		hit_out[h.first] = h.second.value();
	}
	return hit_out;
}

int main(int argc, char** argv)
{
	std::ifstream inp("../inputs/day7a.in");

	std::vector<BagRule> brules((std::istream_iterator<BagRule>(inp)), std::istream_iterator<BagRule>());
	Bag target("shiny", "gold");
	auto counts=DFS(brules,target);
	
	std::cout << "Bags: " << counts[target]-1 << std::endl;
	
	return 0;
}