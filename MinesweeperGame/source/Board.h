#pragma once
#include <string>
#include "Tile.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <map>

using namespace std;
class Board
{
	int numColumns, numRows, configNumMines;
	vector<vector<Tile>> board;
	int numFlagsPlaced;
	bool isDebug = false;
	sf::Sprite faceBtn, mineBtn, Test1Btn, Test2Btn, Test3Btn;
	sf::Sprite hundreds, tens, ones, negSign;
	int counter;
	bool isNegative=false;
	bool isGameOver;
	bool playerLost;
	bool playerWon;
	int numMines;


public:
	Board(string fileName);
	bool checkIfWin();
	unsigned int windowHeight();
	
	unsigned int windowWidth();
	void readBoard(string fileName); \
	void createButtons();
	void drawButtons(sf::RenderWindow& myWindow);
	void readConfigFile(string fileName);
	Tile findTile(int column, int row);
	void findAdjacentTiles(int row, int column);
	void setTile(int x, int y);
	void revealMineTiles();

	
	void drawBoard(sf::RenderWindow& myWindow);
	void drawCounter(sf::RenderWindow& myWindow);
	void createBoard();
	void UpdateCounter();
	int GetCount();
	void setAllAdjacentTiles();
	void addFlag();
	int GetFlagCount();
	void RemoveFlag();
	bool checkBoardMouseEvents(sf::Event::MouseButtonEvent mouseEvent);
	bool checkButtonEvents(sf::Event::MouseButtonEvent mouseEvent);

};

