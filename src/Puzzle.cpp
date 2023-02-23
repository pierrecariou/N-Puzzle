#include <vector>
#include <map>
#include <random>
#include <cmath>

#include "Puzzle.hpp"

bool Puzzle::canMove(Direction direction)
{
	switch (direction)
	{
	case UP:
		return emptyTile.first != 0;
	case DOWN:
		return emptyTile.first != size - 1;
	case LEFT:
		return emptyTile.second != 0;
	case RIGHT:
		return emptyTile.second != size - 1;
	}
	return false;
}

Puzzle Puzzle::move(Direction direction)
{
	Puzzle result = *this;
	switch (direction)
	{
	case UP:
		result.emptyTile.first--;
		break;
	case DOWN:
		result.emptyTile.first++;
		break;
	case LEFT:
		result.emptyTile.second--;
		break;
	case RIGHT:
		result.emptyTile.second++;
		break;
	}
	std::swap(result.tiles[emptyTile.first][emptyTile.second], result.tiles[result.emptyTile.first][result.emptyTile.second]);
	return result;
}

Puzzle::Puzzle(unsigned char size) : size(size)
{
	std::vector<unsigned char> tiles(size * size);
	std::iota(tiles.begin(), tiles.end(), 1);
	tiles.back() = 0;

	*this = Puzzle(tiles);

	std::random_device rd;
	std::mt19937 gen(rd());

	for (unsigned int _ = 0; _ < pow(size, 4); _++)
	{
		std::vector<Puzzle> moves = getMoves();
		std::uniform_int_distribution<> dis(0, moves.size() - 1);
		*this = moves[dis(gen)];
	}
}

Puzzle::Puzzle(std::vector<unsigned char> const &tiles) : size(std::sqrt(tiles.size()))
{
	this->tiles.resize(size);
	for (unsigned char i = 0; i < size; i++)
		this->tiles[i].assign(tiles.begin() + i * size, tiles.begin() + (i + 1) * size);

	for (unsigned char y = 0; y < size; y++)
		for (unsigned char x = 0; x < size; x++)
			if (this->tiles[y][x] == 0)
				emptyTile = std::make_pair(y, x);
}

std::string Puzzle::toString() const
{
	std::string result;
	for (unsigned char y = 0; y < size; y++)
	{
		if (y != 0)
			result += "\n";
		for (unsigned char x = 0; x < size; x++)
		{
			if (x != 0)
				result += "\t";
			result += std::to_string(tiles[y][x]);
		}
	}
	return result;
}

unsigned char Puzzle::getSize() const { return size; }
std::vector<std::vector<unsigned char>> Puzzle::getTiles() const { return tiles; }
std::vector<Puzzle> Puzzle::getMoves()
{
	std::vector<Puzzle> result;
	for (auto direction : {UP, DOWN, LEFT, RIGHT})
		if (canMove(direction))
			result.push_back(move(direction));
	return result;
}

bool Puzzle::operator==(Puzzle const &other) const { return tiles == other.tiles; }
