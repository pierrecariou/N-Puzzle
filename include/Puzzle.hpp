#pragma once

#include <vector>
#include <string>

class Puzzle
{
private:
	unsigned char size;
	std::vector<std::vector<unsigned char>> tiles;
	std::pair<unsigned char, unsigned char> emptyTile;

	enum Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	bool canMove(Direction direction);
	Puzzle move(Direction direction);

public:
	Puzzle(unsigned char size = 3);
	Puzzle(std::vector<unsigned char> const &tiles);

	std::string toString() const;

	unsigned char getSize() const;
	std::vector<std::vector<unsigned char>> getTiles() const;
	std::vector<Puzzle> getMoves();

	bool operator==(Puzzle const &other) const;
};
