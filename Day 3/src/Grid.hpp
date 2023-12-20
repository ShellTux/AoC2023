#include <vector>

typedef struct {
	int row;
	int col;
} Position;

class Grid;

class Number {
public:
	Number(int startRow, int startCol, int endRow, int endCol, int number);
	Number(Number &&) = default;
	Number(const Number &) = default;
	Number &operator=(Number &&) = default;
	Number &operator=(const Number &) = default;
	~Number();
	bool isPartNumber(Grid &grid) const;
	int getNumber(void) const;
	Position getStart(void) const;
	Position getEnd(void) const;
	void print(void) const;
	void print(Grid &grid) const;
	bool operator==(const Number& other) const;
	bool operator!=(const Number& other) const;

private:
	Position start, end;
	int number;
};

class Grid {
public:
	Grid(int rows, int cols);
	Grid(Grid &&) = default;
	Grid(const Grid &) = default;
	Grid &operator=(Grid &&) = default;
	Grid &operator=(const Grid &) = default;
	~Grid();
	void setChar(int row, int col, char c);
	char getChar(int row, int col) const;
	void print(void) const;
	int getRows(void) const;
	int getCols(void) const;
	std::vector<Number> getNumbers(void) const;
	int gearRatioSum(void) const;
	bool isValidPosition(Position position) const;
	bool isValidPosition(int i, int j) const;

private:
	int rows;
	int cols;
	char *matrix;
	std::vector<Position> possibleGears{};
};
