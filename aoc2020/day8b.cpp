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
typedef std::vector<Instruction> Program;
struct Machine
{
public:
	size_t ip;
	int acc;
	Program program;
	std::vector<unsigned int> execution_counts;
	
	Machine(const Program& prog) :ip(0),acc(0), program(prog),execution_counts(program.size(),0)
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

bool try_swap(Program p,size_t index)
{
	if (p[index].opcode == "nop")
	{
		p[index].opcode = "jmp";
	}
	else if (p[index].opcode == "jmp")
	{
		p[index].opcode = "nop";
	}
	else
	{
		return false;
	}
	Machine vm(p);
	bool did_finish=!vm.run_until([](Machine& vm)
		{
			return vm.execution_counts[vm.ip] == 1;
		});
	if (did_finish)
	{
		std::cout << "ACC: " << vm.acc << std::endl;
	}
	return did_finish;
}


int main(int argc, char** argv)
{
	std::ifstream inp("../inputs/day8a.in");

	Program prog((std::istream_iterator<Instruction>(inp)), std::istream_iterator<Instruction>());

	for (size_t i = 0; i < prog.size(); i++)
	{
		if (try_swap(prog, i))
		{
			std::cout << "Try Swap" << std::endl;
		}
	}
	
	return 0;
}