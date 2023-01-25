#include <iostream>
#include <iomanip>
#include <cctype>
#include <conio.h>

using namespace std;

//let's fix the field dimensions 4 now
const int FIELDMAX = 10;

//Cell is the smallest element on the field
struct Cell{
    int posx;
    int posy;
    bool cstate;
};
//override << operator to output Cell cstate
ostream& operator << (ostream &os, const Cell &p){
    return os << p.cstate;
}

void PrintDaField(Cell arr[FIELDMAX][FIELDMAX],const int max){
    cout << "guess its start of the field" << endl;
    for (int i = 0; i<max;i++){
        for (int j = 0; j<max;j++){
            cout <<setfill('0') << setw(1)<< arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << "guess its end of the field" << endl;
}

void MenuControlsLines(){
    cout << "(S)tart simulation"<< endl;
    cout << "(P)ause simulation"<< endl;
    cout << "(L)oad simulation from file"<< endl;
    cout << "S(a)ve simulation to file" << endl;
    cout << "(E)xit" << endl;
};

int main() {
    cout << "there is a start to anything(placeholder)" << endl;
    //there we set up cell array Cellarr
    Cell Cellarr[FIELDMAX][FIELDMAX];
    for (int i = 0; i<FIELDMAX;i++){
        for (int j = 0; j<FIELDMAX;j++){
        Cellarr[i][j].cstate=0;
        }
    }
    char c;

    while(toupper(c)!='E'){
        system("cls");
        PrintDaField(Cellarr, FIELDMAX);
        MenuControlsLines();
        cin >> c;
        switch (toupper(c)){
                //start
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

