#include "Board.h"
#include "Tile.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureManager.h"
Board::Board(string fileName) {
    readConfigFile(fileName);
    createBoard();
    createButtons();
    
}

void Board::readConfigFile(string fileName) {
    ifstream inFile(fileName);
    if (inFile.is_open()) {
        string sNumColumns, sNumRows, sNumMines;
        getline(inFile, sNumColumns);
        getline(inFile, sNumRows);
        getline(inFile, sNumMines);
        numColumns = stoi(sNumColumns);
        numRows = stoi(sNumRows);
        configNumMines = stoi(sNumMines);
        inFile.close();
    }

}

unsigned int Board::windowWidth() {
    return numColumns * 32;
}

unsigned int Board::windowHeight() {
    return (numRows * 32) + 88;
}

void Board::createButtons() {
   faceBtn = sf::Sprite(TextureManager::GetTexture("face_happy"));
   auto buttonX = windowWidth() / 2;
   auto buttonY = windowHeight()-88;
   faceBtn.setPosition(buttonX, buttonY);
   mineBtn= sf::Sprite(TextureManager::GetTexture("debug"));
   buttonX += 128;
   mineBtn.setPosition(buttonX, buttonY);
   Test1Btn=  sf::Sprite(TextureManager::GetTexture("test_1"));
   buttonX += 64;
   Test1Btn.setPosition(buttonX, buttonY);
   Test2Btn= sf::Sprite(TextureManager::GetTexture("test_2"));
   buttonX += 64;
   Test2Btn.setPosition(buttonX, buttonY);
   Test3Btn= sf::Sprite(TextureManager::GetTexture("test_3"));
   buttonX += 64;
   Test3Btn.setPosition(buttonX, buttonY);
}

void Board::drawButtons(sf::RenderWindow& myWindow) {
    if (isGameOver) {
        if(playerLost)
            faceBtn.setTexture(TextureManager::GetTexture("face_lose"));
            revealMineTiles();
        if(playerWon) {
            faceBtn.setTexture(TextureManager::GetTexture("face_win"));
        }
    }
    else {
        faceBtn.setTexture(TextureManager::GetTexture("face_happy"));
    }
    myWindow.draw(faceBtn);
    myWindow.draw(mineBtn);
    myWindow.draw(Test1Btn);
    myWindow.draw(Test2Btn);
    myWindow.draw(Test3Btn);
}
void Board::findAdjacentTiles(int row, int column) {
    //EX: Row = 10, column =12
    //Locations of adjacent tiles are (9,12) (10,11) (9,11) (11,13)...........
   
    
    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = column - 1; j <= column + 1; j++) {
            if (i >= 0 && i < numRows && j >= 0 && j < numColumns) {
                board[row][column].addAdjacentTile(&board[i][j]);
                if (board[i][j].GetIsMine()) {
                    board[row][column].IncrementAdjacentMines();
                }
            }
           }
        }
    }
    
void Board::setAllAdjacentTiles() {
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numColumns; j++)
            findAdjacentTiles(i,j);
    }
}

void Board::readBoard(string fileName) {
    ifstream inFile(fileName);
    if (inFile.is_open()) {

        board.clear();
        for (int i = 0; i < numRows; i++)
        {
            vector <Tile> newRow;

            for (int j = 0; j < numColumns; j++)
            {
                Tile newTile;
                newTile.placeTile(j * 32, i * 32);
                newRow.push_back(newTile);
            }
            board.push_back(newRow);
        }

        numMines = 0;
        for (int i = 0; i < numRows; i++)
        {
           
            string sRow;
            getline(inFile, sRow);
            for (int j = 0; j < numColumns; j++)
            {
                if (j < sRow.size() && sRow[j] == '1') {
                    board[i][j].SetMine(true);
                    numMines++;
                }
                   
            }
        }
        UpdateCounter();
        setAllAdjacentTiles();
        inFile.close();
    }
}


void Board::createBoard() {
    board.clear();
    numMines = configNumMines;
    for (int i = 0; i < numRows; i++)
    {
        vector <Tile> newRow;
        for (int j = 0; j < numColumns; j++)
        {
            Tile newTile;
            newTile.placeTile(j * 32, i * 32);
            newRow.push_back(newTile);
        }
        board.push_back(newRow);
    }
    //add random mines.
    for (int i = 0; i < numMines; i++) {
        int randomRow = rand() % numRows;
        int randomColumns = rand() % numColumns;
        board[randomRow][randomColumns].SetMine(true);
    }
    setAllAdjacentTiles();
    UpdateCounter();
}

void Board::UpdateCounter() {
    int dHundreds, dTens, dOnes;
    counter = GetCount();
    dHundreds = counter / 100;
    counter -= dHundreds * 100;
    dTens = counter / 10;
    counter -= dTens * 10;
    dOnes = counter / 1;
    negSign = sf::Sprite(TextureManager::GetSign());
    negSign.setPosition(12, windowHeight() - 88);
    hundreds = sf::Sprite(TextureManager::GetDigit(dHundreds));
    tens = sf::Sprite(TextureManager::GetDigit(dTens));
    ones = sf::Sprite(TextureManager::GetDigit(dOnes));
    auto digitX = 32;
    auto digitY = windowHeight() - 88;
    hundreds.setPosition(digitX, digitY);
    digitX += 20;
    tens.setPosition(digitX, digitY);
    digitX += 20;
    ones.setPosition(digitX, digitY);

    
}


void Board::drawCounter(sf::RenderWindow& myWindow) {
    //calculate current count (nummines- numFlags)
   // update textures for hundreds tens and ones.
    if (isNegative==true)
        myWindow.draw(negSign);
    myWindow.draw(hundreds);
    myWindow.draw(tens);
    myWindow.draw(ones);
}
int Board::GetCount() {
    int count = numMines - GetFlagCount();
    isNegative = false;
    if (count < 0) {
        count = GetFlagCount() - numMines;
        isNegative = true;
        }
        return count;
}



int Board::GetFlagCount() {
    numFlagsPlaced = 0;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numColumns; j++) {
            if (board[i][j].GetIsFlagged())
                numFlagsPlaced++;
        }
    }
    return numFlagsPlaced;
}

bool Board::checkIfWin() {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numColumns; j++) {
            if (!board[i][j].GetIsMine() && (!board[i][j].GetIsRevealed())) 
                return false;
            }
        }
    isGameOver = true;
    playerWon = true;
    return true;
    }


bool Board:: checkBoardMouseEvents(sf::Event::MouseButtonEvent mouseEvent) {
   //check mouse event for every tile.
    if (!isGameOver) {
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numColumns; j++) {
                if (board[i][j].checkMouseEvent(mouseEvent)) {
                    UpdateCounter();
                    if (board[i][j].GetIsMine() && board[i][j].GetIsRevealed()) {
                        isGameOver = true;
                        playerLost = true;
                        
                    }
                    checkIfWin();
                    return true;
                }

                    
            }
            UpdateCounter();
        }
    }
    return false;
}

bool Board::checkButtonEvents(sf::Event::MouseButtonEvent mouseEvent) {
    //check if debug button is clicked
    if (mineBtn.getGlobalBounds().contains(mouseEvent.x, mouseEvent.y))
        if (mouseEvent.button == sf::Mouse::Left) {
            isDebug = !isDebug;
        }
    if (faceBtn.getGlobalBounds().contains(mouseEvent.x, mouseEvent.y))
        if (mouseEvent.button == sf::Mouse::Left) {
            isGameOver = false;
            playerLost = false;
            playerWon = false;
            isNegative = false;
            createBoard();
            UpdateCounter();
            
        }
    if(Test1Btn.getGlobalBounds().contains(mouseEvent.x, mouseEvent.y))
        if (mouseEvent.button == sf::Mouse::Left) {
            readBoard("boards/testboard1.brd");
            
        }
     if(Test2Btn.getGlobalBounds().contains(mouseEvent.x,mouseEvent.y))
         if (mouseEvent.button == sf::Mouse::Left) {
             readBoard("boards/testboard2.brd");
             
         }
     if(Test3Btn.getGlobalBounds().contains(mouseEvent.x,mouseEvent.y))
         if (mouseEvent.button == sf::Mouse::Left) {
             readBoard("boards/testboard3.brd");
             
         }
    return true;
}
void Board::addFlag() {
    numFlagsPlaced++;
}

void Board::RemoveFlag() {
    numFlagsPlaced--;
}

void Board::drawBoard(sf::RenderWindow& myWindow) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numColumns; j++) {
            board[i][j].drawTile(myWindow, isDebug);
        }
    }

       
}



void Board::revealMineTiles() {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numColumns; j++) {
            if (board[i][j].GetIsMine()) {
                board[i][j].SetRevealed(true);
                if(playerWon){
                    board[i][j].SetFlag(true);
                }
                UpdateCounter();
            }
               
        }
    }
}