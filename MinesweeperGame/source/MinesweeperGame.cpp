// MinesweeperGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <map>
#include "Tile.h"
#include "Board.h"
#include "TextureManager.h"
using namespace std;
int main()
{
    Board newBoard("boards/config.cfg");



    sf::RenderWindow window(sf::VideoMode(newBoard.windowWidth(), newBoard.windowHeight()), "Minesweeper");

    while (window.isOpen())
    {
        sf::Event event;
        window.clear();
        window.clear(sf::Color::White);
        newBoard.drawBoard(window);
        newBoard.drawButtons(window);
        newBoard.drawCounter(window);

        window.display();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonReleased) {
                newBoard.checkBoardMouseEvents(event.mouseButton);
                newBoard.checkButtonEvents(event.mouseButton);
            }
        }
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
