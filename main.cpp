#include <iostream>
#include <cctype>
#include "include/color.hpp"
#include <fstream>
#include "simple.h"
using namespace std;

//let's fix the field dimensions 4 now
const int FIELDMAX = 10;

//Cell is the smallest element on the field only 4 bytes kinda cool
struct Cell{
    //state of cell: 0 is dead 1 is alive
    int cstate:2;
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
        default:
            return os;
    }

}
void MenuControlLines();
void PrintDaField(Cell**);
Cell** CreateDefautArr();
int poscalc(int, int);
void Upvote(Cell**, int, int);
void Stepcgl(Cell**);
int LoadFromFile(Cell**);
int SaveToFile(Cell**);

int main() {
    //there we set up cell array Cellarr
    Cell** Cellarr = CreateDefautArr();
    char c;

    while(toupper(c)!='E'){
        PrintDaField(Cellarr);
        MenuControlLines();
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
                LoadFromFile(Cellarr);
                break;
            //save to file
            case 'A':
                SaveToFile(Cellarr);
                break;
        }

    }
    //free the allocated memory after competion
    for (int i=0;i<FIELDMAX;i++){
        delete Cellarr[i];
    }
    delete Cellarr;
    //I want it to be menu controlled so let's write down menu
    return 0;
}

void PrintDaField(Cell** arr){

    for (int i = 0; i<FIELDMAX;i++){
        for (int j = 0; j<FIELDMAX;j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}
int LoadFromFile(Cell** Cellarr){
    ifstream source("D:\\clion(jetc)\\conway\\cglsource.txt");
    int cstate;
    if (source.is_open()){
        for (int i = 0; i<FIELDMAX;i++){
            for (int j = 0; j<FIELDMAX;j++){
                source >> cstate;
                Cellarr[i][j].cstate = cstate;
            }
            }
    } else {
        cout << "Error loading file cglsource.txt" << endl;
        return -2;
    }
    source.close();
}
int SaveToFile(Cell** Cellarr){
    ofstream result("D:\\clion(jetc)\\conway\\cglresult.txt");
    if (result.is_open()){
        for (int i = 0; i<FIELDMAX;i++){
            for (int j = 0; j<FIELDMAX;j++){
                result << Cellarr[i][j].cstate << " ";
            }
            result << endl;
        }
    } else {
        cout << "Error loading file cglresult.txt" << endl;
        return -2;
    }
    result.close();
};
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
int poscalc(int x, int max){
    return ((abs(x)-x)/2*max+x%max);
}
void Upvote(Cell** arr, int i, int j){
//    cout << "Asking " << i << " " << j << "Cell" << endl;
    if (i<0 or i>FIELDMAX-1 or j<0 or j>FIELDMAX-1) {
        //error out of array
        cout << dye::on_red("LOL YOU SOMEHOW ESCAPED THE ARRAY HIIII") << endl;
        return;
    }
    //4 poscalc functions: 2 for i 2 for j (+-1)
    int imin=poscalc(i-1,FIELDMAX);
    int imax=poscalc(i+1,FIELDMAX);
    int jmin=poscalc(j-1,FIELDMAX);
    int jmax=poscalc(j+1,FIELDMAX);
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
void MenuControlLines(){
    cout << hue::aqua << "(S)tart(step) simulation" << endl;
    cout << "(P)ause simulation"<< endl;
    cout << "(L)oad simulation from file"<< endl;
    cout << "S(a)ve simulation to file" << endl;
    cout << "(E)xit" << hue::reset << endl;
}