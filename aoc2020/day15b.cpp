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




#ifdef _MSC_VER 
#include<immintrin.h>

static inline uint64_t popcnt64(uint64_t x) { return __popcnt64(x); }
static inline uint64_t pdep64(uint64_t x, uint64_t msk) {
	return _pdep_u64(x, msk);
}

#endif

struct MemCmd
{
	std::string op;
	uint64_t arg1;
	uint64_t arg2;
};

std::istream& operator>>(std::istream& inp, MemCmd& mc)
{
	std::string lhs, eq, rhs;
	inp >> lhs >> eq >> rhs;
	if (lhs.substr(0, 3) == "mem")
	{

		std::istringstream issl(lhs);
		std::istringstream issr(rhs);
		mc.op = "mem";
		issl.ignore(4);
		issl >> mc.arg1;
		issr >> mc.arg2;
	}
	else
	{
		mc.op = "mask";
		mc.arg1 = 0;
		mc.arg2 = 0;
		for (size_t i = 0; i < rhs.size(); i++)
		{
			char ch = rhs[rhs.size() - 1 - i];
			if (ch == 'X')	//arg1 = floatmask
			{
				mc.arg1 |= ((uint64_t)1) << i;
			}
			else if (ch == '1')
			{
				mc.arg2 |= ((uint64_t)1) << i;
			}
		}
	}
	return inp;
}

using Program = std::vector<MemCmd>;
struct Machine
{
public:
	uint64_t currfloat = 0;
	uint64_t currsets = 0;
	std::unordered_map<uint64_t, uint64_t> memory;
	static const uint64_t REGMASK = (((uint64_t)1) << 36) - 1;

	void execute(const MemCmd& mc)
	{
		if (mc.op == "mem")
		{
			size_t N = ((size_t)1) << popcnt64(currfloat);
			uint64_t keep = (~(currfloat | currsets)) & REGMASK;

			uint64_t initaddr = (mc.arg1 & keep);
			for (size_t i = 0; i < N; i++)
			{
				uint64_t addr = (initaddr | pdep64(i, currfloat) | currsets) & REGMASK;
				memory[addr] = mc.arg2 & REGMASK;
			}
		}
		else if (mc.op == "mask")
		{
			currfloat = mc.arg1;
			currsets = mc.arg2;
		}
	}

	void execute(const Program& prog)
	{
		for (const MemCmd& mc : prog)
		{
			execute(mc);
		}
	}

	uint64_t sum_memory() const
	{
		uint64_t sm = 0;
		for (auto v : memory)
		{
			sm += v.second;
		}
		return sm;
	}
};

int main(int argc, char** argv)
{
	std::ifstream inp("../inputs/day14a.in");
	Program mcmds((std::istream_iterator<MemCmd>(inp)), std::istream_iterator<MemCmd>());
	Machine ms;
	ms.execute(mcmds);
	std::cout << ms.sum_memory() << std::endl;

	return 0;
}