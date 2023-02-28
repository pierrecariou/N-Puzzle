#include "Puzzle.hpp"

#include <numeric>
#include <random>
#include <fstream>

std::unique_ptr<Puzzle> Puzzle::move(Direction direction)
{
	Puzzle move = *this;

	switch (direction)
	{
	case Direction::UP:
		if (emptyTile.first > 0)
			move.emptyTile.first--;
		break;
	case Direction::DOWN:
		if (emptyTile.first < size - 1)
			move.emptyTile.first++;
		break;
	case Direction::LEFT:
		if (emptyTile.second > 0)
			move.emptyTile.second--;
		break;
	case Direction::RIGHT:
		if (emptyTile.second < size - 1)
			move.emptyTile.second++;
		break;
	}

	if (move.emptyTile != emptyTile)
	{
		std::swap(move.tiles[emptyTile.first * size + emptyTile.second], move.tiles[move.emptyTile.first * size + move.emptyTile.second]);
		return std::make_unique<Puzzle>(move);
	}

	return nullptr;
}

Puzzle::Puzzle(unsigned char size) : size(size)
{
	std::vector<unsigned char> tiles(size * size);
	std::iota(tiles.begin(), tiles.end(), 1);
	tiles.back() = 0;

	*this = Puzzle(tiles);

	std::random_device rd;
	std::mt19937 g(rd());

	for (unsigned char _ = 0; _ < 100; ++_)
	{
		std::vector<Puzzle> moves = getMoves();
		std::uniform_int_distribution<> dis(0, moves.size() - 1);
		*this = moves[dis(g)];
	}
}

Puzzle::Puzzle(std::string filename)
{
	std::ifstream file(filename);
	int number;

	if (!file.is_open())
		throw std::runtime_error("Could not open file " + filename);

	file >> number;
	size = number;
	tiles.resize(size * size);

	for (unsigned char i = 0; i < size; ++i)
		for (unsigned char j = 0; j < size; ++j)
		{
			file >> number;
			tiles[i * size + j] = number;
			if (number == 0)
				emptyTile = std::make_pair(i, j);
		}

	file.close();
}

Puzzle::Puzzle(std::vector<unsigned char> tiles) : size(std::sqrt(tiles.size())), tiles(tiles)
{
	for (unsigned char i = 0; i < tiles.size(); ++i)
		if (tiles[i] == 0)
		{
			emptyTile = std::make_pair(i / size, i % size);
			break;
		}
}

bool Puzzle::isSolvable()
{
	unsigned int inversions = 0;

	for (unsigned char i = 0; i < tiles.size(); ++i)
		for (unsigned char j = i + 1; j < tiles.size(); ++j)
			if (tiles[i] > tiles[j] && tiles[j] != 0)
				inversions++;

	return (size % 2 == 1 && inversions % 2 == 0) || (size % 2 == 0 && ((emptyTile.first + inversions) % 2 == 1));
}

unsigned char Puzzle::getSize() { return size; }
std::vector<unsigned char> Puzzle::getTiles() { return tiles; }
std::vector<Puzzle> Puzzle::getMoves()
{
	std::vector<Puzzle> moves;

	for (auto direction : {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT})
	{
		std::unique_ptr<Puzzle> move = this->move(direction);
		if (move)
			moves.push_back(*move);
	}

	return moves;
}

bool Puzzle::operator==(Puzzle const &other) const { return tiles == other.tiles; }
std::ostream &operator<<(std::ostream &os, const Puzzle &puzzle)
{
	for (unsigned char i = 0; i < puzzle.size; ++i)
	{
		if (i > 0)
			os << std::endl;
		for (unsigned char j = 0; j < puzzle.size; ++j)
		{
			if (j > 0)
				os << "\t";
			os << (int)puzzle.tiles[i * puzzle.size + j];
		}
	}

	return os;
}
