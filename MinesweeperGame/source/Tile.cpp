#include "Tile.h"
#include "TextureManager.h"
#include "Board.h"
Tile::Tile(bool _isMine) {
	isMine = _isMine;
	isFlagged = false;
	isRevealed = false;
	numAdjacentMines = 0;
	mySprite = sf::Sprite(TextureManager::GetTexture("tile_hidden"));
}
Tile::Tile() {
	isMine = false;
	isFlagged = false;
	isRevealed = false;
	numAdjacentMines = 0;
	mySprite = sf::Sprite(TextureManager::GetTexture("tile_hidden"));
}

int Tile::GetNumAdjacentMines() {
	return numAdjacentMines;
}

void Tile::addAdjacentTile(Tile* aTile) {
	adjacentTiles.push_back(aTile);
}
void Tile::IncrementAdjacentMines() {
	numAdjacentMines++;
}
bool Tile::GetIsFlagged() {
	return isFlagged;
}

bool Tile::GetIsMine() {
	return isMine;
}

bool Tile::GetIsRevealed() {
	return isRevealed;
}

void Tile::SetFlag(bool _isFlagged) {
	isFlagged = _isFlagged;
}
void Tile::SetMine(bool _isMine) {
	isMine = _isMine;
}
void Tile::drawTile(sf::RenderWindow &myWindow, bool isDebug) {
	mySprite.setTexture(TextureManager::GetTexture("tile_hidden"));
	myWindow.draw(mySprite);
	if (isRevealed) {
		mySprite.setTexture(TextureManager::GetTexture("tile_revealed"));
		myWindow.draw(mySprite);
	}
	if (isDebug&&isMine) {
		mySprite.setTexture(TextureManager::GetTexture("mine"));
		myWindow.draw(mySprite);
	}
	if (isMine&& isRevealed) {
	
		mySprite.setTexture(TextureManager::GetTexture("mine"));
		myWindow.draw(mySprite);
	}
	if (isFlagged) {
		mySprite.setTexture(TextureManager::GetTexture("flag"));
		myWindow.draw(mySprite);
	}
	else if (isRevealed && !isMine){
		switch (numAdjacentMines) {
		case 1:
			mySprite.setTexture(TextureManager::GetTexture("number_1"));
			break;
		case 2: 
			mySprite.setTexture(TextureManager::GetTexture("number_2"));
			break;
		case 3:
			mySprite.setTexture(TextureManager::GetTexture("number_3"));
			break;
		case 4:
			mySprite.setTexture(TextureManager::GetTexture("number_4"));
			break;
		case 5:
			mySprite.setTexture(TextureManager::GetTexture("number_5"));
			break;
		case 6:
			mySprite.setTexture(TextureManager::GetTexture("number_6"));
			break;
		case 7:
			mySprite.setTexture(TextureManager::GetTexture("number_7"));
			break;
		case 8:
			mySprite.setTexture(TextureManager::GetTexture("number_8"));
			break;
		case 0:
			//reveal all neighboring tiles that are NOT revealed, NOT mines, and NOT flagged.
			break;
		}
		myWindow.draw(mySprite);
	}
	
	
}

void Tile::RevealTiles() {
	if (!isFlagged && !isRevealed) {
		isRevealed = true;
		if (numAdjacentMines == 0) {
			for (Tile* aTile : adjacentTiles)
				aTile->RevealTiles();
		}
	}
	
}
void Tile::SetRevealed(bool _isRevealed) {
	isRevealed = _isRevealed;
}

void Tile::placeTile(int x, int y) {
	mySprite.setPosition(x, y);
}
bool Tile::checkMouseEvent(sf::Event::MouseButtonEvent mouseEvent) {
	//check if mouse clicked on this tile 
	if (!mySprite.getGlobalBounds().contains(mouseEvent.x, mouseEvent.y))
		return false;
	//success mouse clicked on this. 
	if (isRevealed)
		return true;

	if (mouseEvent.button == sf::Mouse::Right) {
		if (isFlagged) {
			isFlagged = false;
		}
		else {
			isFlagged = true;
		}
			
	}
		
	if (mouseEvent.button == sf::Mouse::Left && !isFlagged)
		RevealTiles();
	return true;
}


 

			
	
