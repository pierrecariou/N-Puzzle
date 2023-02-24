#include "Puzzle.hpp"

#include <vector>
#include <random>

bool Puzzle::canMove(Direction direction) const
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

std::unique_ptr<Puzzle> Puzzle::move(Direction direction) const
{
	std::unique_ptr<Puzzle> result(new Puzzle(*this));

	switch (direction)
	{
	case UP:
		result.get()->emptyTile.first--;
		break;
	case DOWN:
		result.get()->emptyTile.first++;
		break;
	case LEFT:
		result.get()->emptyTile.second--;
		break;
	case RIGHT:
		result.get()->emptyTile.second++;
		break;
	}

	std::swap(result.get()->tiles[emptyTile.first + emptyTile.second * size], result.get()->tiles[result.get()->emptyTile.first + result.get()->emptyTile.second * size]);
	return result;
}

Puzzle::Puzzle(unsigned char size)
{
	std::vector<unsigned char> tiles(size * size);
	std::iota(tiles.begin(), tiles.end(), 1);
	tiles.back() = 0;

	*this = Puzzle(tiles);

	std::random_device rd;
	std::mt19937 gen(rd());

	for (unsigned int _ = 0; _ < std::pow(size, 5); _++)
	{
		const std::vector<std::unique_ptr<Puzzle>> &moves = getMoves();
		std::uniform_int_distribution<> dis(0, moves.size() - 1);
		*this = *moves[dis(gen)];
	}
}

Puzzle::Puzzle(std::vector<unsigned char> tiles) : size(std::sqrt(tiles.size())), tiles(tiles)
{
	for (unsigned short i = 0; i < tiles.size(); i++)
		if (tiles[i] == 0)
		{
			emptyTile = std::make_pair(i % size, i / size);
			break;
		}
}

unsigned char Puzzle::getSize() const { return size; }
std::vector<unsigned char> const &Puzzle::getTiles() const { return tiles; }
std::vector<std::unique_ptr<Puzzle>> Puzzle::getMoves() const
{
	std::vector<std::unique_ptr<Puzzle>> result;
	for (auto direction : {UP, DOWN, LEFT, RIGHT})
		if (canMove(direction))
			result.push_back(move(direction));
	return result;
}

bool Puzzle::operator==(Puzzle const &other) const { return tiles == other.tiles; }
