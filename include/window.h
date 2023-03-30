//
// Created by Stas on 30.03.2023.
//

#ifndef CONWAY_WINDOW_H
#define CONWAY_WINDOW_H
#include <SFML/Graphics.hpp>
#include "logic.h"

void drawCells(sf::RenderWindow& window, Cell** cellarr)
{
    // Loop through each cell in the array
    for (int i = 0; i < FIELDMAXh; i++) {
        for (int j = 0; j < FIELDMAXw; j++) {
            // Check if the cell is alive
            if (cellarr[i][j].cstate==1) {
                // Create a rectangle shape
                sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                cell.setPosition(j * CELL_SIZE+FRAMETHIC, i * CELL_SIZE+FRAMETHIC);
                cell.setFillColor(sf::Color::Green);
                // Draw the rectangle to the window
                window.draw(cell);
            }
        }
    }
}

void drawUIbottom(sf::RenderWindow& window)
{
    // Create a rectangle shape for the frame
    sf::RectangleShape frame(sf::Vector2f(WINDOWw - 2*FRAMETHIC, WINDOWh - 2*FRAMETHIC));
    frame.setPosition(FRAMETHIC,FRAMETHIC);
    frame.setFillColor(sf::Color::Transparent);
    frame.setOutlineThickness(FRAMETHIC);
    frame.setOutlineColor(sf::Color::Cyan);

    // Draw the frame to the window
    window.draw(frame);

    // Create a rectangle shape for the bottom bar
    sf::RectangleShape bottomBar(sf::Vector2f(WINDOWw, BOTUIH+FRAMETHIC));
    bottomBar.setPosition(0, WINDOWh-BOTUIH-FRAMETHIC);
    bottomBar.setFillColor(sf::Color::Cyan);

    // Draw the bottom bar to the window
    window.draw(bottomBar);
}
#endif //CONWAY_WINDOW_H
