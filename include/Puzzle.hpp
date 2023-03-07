#pragma once

#include <vector>
#include <utility>
#include <memory>
#include <string>
#include <ostream>

class Puzzle
{
private:
	unsigned char size;
	std::vector<unsigned char> board;
	std::pair<unsigned char, unsigned char> emptyTile;

	enum Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	std::unique_ptr<Puzzle> move(Direction direction);
	bool isSolvable();

public:
	Puzzle(unsigned char size = 3);
	Puzzle(std::string filename);
	Puzzle(std::vector<unsigned char> board);

	unsigned char getSize();
	std::vector<unsigned char> getBoard();
	std::vector<Puzzle> getChildren();

	bool operator==(const Puzzle &other) const;
	friend std::ostream &operator<<(std::ostream &os, const Puzzle &puzzle);
};
