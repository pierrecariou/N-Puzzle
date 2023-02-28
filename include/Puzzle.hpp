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
	std::vector<unsigned char> tiles;
	std::pair<unsigned char, unsigned char> emptyTile;

	enum class Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	std::unique_ptr<Puzzle> move(Direction direction);

public:
	Puzzle(unsigned char size = 3);
	Puzzle(std::string filename);
	Puzzle(std::vector<unsigned char> tiles);

	bool isSolvable();

	unsigned char getSize();
	std::vector<unsigned char> getTiles();
	std::vector<Puzzle> getMoves();

	bool operator==(Puzzle const &other) const;
	friend std::ostream &operator<<(std::ostream &os, const Puzzle &puzzle);
};
