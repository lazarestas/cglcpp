#pragma clang diagnostic push
#include "logic.h"
#include "console.h"
#include <SFML/Graphics.hpp>
#include <thread>
#include <string>

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
    //loading array from file
    LoadFromFile(Cellarr);

    // Declare and load a font
    sf::Font font;
    if (!font.loadFromFile(R"(D:\Work\pycharm\cglcpp\SF-Pro.ttf)")) return 4;

    // start/stop iterator
    unsigned int gamestate = 1;

    // text for controls
    sf::Text text("e-restart esc-exit s-edit l-savetofile",font);
    text.setCharacterSize(20);
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setPosition(FIELDMAXw*CELL_SIZE/2-150,FIELDMAXh*CELL_SIZE-20);
    //text1,2 is frametime measure
    sf::Text text1,text2;
    text1.setCharacterSize(20);
    text2.setCharacterSize(20);
    text1.setFont(font);
    text2.setFont(font);
    text1.setFillColor(sf::Color::Red);
    text2.setFillColor(sf::Color::Yellow);
    text.setPosition(FIELDMAXw*CELL_SIZE/2-150,FIELDMAXh*CELL_SIZE-20);
    text1.setPosition(FIELDMAXw*CELL_SIZE/2-150,FIELDMAXh*CELL_SIZE-40);
    text2.setPosition(FIELDMAXw*CELL_SIZE/2-100,FIELDMAXh*CELL_SIZE-40);

    sf::RenderWindow window(sf::VideoMode(FIELDMAXw*CELL_SIZE, FIELDMAXh*CELL_SIZE), "conway`s game of life",sf::Style::Default);
    sf::Image icon;
    if (!icon.loadFromFile(R"(D:\Work\pycharm\cglcpp\crap\astolfo.png)")) return 5; // File/Image/Pixel
    window.setIcon(200, 200, icon.getPixelsPtr()); //fucking hardcoded width/heigth because of stupid sfml dll differences
    window.setFramerateLimit(10);

    sf::Clock clock; // starts the clock
    sf::Time elapsed1;
    sf::Time elapsed2;
    while (window.isOpen()){
        // timer for frametime
        clock.restart();
        //clear window
        window.clear();

        sf::Event event{};

        while (window.pollEvent(event)){
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case (sf::Keyboard::S):
                        gamestate ^= 1;
                    case (sf::Keyboard::E):
                        LoadFromFile(Cellarr);
                    case (sf::Keyboard::L):
                        SaveToFile(Cellarr);
                    case (sf::Keyboard::Escape):
                        window.close();
                }
            }
            if (event.type == sf::Event::MouseButtonPressed && gamestate == 0){
                switch (event.mouseButton.button){
                    case (sf::Mouse::Left):
                        SetLive(event.mouseButton.y/CELL_SIZE,event.mouseButton.x/CELL_SIZE,Cellarr);
                    case (sf::Mouse::Right):
                        SetDead(event.mouseButton.y/CELL_SIZE,event.mouseButton.x/CELL_SIZE,Cellarr);
                }
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // perf overlay
        elapsed1 = clock.restart();
        text1.setString(std::to_string(elapsed1.asMilliseconds()));
        // drawing stuff
        drawCells(window,Cellarr);
        window.draw(text);
        // perf overlay
        window.draw(text1);
        window.draw(text2);

        //draw window
        window.display();

        // perf overlay
        elapsed2 = clock.restart();
        text2.setString(std::to_string(elapsed2.asMilliseconds()));

        //update the field if the game is not in edit mode
        if (gamestate) Stepcgl(Cellarr);
    }
    //free the allocated memory after competion
    for (int i=0;i<FIELDMAXh;i++){
        delete Cellarr[i];
    }
    delete Cellarr;
    //I want it to be menu controlled so let's write down menu
    return 0;
}

#pragma clang diagnostic pop