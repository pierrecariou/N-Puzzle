#pragma once

#include <vector>
#include <utility>
#include <memory>
#include <ostream>

class Puzzle
{
private:
	unsigned char size;
	std::vector<unsigned char> tiles;
	std::pair<unsigned char, unsigned char> emptyTile;

	enum class Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	std::unique_ptr<Puzzle> move(Direction direction) const;

public:
	Puzzle(unsigned char size = 3);
	Puzzle(std::vector<unsigned char> tiles);

	unsigned char getSize() const;
	std::vector<unsigned char> getTiles() const;
	std::vector<Puzzle> getMoves() const;

	bool operator==(Puzzle const &other) const;
	friend std::ostream &operator<<(std::ostream &os, const Puzzle &puzzle);
};
