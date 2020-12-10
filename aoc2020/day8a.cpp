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


struct Instruction
{
public:
	std::string opcode;
	int arg;
	Instruction(): opcode("nop"), arg(0){}
};

std::istream& operator>>(std::istream& inp, Instruction& inst)
{
	return inp >> inst.opcode >> inst.arg;
}

struct Machine
{
public:
	size_t ip;
	int acc;
	std::vector<Instruction> program;
	std::vector<unsigned int> execution_counts;
	template<class Iter>
	Machine(Iter be, Iter ed) :ip(0),acc(0), program(be, ed),execution_counts(program.size(),0)
	{}
	void step()
	{
		const Instruction& nxt = program[ip];
		execution_counts[ip]++;
		if (nxt.opcode == "acc")
		{
			acc += nxt.arg;
		}
		else if (nxt.opcode == "jmp")
		{
			ip += nxt.arg;
			return;
		}
		ip++;
	}
	template<class Predicate>
	bool run_until(Predicate& p)
	{
		bool pred_triggered = false;
		while (ip != program.size() && !(pred_triggered=p(*this)))
		{
			step();
		}
		return pred_triggered;
	}
};


int main(int argc, char** argv)
{
	std::ifstream inp("../inputs/day8a.in");

	Machine vm((std::istream_iterator<Instruction>(inp)), std::istream_iterator<Instruction>());

	vm.run_until([](Machine& vm)
		{
			return vm.execution_counts[vm.ip] == 1;
		});

	std::cout << "Immediately before the first rep:" << vm.acc << std::endl;
	
	return 0;
}