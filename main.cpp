#pragma clang diagnostic push
//#include "include/logic.h"
//#include "include/console.h"
//#include "include/window.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <SFML/Graphics.hpp>

// Size of each cell in window
const int CELL_SIZE = 5;
//thickness of frame
const int FRAMETHIC =2*CELL_SIZE;

//let's fix the field dimensions 4 now
const int FIELDMAXh = 100; // size of game field
const int FIELDMAXw = 100;
//bottom ui height
const int BOTUIH = 40;
const int WINDOWw = (FIELDMAXw)*CELL_SIZE+2*FRAMETHIC;
const int WINDOWh = (FIELDMAXh)*CELL_SIZE+2*FRAMETHIC+BOTUIH;
// number of threads to use
const int NUM_THREADS = 4;
//framerate
const int FRAMERATE = 60;
//Cell is the smallest element on the field only 4 bytes kinda cool
struct Cell{
    //state of cell: 0 is dead 1 is alive
    int cstate:4;
    //represents the count of neighboring cells alive min 0 FIELDMAX 8 then 4 bits necessary
    int ccount:4;

};


Cell** CreateDefautArr(){
    Cell **Cellarr = new Cell*[FIELDMAXh];
    for (int i=0;i<FIELDMAXh;i++){
        Cellarr[i]=new Cell[FIELDMAXw];
        for (int j = 0; j<FIELDMAXw;j++){
            Cellarr[i][j].cstate=0;
            Cellarr[i][j].ccount=0;
        }
    }
    return Cellarr;
}

[[maybe_unused]] int poscalc(int x, int max){
    return ((abs(x)-x)/2*max+x%max);
}

void Upvote(Cell**& arr, int i, int j){
    //error out of array
    if (i<0 or i>FIELDMAXh-1 or j<0 or j>FIELDMAXw-1)
        exit(1);
    int imin = (i - 1 + FIELDMAXh) % FIELDMAXh;
    int imax = (i + 1) % FIELDMAXh;
    int jmin = (j - 1 + FIELDMAXw) % FIELDMAXw;
    int jmax = (j + 1) % FIELDMAXw;
    arr[imin][jmin].ccount++;
    arr[i][jmin].ccount++;
    arr[imax][jmin].ccount++;
    arr[imin][j].ccount++;
    arr[imax][j].ccount++;
    arr[imin][jmax].ccount++;
    arr[i][jmax].ccount++;
    arr[imax][jmax].ccount++;
}

[[maybe_unused]] void MultiThreadedUpvote(int start_i, int end_i, Cell**& arr) {
    for (int i = start_i; i < end_i; i++) {
        for (int j = 0; j < FIELDMAXw; j++) {
            if (arr[i][j].cstate == 1) {
                Upvote(arr, i, j);
            }
        }
    }
    std::this_thread::sleep_for(std::chrono::microseconds(2));
}
void MultiThreadedRender(int start_i, int end_i, Cell**& arr) {
    for (int i = start_i; i < end_i; i++) {
        for (int j = 0; j < FIELDMAXw; j++) {
            Cell CelectedCell = arr[i][j];
            if (CelectedCell.ccount == 3 or (CelectedCell.ccount == 2 and CelectedCell.cstate == 1)) {
                CelectedCell.cstate=1;
            } else {
                CelectedCell.cstate = 0;
            }
            CelectedCell.ccount=0;
            arr[i][j]=CelectedCell;
        }
    }
}

void Stepcgl(Cell**& arr,sf::Time& elapsedmax){
    sf::Clock clock;
    clock.restart();
    std::thread threads[NUM_THREADS];
    int range = FIELDMAXh / NUM_THREADS;
//    for (int i = 0; i < NUM_THREADS; i++) {
//        int start_i = i * range;
//        int end_i = (i + 1) * range;
//        if (i == NUM_THREADS - 1) {
//            end_i = FIELDMAXh;
//        }
//        threads[i] = std::thread(MultiThreadedUpvote, start_i, end_i, std::ref(arr));
//
//        sf::RectangleShape treadrect(sf::Vector2f(FIELDMAXw*CELL_SIZE,range*CELL_SIZE));
//        treadrect.setPosition(FRAMETHIC,start_i*CELL_SIZE+FRAMETHIC);
//        if (i%2==0){
//            treadrect.setFillColor(sf::Color::Blue);
//        } else treadrect.setFillColor(sf::Color::Magenta);
//        // Draw the rectangle to the window
//        window.draw(treadrect);
//    }
//    for (auto & thread : threads) {
//        thread.join();
//    }
    for (int i = 0; i<FIELDMAXh;i++){
        for (int j = 0; j<FIELDMAXw;j++){
            if (arr[i][j].cstate == 1) {
                Upvote(arr,i,j);
            }
        }
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        int start_i = i * range;
        int end_i = (i + 1) * range;
        if (i == NUM_THREADS - 1) {
            end_i = FIELDMAXh;
        }
        threads[i] = std::thread(MultiThreadedRender, start_i, end_i, std::ref(arr));
    }
    for (auto & thread : threads) {
        thread.join();
    }
    //essenially its the planned RenderCell function, but it fits there
//    for (int i = 0; i<FIELDMAXh;i++){
//        for (int j = 0; j<FIELDMAXw;j++){
//            Cell CelectedCell = arr[i][j];
//            if (CelectedCell.ccount == 3 or (CelectedCell.ccount == 2 and CelectedCell.cstate == 1)) {
//                CelectedCell.cstate=1;
//            } else {
//                CelectedCell.cstate = 0;
//            }
//            CelectedCell.ccount=0;
//            arr[i][j]=CelectedCell;
//        }
//    }
    sf::Time elapsed = clock.restart();
    if (elapsed.asMicroseconds() > elapsedmax.asMicroseconds()) {
        elapsedmax = elapsed;
        std::cout << "max step time " << elapsedmax.asMicroseconds() << std::endl;
    }
}

void SetLive(int x,int y,Cell**& arr){
    if (x>=0 && x<=FIELDMAXh-1 && y>=0 && y<=FIELDMAXw-1)
        arr[x][y].cstate=1;
    else
        std::cout << "frame click" << std::endl;

}
void SetDead(int x,int y,Cell**& arr){
    if (x>=0 && x<=FIELDMAXh-1 && y>=0 && y<=FIELDMAXw-1)
        arr[x][y].cstate=0;
    else
        std::cout << "frame click" << std::endl;
}

[[maybe_unused]] void ChangeCState(int x,int y,Cell**& arr){
    arr[x][y].cstate ^= 1;
}
std::ostream& operator << (std::ostream &os, const Cell &p){
    if (p.cstate)
        return os << p.cstate;
    return os;
}

//void PrintDaField(Cell**& arr){
//
//    for (int i = 0; i<FIELDMAXh;i++){
//        for (int j = 0; j<FIELDMAXw;j++){
//            std::cout << arr[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }
//}

void LoadFromFile(Cell**& Cellarr){
    std::ifstream source(R"(D:\Work\pycharm\cglcpp\cglsource.txt)");
    int cstate;
    if (source.is_open()){
        for (int i = 0; i<FIELDMAXh;i++){
            for (int j = 0; j<FIELDMAXw;j++){
                source >> cstate;
                Cellarr[i][j].cstate = cstate;
            }
        }
    } else {
        std::cout << "Error loading file cglsource.txt" << std::endl;
        exit(2);
    }
    source.close();
}

void SaveToFile(Cell**& Cellarr){
    std::ofstream result(R"(D:\Work\pycharm\cglcpp\cglresult.txt)");
    if (result.is_open()){
        for (int i = 0; i<FIELDMAXh;i++){
            for (int j = 0; j<FIELDMAXw;j++){
                result << Cellarr[i][j].cstate << " ";
            }
            result << std::endl;
        }
    } else {
        std::cout << "Error loading file cglresult.txt" << std::endl;
        exit (3);
    }
    result.close();
}

//void MenuControlLines(){
//    std::cout  << "(S)tart(step) simulation" << std::endl;
//    std::cout << "(P)ause simulation"<< std::endl;
//    std::cout << "(L)oad simulation from file"<< std::endl;
//    std::cout << "S(a)ve simulation to file" << std::endl;
//    std::cout << "(E)xit" << std::endl;
//}
void drawCells(sf::RenderWindow& window, Cell** cellarr,sf::RectangleShape& cell)
{
    // Loop through each cell in the array
    for (int i = 0; i < FIELDMAXh; i++) {
        for (int j = 0; j < FIELDMAXw; j++) {
            // Check if the cell is alive
            if (cellarr[i][j].cstate==1) {
                // Create a rectangle shape
                cell.setPosition(j * CELL_SIZE+FRAMETHIC, i * CELL_SIZE+FRAMETHIC);
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
    // text for controls
    sf::Font font;
    if (!font.loadFromFile(R"(D:\Work\pycharm\cglcpp\include\SF-Pro.ttf)")) exit(4);
    sf::Text text("e-restart esc-exit s-edit l-savetofile", font, 20);
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setPosition((FIELDMAXw * CELL_SIZE / 2) - 150, FIELDMAXh * CELL_SIZE - 20);
    text.setPosition(5, WINDOWh - 25);
    window.draw(text);

}
int main() {

    //there we set up cell array Cellarr
    Cell** Cellarr = CreateDefautArr();
    //loading array from file
    LoadFromFile(Cellarr);

    // Declare and load a font
    sf::Font font;
    if (!font.loadFromFile(R"(D:\Work\pycharm\cglcpp\include\SF-Pro.ttf)")) return 4;
    // start/stop iterator
    unsigned int gamestate = 1;

    // text1,2 is frametime measure
    sf::Text text1("", font, 20), text2("", font, 20);
    text1.setFont(font);
    text2.setFont(font);
    text1.setFillColor(sf::Color::Black);
    text2.setFillColor(sf::Color::Black);
    text1.setPosition(5, WINDOWh - 45);
    text2.setPosition(30, WINDOWh - 45);
    // window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;
    sf::RenderWindow window(
            sf::VideoMode(
                    WINDOWw,
                    WINDOWh),
            "conway`s game of life",
            sf::Style::Default,
            settings);
    //icon
    sf::Image icon;
    if (!icon.loadFromFile(R"(D:\Work\pycharm\cglcpp\crap\astolfo.png)"))
        return 5;
    window.setIcon(200, 200, icon.getPixelsPtr()); //fucking hardcoded width/heigth because of stupid sfml dll differences
    window.setFramerateLimit(FRAMERATE);

    sf::Clock clock; // starts the clock
//    sf::Time elapsed1;
    sf::Time elapsed2,elapsedmax,elapsedmax2;
    //cell rectangle 4 drawcell
    sf::RectangleShape cellrect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    cellrect.setFillColor(sf::Color::Green);
    // create threads and assign ranges to each thread
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
                        break;
                    case (sf::Keyboard::E):
                        LoadFromFile(Cellarr);
                        break;
                    case (sf::Keyboard::L):
                        SaveToFile(Cellarr);
                        break;
                    case (sf::Keyboard::R):
                        elapsedmax = sf::microseconds(0);
                        elapsedmax2 = sf::microseconds(0);
                        break;
                    case (sf::Keyboard::Escape):
                        window.close();
                        break;
                }
            }
            if (event.type == sf::Event::MouseButtonPressed && gamestate == 0){
                switch (event.mouseButton.button){
                    case (sf::Mouse::Left):
                        SetLive((event.mouseButton.y-FRAMETHIC)/CELL_SIZE,(event.mouseButton.x-FRAMETHIC)/CELL_SIZE,Cellarr);
                        break;
                    case (sf::Mouse::Right):
                        SetDead((event.mouseButton.y-FRAMETHIC)/CELL_SIZE,(event.mouseButton.x-FRAMETHIC)/CELL_SIZE,Cellarr);
                        break;
                }
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //update the field if the game is not in edit mode
        if (gamestate) Stepcgl(Cellarr,elapsedmax);

        // drawing stuff
        drawCells(window,Cellarr,cellrect);
        drawUIbottom(window);

        // perf overlay
        window.draw(text1);
        window.draw(text2);

        //draw window
        window.display();

        // perf overlay
        text2.setString(std::to_string(elapsed2.asMicroseconds()));
        elapsed2 = clock.restart();
        if (elapsedmax2<elapsed2){
            elapsedmax2 = elapsed2;
            std::cout << "max frame time " << elapsedmax2.asMicroseconds() << std::endl;
        }

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