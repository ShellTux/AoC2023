#include "Grid.hpp"
#include <cctype>
#include <iostream>
#include <ostream>
#include <string>

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
			Position position{i, j};

			if (position.row < 0) continue;
			if (position.row >= grid.getRows()) continue;
			if (position.col < 0) continue;
			if (position.col >= grid.getCols()) continue;

			char c = grid.getChar(position.row, position.col);

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
}

Grid::~Grid() {
	delete matrix;
}

void Grid::setChar(int row, int col, char c) {
	matrix[row * rows + col] = c;
}

char Grid::getChar(int row, int col) {
	return matrix[row * rows + col];
}

void Grid::print() {
	for (int i = 0 ; i < rows ; ++i) {
		for (int j = 0 ; j < cols ; ++j) {
			char c = getChar(i, j);
			std::cout << c;
		}
		std::cout << std::endl;
	}
}

int Grid::getRows(void) {
	return rows;
}

int Grid::getCols(void) {
	return cols;
}

std::vector<Number> Grid::getNumbers(void) {
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
