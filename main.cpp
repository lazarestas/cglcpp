#include <cctype>
#include <fstream>
#include "logic.h"
#include "console.h"
#include <windows.h>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
using namespace std;

const int CELL_SIZE = 10; // Size of each cell


void drawCells(sf::RenderWindow& window, Cell** cellarr)
{
    // Loop through each cell in the array
    for (int i = 0; i < FIELDMAXh; i++) {
        for (int j = 0; j < FIELDMAXw; j++) {
            // Check if the cell is alive
            if (cellarr[i][j].cstate==1) {
                // Create a rectangle shape
                sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                cell.setPosition(j * CELL_SIZE, i * CELL_SIZE);
                cell.setFillColor(sf::Color::Green);

                // Draw the rectangle to the window
                window.draw(cell);
            }
        }
    }
}
int main() {
    //there we set up cell array Cellarr
    Cell** Cellarr = CreateDefautArr();
    LoadFromFile(Cellarr);
    // Declare and load a font
    sf::Font font;
    if (!font.loadFromFile("C:\\Users\\Stas\\Downloads\\SF Pro\\SF-Pro.ttf"))
    {
        return 123;
    }
// Create a text
    sf::Text text("e-restart esc-exit",font);
    text.setCharacterSize(20);
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setPosition(FIELDMAXw*CELL_SIZE/2,FIELDMAXh*CELL_SIZE-20);
    sf::RenderWindow window(sf::VideoMode(FIELDMAXw*CELL_SIZE, FIELDMAXh*CELL_SIZE), "conway`s game of life",sf::Style::None);
    window.setFramerateLimit(10);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            {
                // left key is pressed: move our character
                LoadFromFile(Cellarr);
            }

            if (event.type == sf::Event::Closed||sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }
        window.clear();
        // Add your drawing code here
        drawCells(window,Cellarr);
        window.draw(text);
        window.display();
        Stepcgl(Cellarr);
    }
    //free the allocated memory after competion
    for (int i=0;i<FIELDMAXh;i++){
        delete Cellarr[i];
    }
    delete Cellarr;
    //I want it to be menu controlled so let's write down menu
    return 0;
}
