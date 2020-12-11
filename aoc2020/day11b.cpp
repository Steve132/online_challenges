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



struct PlaneState
{
	std::vector<std::string> data2;
	std::vector<std::string> data;
	size_t columns() const { return data[0].size(); }
	size_t rows() const { return data.size(); }

	const char& operator()(int r, int c) const {
		return data[r][c];
	}
	char& operator()(int r, int c) {
		return data[r][c];
	}

	unsigned int occupiedNear(int r, int c) const {
		static const int offsets[8][2] = { {-1,-1},{-1,0},{-1,1},
											{0,-1},        {0,1},
											{1,-1}, {1,0}, {1,1} };

		unsigned int cnt = 0;
		for (int i = 0; i < 8; i++)
		{
			int nr = r+ offsets[i][0];
			int nc = c+ offsets[i][1];
			while(nr >= 0 && nr < rows() && nc >= 0 && nc < columns())
			{
				if (data[nr][nc] == '#')
				{
					cnt++;
					break;
				}
				if (data[nr][nc] == 'L')
				{
					break;
				}
				nr += offsets[i][0];
				nc += offsets[i][1];
			}
		}
		return cnt;
	}

	bool step()
	{
		bool steady = true;
		data2 = data;
		for(int r=0;r<rows();r++)
		for(int c = 0; c < columns(); c++)
		{
			unsigned int cnt = occupiedNear(r, c);
			if (data[r][c] == 'L' && cnt == 0) {
				data2[r][c] = '#'; 
				steady = false;
			}

			if (data[r][c] == '#' && cnt >= 5){
				data2[r][c] = 'L';
				steady = false;
			}
		}
		data = data2;
		return steady;
	}

	size_t occupied() const {
		size_t occ = 0;
		for (size_t i = 0; i < data.size(); i++)
		{
			occ += std::count(data[i].begin(), data[i].end(), '#');
		}
		return occ;
	}
};

std::istream& operator>>(std::istream& inp, PlaneState& ps)
{
	ps.data = std::vector<std::string>((std::istream_iterator<std::string>(inp)), std::istream_iterator<std::string>());
	return inp;
}
std::ostream& operator<<(std::ostream& outp, const PlaneState& ps)
{
	std::copy(ps.data.begin(), ps.data.end(), std::ostream_iterator<std::string>(outp, "\n"));
	return outp;
}

int main(int argc, char** argv)
{
	std::ifstream inp("../inputs/day11a.in");
	PlaneState ps;
	inp >> ps;
	for (int i = 0; !ps.step(); i++)
	{
		std::cout << "Iter " << i << std::endl;
		//std::cout << ps << std::endl;
	}
	std::cout << "Occupied:" << ps.occupied() << std::endl;

	return 0;
}