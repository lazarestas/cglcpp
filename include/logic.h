//
// Created by LAZPC on 30.01.2023.
//

#ifndef CONWAY_LOGIC_H
#define CONWAY_LOGIC_H

#include "color.hpp"
#include <iostream>
#include <thread>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

const int CELL_SIZE = 5; // Size of each cell in window
const int FRAMETHIC =2*CELL_SIZE;
//let's fix the field dimensions 4 now
const int FIELDMAXh = 100; // size of game field
const int FIELDMAXw = 100;
const int BOTUIH = 40;
const int WINDOWw = (FIELDMAXw)*CELL_SIZE+2*FRAMETHIC;
const int WINDOWh = (FIELDMAXh)*CELL_SIZE+2*FRAMETHIC+BOTUIH;

const int NUM_THREADS = 4; // number of threads to use
const int FRAMERATE = 60;
//Cell is the smallest element on the field only 4 bytes kinda cool
struct Cell{
    //state of cell: 0 is dead 1 is alive
    int cstate:4;
    //represents the count of neighboring cells alive min 0 FIELDMAX 8 then 4 bits necessary
    int ccount:4;

};

//Cell** CreateDefautArr();
//[[maybe_unused]] int poscalc(int, int);
//void Upvote(Cell**&, int, int);
//void Stepcgl(Cell**&);
//void SetLive(int,int,Cell**&);
//void SetDead(int,int,Cell**&);
//void ChangeCState(int,int,Cell**&);

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

void MultiThreadedUpvote(int start_i, int end_i, Cell**& arr) {
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

void Stepcgl(Cell**& arr, sf::RenderWindow& window,sf::Time& elapsedmax){
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



#endif //CONWAY_LOGIC_H
