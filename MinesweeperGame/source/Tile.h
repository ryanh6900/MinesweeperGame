#pragma once
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;
class Tile
{
	sf::Sprite mySprite;
	string tileType;
	bool isFlagged;
	bool isMine;
	bool isRevealed;
	vector<Tile*> adjacentTiles;
	int numAdjacentMines;
	int numFlags = 0;

public:
	Tile(bool isMine);
	Tile();
	void placeTile(int x, int y);
	void SelectImage(bool isDebug = false);
	/*sf::Sprite GetSprite();*/
	bool GetIsMine();
	bool GetIsFlagged();
	bool GetIsRevealed();
	void SetMine(bool _isMine);
	void SetFlag(bool _isFlagged);
	void SetRevealed(bool _isRevealed);
	void drawTile(sf::RenderWindow& myWindow, bool isDebug = false);
	void RevealTiles();
	bool checkMouseEvent(sf::Event::MouseButtonEvent mouseEvent/*,*//* int numFlags*/);
	void addAdjacentTile(Tile* aTile);
	int GetNumAdjacentMines();
	void IncrementAdjacentMines();
	
};

