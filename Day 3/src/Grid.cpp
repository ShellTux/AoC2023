#include "Grid.hpp"
#include <cctype>
#include <iostream>
#include <ostream>
#include <string>

#define GEAR_SYMBOL '*'

Number::Number(int startRow, int startCol, int endRow, int endCol, int number) {
	start.row = startRow;
	start.col = startCol;
	end.row = endRow;
	end.col = endCol;

	this->number = number;
}

Number::~Number() {}

bool Number::isPartNumber(Grid &grid) const {
	for (int i = start.row - 1; i <= end.row + 1; ++i) {
		for (int j = start.col - 1; j <= end.col + 1; ++j) {
			if (!grid.isValidPosition(i, j)) continue;

			char c = grid.getChar(i, j);

			if ('0' <= c && c <= '9') continue;
			if (c == '.') continue;

			return true;
		}
	}

	return false;
}

int Number::getNumber(void) const {
	return number;
}

Position Number::getStart(void) const {
	return start;
}

Position Number::getEnd(void) const {
	return end;
}

void Number::print(void) const {
	std::cout
		<< "Number: " << number
		<< "; start: " << start.row << "," << start.col
		<< "; end: " << end.row << "," << end.col
		<< std::endl;
}

void Number::print(Grid &grid) const {
	std::cout
		<< "Number: " << number
		<< "; start: " << start.row << "," << start.col
		<< "; end: " << end.row << "," << end.col
		<< "; partNumber: " << isPartNumber(grid)
		<< std::endl;
}

bool Number::operator==(const Number& other) const {
	return start.row == other.start.row
		&& start.col == other.start.col
		&& end.row == other.end.row
		&& end.col == other.end.col
		&& number == other.number;
}

bool Number::operator!=(const Number& other) const {
	return !operator==(other);
}

Grid::Grid(int rows, int cols) {
	this->rows = rows;
	this->cols = cols;

	matrix = new char[rows * cols];

	possibleGears = {};
}

Grid::~Grid() {
	delete matrix;
}

void Grid::setChar(int row, int col, char c) {
	matrix[row * rows + col] = c;

	if (c == GEAR_SYMBOL) possibleGears.push_back((Position) {row, col});
}

char Grid::getChar(int row, int col) const {
	return matrix[row * rows + col];
}

void Grid::print() const {
	for (int i = 0 ; i < rows ; ++i) {
		for (int j = 0 ; j < cols ; ++j) std::cout << getChar(i, j);
		std::cout << std::endl;
	}
}

int Grid::getRows(void) const {
	return rows;
}

int Grid::getCols(void) const {
	return cols;
}

std::vector<Number> Grid::getNumbers(void) const {
	std::vector<Number> numbers{};

	for (int i = 0 ; i < rows ; ++i) {
		std::string numberString = "";
		for (int j = 0; j < cols; j++) {
			char c = getChar(i, j);

			if (!std::isdigit(c)) continue;

			int start = j;
			int length = 1;
			numberString = c;
			while (j + 1 < rows && std::isdigit((c = getChar(i, j + 1)))) {
				length++;
				j++;
				numberString += c;
			}
			numbers.push_back(Number(
						i,
						start,
						i,
						start + length -1,
						std::stoi(numberString)
						));
		}
	}

	return numbers;
}

int Grid::gearRatioSum(void) const {
	std::vector<Number> numbers = getNumbers();
	int sum = 0;

	for(Position gear : possibleGears) {
		int result = 1;
		int gearRatio = 0;

		for (int i = gear.row - 1 ; i <= gear.row + 1 ; ++i) {
			for (int j = gear.col - 1 ; j <= gear.col + 1 ; ++j) {
				if (!isValidPosition(i, j)) continue;
				if (i == gear.row && j == gear.col) continue;

				for (Number number : numbers) {
					Position start = number.getStart();
					Position end = number.getEnd();

					if (i < start.row || i > end.row) continue;
					if (j < start.col || j > end.col) continue;

					result *= number.getNumber();
					gearRatio++;
					j = end.col;
				}

			}
		}

		sum += (gearRatio == 2) * result;
	}

	return sum;
}

bool Grid::isValidPosition(Position position) const {
	return isValidPosition(position.row, position.col);
}

bool Grid::isValidPosition(int i, int j) const {
	if (i < 0 || j < 0) return false;
	if (i >= rows || j >= cols) return false;
	return true;
}
