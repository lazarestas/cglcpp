//
// Created by LAZPC on 30.01.2023.
//

#ifndef CONWAY_LOGIC_H
#define CONWAY_LOGIC_H

#include "include/color.hpp"
#include <iostream>
using namespace std;
//let's fix the field dimensions 4 now
const int FIELDMAXh = 36;
const int FIELDMAXw = 50;
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
Cell** CreateDefautArr(){
    Cell **Cellarr = new Cell*[FIELDMAXh];
    for (int i=0;i<FIELDMAXh;i++){
        Cellarr[i]=new Cell[FIELDMAXw];
        for (int j = 0; j<FIELDMAXw;j++){
            Cellarr[i][j].cstate=0;
            Cellarr[i][j].ccount=0;
        }
    }
    Cellarr[1][1].cstate++;
    Cellarr[1][2].cstate++;
    Cellarr[1][3].cstate++;
    Cellarr[3][8].cstate++;
    Cellarr[4][8].cstate++;
    Cellarr[4][9].cstate++;
    Cellarr[5][3].cstate++;
    Cellarr[6][3].cstate++;
    Cellarr[7][3].cstate++;
    Cellarr[6][1].cstate++;
    Cellarr[7][2].cstate++;
    return Cellarr;
}

[[maybe_unused]] int poscalc(int x, int max){
    return ((abs(x)-x)/2*max+x%max);
}
void Upvote(Cell** arr, int i, int j){
//    cout << "Asking " << i << " " << j << "Cell" << endl;
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



#endif //CONWAY_LOGIC_H
