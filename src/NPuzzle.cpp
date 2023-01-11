#include "NPuzzle.hpp"

#include <cctype>
#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include <iomanip>
#include <utility>
#include <vector>
#include <random>

NPuzzle::NPuzzle() : _size(0), _puzzle(), _tilePositions(), _heuristicValue(0), _f(0), _g(0), _parent(nullptr)
{
	std::random_device randomDevice;

	std::mt19937 generator(randomDevice());

	std::uniform_int_distribution<int> distribution(3, 17);

	_size = distribution(generator);

	int nums[_size * _size];

	for (int i = 0; i < _size * _size; i++) {
		nums[i] = i;
	}

	for (int i = 0; i < _size * _size; i++) {
		int j = rand() % (_size * _size);
		int temp = nums[i];
		nums[i] = nums[j];
		nums[j] = temp;
	}

	for (int i = 0; i < _size; i++) {
		std::vector<int> row;
		for (int j = 0; j < _size; j++) {
			row.push_back(nums[i * _size + j]);
		}
		_puzzle.push_back(row);
	}

	initializeTilePositions();
}

NPuzzle::NPuzzle(std::string inputFile) : _parent(nullptr)
{
	std::ifstream file(inputFile);
	std::string line;

	if (file.is_open())
	{
		std::getline(file, line);
		if (line.size() != 1 || !isdigit(line[0]))
		{
			std::cout << "Error: Invalid size in inputFile" << std::endl;
			file.close();
			exit(1);
		}
		this->_size = stoi(line);
		while (getline(file, line))
		{
			std::stringstream ss(line);
			std::string number;
			std::vector<int> row;
			while (getline(ss, number, ' '))
			{
				for (size_t i = 0; i < number.size(); i++)
				{
					if (!isdigit(number[i]))
					{
						std::cout << "Error: Invalid puzzle in inputFile" << std::endl;
						file.close();
						exit(1);
					}
				}
				row.push_back(stoi(number));
			}
			if (row.size() != this->_size) {
				std::cout << row.size() << std::endl;
				std::cout << "Error: Invalid puzzle in inputFile" << std::endl;
				file.close();
				exit(1);
			}
			this->_puzzle.push_back(row);
		}
		file.close();
	}
	else {
		std::cout << "Unable to open file" << std::endl;
		exit(1);
	}
	if (this->_puzzle.size() != this->_size)
	{
		std::cout << "Error: Invalid puzzle in inputFile" << std::endl;
		exit(1);
	}

	this->initializeTilePositions();
}

NPuzzle::NPuzzle(int puzzleSize) : _parent(nullptr)
{
	this->_size = puzzleSize;
	for (int i = 0; i < this->_size; i++)
	{
		std::vector<int> row;
		for (int j = 0; j < this->_size; j++)
		{
			row.push_back((i * this->_size) + j + 1);
		}
		this->_puzzle.push_back(row);
	}
	this->_puzzle[this->_size - 1][this->_size - 1] = 0;
	this->initializeTilePositions();
}

NPuzzle::NPuzzle(NPuzzle const &currentState, Direction direction) : _parent(std::make_unique<NPuzzle>(currentState))
{
	this->_size = currentState._size;
	this->_puzzle = currentState._puzzle;
	int blankTileRow = currentState.getTilePosition(0).first;
	int blankTileColumn = currentState.getTilePosition(0).second;
	int temp;

	switch (direction)
	{
		case UP:
			temp = this->_puzzle[blankTileRow - 1][blankTileColumn];
			this->_puzzle[blankTileRow - 1][blankTileColumn] = 0;
			this->_puzzle[blankTileRow][blankTileColumn] = temp;
			break;
		case DOWN:
			temp = this->_puzzle[blankTileRow + 1][blankTileColumn];
			this->_puzzle[blankTileRow + 1][blankTileColumn] = 0;
			this->_puzzle[blankTileRow][blankTileColumn] = temp;
			break;
		case LEFT:
			temp = this->_puzzle[blankTileRow][blankTileColumn - 1];
			this->_puzzle[blankTileRow][blankTileColumn - 1] = 0;
			this->_puzzle[blankTileRow][blankTileColumn] = temp;
			break;
		case RIGHT:
			temp = this->_puzzle[blankTileRow][blankTileColumn + 1];
			this->_puzzle[blankTileRow][blankTileColumn + 1] = 0;
			this->_puzzle[blankTileRow][blankTileColumn] = temp;
			break;
		case END:
			break;
	}
	this->initializeTilePositions();
}

NPuzzle::~NPuzzle()
{
}

NPuzzle::NPuzzle(NPuzzle const &src)
{
	*this = src;
}

NPuzzle &NPuzzle::operator=(NPuzzle const &rhs)
{
	if (this != &rhs)
	{
		this->_size = rhs._size;
		this->_puzzle = rhs._puzzle;
		this->_tilePositions = rhs._tilePositions;
		this->_heuristicValue = rhs._heuristicValue;
		this->_g = rhs._g;
		this->_f = rhs._f;
		if (rhs._parent)
			this->_parent = std::make_unique<NPuzzle>(*rhs._parent);
	}
	return (*this);
}

void NPuzzle::initializeTilePositions()
{
	for (int i = 0; i < this->_size; i++) {
		for (int j = 0; j < this->_size; j++)
			this->_tilePositions[this->_puzzle[i][j]] = {i, j};
	}
}

bool NPuzzle::canMove(const Direction &direction) const
{
	int blankTileRow = this->getTilePosition(0).first;
	int blankTileColumn = this->getTilePosition(0).second;

	switch (direction)
	{
		case UP:
			if (blankTileRow == 0)
				return false;
			break;
		case DOWN:
			if (blankTileRow == this->_size - 1)
				return false;
			break;
		case LEFT:
			if (blankTileColumn == 0)
				return false;
			break;
		case RIGHT:
			if (blankTileColumn == this->_size - 1)
				return false;
			break;
		case END:
			return false;
			break;
	}
	return true;
}

bool NPuzzle::operator<(const NPuzzle &rhs) const
{
	//std::cout << "operator<" << std::endl;
	return (this->_f < rhs._f);
}

bool NPuzzle::operator==(const NPuzzle &rhs) const
{
	return (this->_puzzle == rhs._puzzle);
}

int NPuzzle::getSize() const
{
	return  this->_size;
}

void NPuzzle::setSize(int size)
{
	this->_size = size;
}

std::vector<std::vector<int>> NPuzzle::getPuzzle() const
{
	return this->_puzzle;
}

void NPuzzle::setPuzzle(std::vector<std::vector<int>> puzzle)
{
	this->_puzzle = puzzle;
}

std::pair<int, int> NPuzzle::getTilePosition(int tile) const
{
	return this->_tilePositions.at(tile);
}

void NPuzzle::setTilePosition(int tile, std::pair<int, int> position)
{
	this->_tilePositions[tile] = position;
}

int NPuzzle::getHeuristicValue() const
{
	return this->_heuristicValue;
}

void NPuzzle::setHeuristicValue(int heuristicValue)
{
	this->_heuristicValue = heuristicValue;
}

void NPuzzle::setF(int f)
{
	this->_f = f;
}

int NPuzzle::getF() const
{
	return this->_f;
}

int NPuzzle::getG() const
{
	return this->_g;
}

void NPuzzle::setG(int g)
{
	this->_g = g;
}

NPuzzle* NPuzzle::getParent() const
{
	return this->_parent.get();
}

void NPuzzle::setParent(std::unique_ptr<NPuzzle> parent)
{
	this->_parent = std::move(parent);
}

bool NPuzzle::isSolvable() const
{
	int inversions = 0;
	std::vector<int> linearizedPuzzle;

	for (int i = 0; i < this->_size; i++) {
		for (int j = 0; j < this->_size; j++)
			linearizedPuzzle.push_back(this->_puzzle[i][j]);
	}
	for (int i = 0; i < linearizedPuzzle.size(); i++) {
		for (int j = i + 1; j < linearizedPuzzle.size(); j++) {
			if (linearizedPuzzle[i] && linearizedPuzzle[j] && linearizedPuzzle[i] > linearizedPuzzle[j])
				inversions++;
		}
	}
	if (this->_size % 2 == 0) {
		if (inversions % 2 == 0)
			return true;
		else
			return false;
	}
	else {
		if (inversions % 2 == 0)
			return true;
		else
			return false;
	}
}

void NPuzzle::printPuzzle() const
{
	for (int i = 0; i < this->_size; i++)
	{
		for (int j = 0; j < this->_size; j++)
				std::cout << std::setw(4) << this->_puzzle[i][j] << " ";
		std::cout << std::endl;
	}
}
