#include "Grid.hpp"

#include <fstream>
#include <iostream>
#include <ostream>

int main(int argc, char *argv[])
{
	if (argc < 2) return 1;

	std::ifstream file(argv[1]);

	if (!file.is_open()) {
		std::cerr << "Failed to open the file." << std::endl;
		return 1;
	}

	int rows = 0;
	int cols;
	std::string line;
	while (std::getline(file, line)) {
		rows++;
		if (rows == 1) cols = line.length();
	}
	file.clear();
	file.seekg(0, std::ios::beg);

	Grid grid = Grid(rows, cols);

	int i = 0;
	int j = 0;
	while (std::getline(file, line)) {
		for (char c : line) grid.setChar(i, j++, c);
		i++;
		j = 0;
	}

	grid.print();

	int sumPartNumbers = 0;
	for (Number number : grid.getNumbers()) {
		if (number.isPartNumber(grid))
			sumPartNumbers += number.getNumber();
	}

	std::cout << "Sum of part numbers: " << sumPartNumbers << std::endl;

	int gearRatioSum = grid.gearRatioSum();
	std::cout << "Sum of gear ratios:  " << gearRatioSum << std::endl;

	file.close();

	return 0;
}
