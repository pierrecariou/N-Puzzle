#pragma once

#include <vector>
#include <memory>

class Puzzle
{
private:
	unsigned char size;
	std::vector<unsigned char> tiles;
	std::pair<unsigned char, unsigned char> emptyTile;

	enum Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	bool canMove(Direction direction) const;
	std::unique_ptr<Puzzle> move(Direction direction) const;

public:
	Puzzle(unsigned char size = 3);
	Puzzle(std::vector<unsigned char> tiles);

	unsigned char getSize() const;
	std::vector<unsigned char> const &getTiles() const;
	std::vector<std::unique_ptr<Puzzle>> getMoves() const;

	bool operator==(Puzzle const &other) const;
};
