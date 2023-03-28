//
// Created by LAZPC on 30.01.2023.
//

#ifndef CONWAY_LOGIC_H
#define CONWAY_LOGIC_H

#include "include/color.hpp"
#include <iostream>
using namespace std;

//let's fix the field dimensions 4 now
const int FIELDMAXh = 80; // size of game field
const int FIELDMAXw = 120;
const int CELL_SIZE = 10; // Size of each cell in window

//Cell is the smallest element on the field only 4 bytes kinda cool
struct Cell{
    //state of cell: 0 is dead 1 is alive
    int cstate:2;
    //represents the count of neighboring cells alive min 0 FIELDMAX 8 then 4 bits necessary
    int ccount:4;

};

Cell** CreateDefautArr();
[[maybe_unused]] int poscalc(int, int);
void Upvote(Cell**, int, int);
void Stepcgl(Cell**);
void SetLive(int,int,Cell**);
void SetDead(int,int,Cell**);

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

void Upvote(Cell** arr, int i, int j){
    if (i<0 or i>FIELDMAXh-1 or j<0 or j>FIELDMAXw-1) {
        //error out of array
        cout << dye::on_red("LOL YOU SOMEHOW ESCAPED THE ARRAY HIIII") << endl;
        return;
    }
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


void Stepcgl(Cell** arr){
    for (int i = 0; i<FIELDMAXh;i++){
        for (int j = 0; j<FIELDMAXw;j++){
            if (arr[i][j].cstate == 1) {
                Upvote(arr,i,j);
            }
        }
    }
    //essenially its the planned RenderCell function, but it fits there
    for (int i = 0; i<FIELDMAXh;i++){
        for (int j = 0; j<FIELDMAXw;j++){
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

void SetLive(int x,int y,Cell** arr){
    arr[x][y].cstate=1;
}
void SetDead(int x,int y,Cell** arr){
    arr[x][y].cstate=0;
}


#endif //CONWAY_LOGIC_H
