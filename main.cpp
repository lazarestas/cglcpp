#include <iostream>
#include <iomanip>
#include <cctype>
#include <conio.h>
#include "include/color.hpp"

using namespace std;

//let's fix the field dimensions 4 now
const int FIELDMAX = 10;

//Cell is the smallest element on the field
struct Cell{
    //state of cell: 0 is dead 1 is alive
    int cstate:2;
    //represents the count of neighboring cells alive min 0 max 8 then 4 bits necessary
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

void PrintDaField(Cell** arr,const int max){
//    cout << "guess its start of the field" << endl;
    for (int i = 0; i<max;i++){
        for (int j = 0; j<max;j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
//    for (int i = 0; i<max;i++){
//        for (int j = 0; j<max;j++){
//            cout << arr[i][j].posx << " " << arr[i][j].posy << endl;
//        }
//        cout << endl;
//    }
//    cout << "guess its end of the field" << endl;
}

Cell** CreateDefautArr(const int max){
    Cell **Cellarr = new Cell*[max];
        for (int i=0;i<max;i++){
            Cellarr[i]=new Cell[max];
            for (int j = 0; j<max;j++){
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
void Upvote(Cell** arr, const int max, int i, int j){
}
void Stepcgl(Cell** arr, const int max){
    for (int i = 0; i<max;i++){
        for (int j = 0; j<max;j++){
        if (arr[i][j].cstate == 1) {
            Upvote(arr,max,i,j);
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
    Cell** Cellarr = CreateDefautArr(FIELDMAX);
    char c;

    while(toupper(c)!='E'){
        system("cls");
        cout << "Cell is " << sizeof(Cell) << " bytes" << endl;
        PrintDaField(Cellarr, FIELDMAX);
        MenuControlsLines();
        cin >> c;
        switch (toupper(c)){
                //start/step
            case 'S':
                //pause
            case 'P':
                //load
                //will load from file conwaytable.txt
            case 'L':
            case 'A':
            default:
                break;
        };
    }

    //I want it to be menu controlled so let's write down menu

    return 0;
}

