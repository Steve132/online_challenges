#include<iostream>
#include<iterator>
#include<fstream>
#include<vector>

struct Instruction
{
	enum 
	{
		OP_ADD=1,
		OP_MUL=2,
		OP_END=99
	};
	int op;
	int addr1;
	int addr2;
	int dst;
	Instruction():op(0),addr1(0),addr2(0),dst(0)
	{}
};
std::istream& operator>>(std::istream& inp,Instruction& inst)
{
	char comma;
	int vals[3]={0,0,0};
	inp >> inst.op;
	if(!inp.good()) return inp;
	for(int i=0;i<3;i++)
	{ 
		if(inp.good()) inp >> comma >> vals[i];
	}
	inst.addr1=vals[0];inst.addr2=vals[1];inst.dst=vals[2];
	inp >> comma;
	if(!inp.good()) { inp.clear();}
	return inp;
}
std::ostream& operator<<(std::ostream& out,const Instruction inst)
{
	return out << inst.op << ":" << inst.addr1 << ":" << inst.addr2 << ":" << inst.dst;
}
bool execute(int* data,Instruction inst)
{
	switch(inst.op)
	{
	case Instruction::OP_ADD:
		data[inst.dst]=data[inst.addr1]+data[inst.addr2];break;
	case Instruction::OP_MUL:
		data[inst.dst]=data[inst.addr1]*data[inst.addr2];break;
	default:
		std::cerr << "Unrecognized opcode: " << inst.op << std::endl;
	case Instruction::OP_END:
		return false;
	};
	return true;	
}
struct Program
{
public:
	std::vector<Instruction> instructions;
	int* vn_array() { return reinterpret_cast<int*>(instructions.data()); }

	int operator()(int noun,int verb) 
	{
		std::vector<Instruction> old=instructions;
		vn_array()[1]=noun;vn_array()[2]=verb;
		for(size_t i=0;i < instructions.size() && execute(vn_array(),instructions[i]);i++);
		int result=vn_array()[0];
		instructions=old;
		return result;
	}
};
std::istream& operator>>(std::istream& inp,Program& prog)
{
	auto be=std::istream_iterator<Instruction>(inp);
	auto ed=std::istream_iterator<Instruction>();

	prog.instructions=std::vector<Instruction>(be,ed);
	return inp;
}
int main(int argc,char** argv)
{
	std::ifstream infile("../day2.in");
	Program p;
	infile >> p;

	for(int n=0;n<1000;n++)
	for(int v=0;v<100;v++)
	{
		int r=p(n,v);
		if(r==19690720)
		{
			std::cout << n << ',' << v << std::endl;
		}
	}
	return 0;
}
