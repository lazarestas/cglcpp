#include <iostream>
#include <iomanip>
#include <cctype>
#include <conio.h>
#include "include/color.hpp"

using namespace std;

//let's fix the field dimensions 4 now
const int FIELDMAX = 10;

//Cell is the smallest element on the field only 4 bytes kinda cool
struct Cell{
    //state of cell: 0 is dead 1 is alive
    int cstate:2;
    int checked:2;
    //represents the count of neighboring cells alive min 0 FIELDMAX 8 then 4 bits necessary
    int ccount:4;

};

//override << operator to output Cell cstate
ostream& operator << (ostream &os, const Cell &p){
    switch (p.cstate) {
        case 0:
            return os << p.cstate;
        case 1:
            return os << dye::red(p.cstate);
    }

}

void PrintDaField(Cell** arr){
//    cout << "guess its start of the field" << endl;
    for (int i = 0; i<FIELDMAX;i++){
        for (int j = 0; j<FIELDMAX;j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
//    for (int i = 0; i<FIELDMAX;i++){
//        for (int j = 0; j<FIELDMAX;j++){
//            cout << arr[i][j].posx << " " << arr[i][j].posy << endl;
//        }
//        cout << endl;
//    }
//    cout << "guess its end of the field" << endl;
}

Cell** CreateDefautArr(){
    Cell **Cellarr = new Cell*[FIELDMAX];
        for (int i=0;i<FIELDMAX;i++){
            Cellarr[i]=new Cell[FIELDMAX];
            for (int j = 0; j<FIELDMAX;j++){
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

void Upvote(Cell** arr, int i, int j){
    if (i==0) {
        if (j==0){
            //top left corner
            arr[FIELDMAX][FIELDMAX].ccount++;
            arr[FIELDMAX][0].ccount++;
            arr[FIELDMAX][1].ccount++;
            arr[0][FIELDMAX].ccount++;
            arr[0][1].ccount++;
            arr[1][FIELDMAX].ccount++;
            arr[1][0].ccount++;
            arr[1][1].ccount++;
        } else if (j==FIELDMAX){
            //top right corner
            arr[FIELDMAX][FIELDMAX - 1].ccount++;
            arr[FIELDMAX][FIELDMAX].ccount++;
            arr[FIELDMAX][0].ccount++;
            arr[0][FIELDMAX - 1].ccount++;
            arr[0][0].ccount++;
            arr[1][FIELDMAX - 1].ccount++;
            arr[1][FIELDMAX].ccount++;
            arr[1][0].ccount++;
        }
    } else if (i == FIELDMAX) {
        if (j==0){
            //bottom left corner
            arr[FIELDMAX-1][FIELDMAX].ccount++;
            arr[FIELDMAX][FIELDMAX].ccount++;
            arr[0][FIELDMAX].ccount++;
            arr[0][0].ccount++;
            arr[0][1].ccount++;
            arr[FIELDMAX-1][0].ccount++;
            arr[FIELDMAX-1][1].ccount++;
            arr[FIELDMAX][1].ccount++;
        } else if (j==FIELDMAX){
            //bottom right corner
            arr[FIELDMAX-1][0].ccount++;
            arr[FIELDMAX][0].ccount++;
            arr[0][FIELDMAX - 1].ccount++;
            arr[0][FIELDMAX].ccount++;
            arr[0][0].ccount++;
            arr[FIELDMAX-1][FIELDMAX-1].ccount++;
            arr[FIELDMAX-1][FIELDMAX].ccount++;
            arr[FIELDMAX][FIELDMAX-1].ccount++;
        }
    } else if (i<0 or i>FIELDMAX or j<0 or j>FIELDMAX){
        //error out of array
        cout << dye::on_red("LOL YOU SOMEHOW ESCAPED THE ARRAY HIIII") << endl;
    } else {
        //inside array, no weird teleports
        arr[i-1][j-1].ccount++;
        arr[i-1][j].ccount++;
        arr[i-1][j+1].ccount++;
        arr[i][j-1].ccount++;
        arr[i][j+1].ccount++;
        arr[i+1][j-1].ccount++;
        arr[i+1][j].ccount++;
        arr[i+1][j+1].ccount++;
    }
}

void Stepcgl(Cell** arr){
    for (int i = 0; i<FIELDMAX;i++){
        for (int j = 0; j<FIELDMAX;j++){
        if (arr[i][j].cstate == 1) {
            Upvote(arr,i,j);
        }
        }
    }
    //essenially its the planned RenderCell function, but it fits there
    for (int i = 0; i<FIELDMAX;i++){
        for (int j = 0; j<FIELDMAX;j++){
            switch (arr[i][j].ccount){
                case 0:
                    //Any live cell with fewer than two
                    // live neighbours dies, as if by underpopulation.
                    arr[i][j].cstate=0;
                    arr[i][j].ccount=0;
                    break;
                case 1:
                    //Any live cell with fewer than two
                    // live neighbours dies, as if by underpopulation.
                    arr[i][j].cstate=0;
                    arr[i][j].ccount=0;
                    break;
                case 2:
                    //Any live cell with two or three
                    // live neighbours lives on to the next generation.
                    if (arr[i][j].cstate==1){
                        arr[i][j].cstate=1;
                        arr[i][j].ccount=0;
                    }
                    break;
                case 3:
                    //Any dead cell with exactly three
                    // live neighbours becomes a live cell, as if by reproduction.
                    arr[i][j].cstate=1;
                    arr[i][j].ccount=0;
                    break;
                default:
                    //Any live cell with more than three
                    // live neighbours dies, as if by overpopulation.
                    arr[i][j].cstate=0;
                    arr[i][j].ccount=0;
                    break;
            }
        }
    }
}

void MenuControlsLines(){
    cout << hue::aqua << "(S)tart(step) simulation" << endl;
    cout << "(P)ause simulation"<< endl;
    cout << "(L)oad simulation from file"<< endl;
    cout << "S(a)ve simulation to file" << endl;
    cout << "(E)xit" << hue::reset << endl;
};

int main() {
    cout << "there is a start to anything(placeholder)" << endl;
    //there we set up cell array Cellarr
    Cell** Cellarr = CreateDefautArr();
    char c;

    while(toupper(c)!='E'){
        system("cls");
        cout << "Cell is " << sizeof(Cell) << " bytes" << endl;
        PrintDaField(Cellarr);
        MenuControlsLines();
        cin >> c;
        switch (toupper(c)){
                //start/step
            case 'S':
                Stepcgl(Cellarr);
                break;
                //pause
            case 'P':
                //load
                //will load from file conwaytable.txt
            case 'L':
            case 'A': break;
        }
    }
    //I want it to be menu controlled so let's write down menu
    return 0;
}

