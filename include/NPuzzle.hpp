#pragma once

#include <memory>
#include <utility>
#include <vector>
#include <string>
#include <unordered_map>

#include "Direction.hpp"


class NPuzzle {
 public:
	static constexpr int cost = 1;

	NPuzzle();
	NPuzzle(std::string inputFile);
	NPuzzle(int puzzleSize);
	NPuzzle(NPuzzle const &currentState, int parentIndex, Direction direction);

	NPuzzle(NPuzzle const &src);
	NPuzzle &operator=(NPuzzle const &rhs);

	~NPuzzle();
	
	bool canMove(Direction const &direction) const;

	bool operator<(const NPuzzle& rhs) const;
	bool operator==(const NPuzzle& rhs) const;

	int getSize() const;
	void setSize(int size);

	std::vector<std::vector<int>> getPuzzle() const;
	void setPuzzle(std::vector<std::vector<int>> puzzle);

	//std::pair<int, int> getBlankTilePosition() const;
	//void setBlankTilePosition(std::pair<int, int> blankTilePosition);

	std::pair<int, int> getTilePosition(int tileNum) const;
	void setTilePosition(int tileNum, std::pair<int, int> tilePosition);

	int getHeuristicValue() const;
	void setHeuristicValue(int heuristicValue);

	int getF() const;
	void setF(int f);

	int getG() const;
	void setG(int g);

	int getParentIndex() const;
	void setParentIndex(int parentIndex);

	bool isSolvable() const;

	void printPuzzle() const;

 private:
	void initializeTilePositions();

	// Attributes
	int _size;
	std::vector<std::vector<int>> _puzzle;
	std::unordered_map<int, std::pair<int, int>> _tilePositions;
	int _heuristicValue;
	int _g;
	int _f;
	int _parentIndex;
};
