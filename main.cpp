#include <iostream>
#include <iomanip>
#include <cctype>
#include <conio.h>

using namespace std;

//let's fix the field dimensions 4 now
const int FIELDMAX = 4;

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

void PrintDaField(Cell** arr,const int max){
    cout << "guess its start of the field" << endl;
    for (int i = 0; i<max;i++){
        for (int j = 0; j<max;j++){
            cout <<setfill('0') << setw(1)<< arr[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i<max;i++){
        for (int j = 0; j<max;j++){
            cout << arr[i][j].posx << " " << arr[i][j].posy << endl;
        }
        cout << endl;
    }
    cout << "guess its end of the field" << endl;
}

Cell** CreateDefautArr(const int max){
    Cell **Cellarr = new Cell*[max];
        for (int i=0;i<max;i++){
            Cellarr[i]=new Cell[max];
            for (int j = 0; j<max;j++){
                Cellarr[i][j].cstate=0;
                Cellarr[i][j].posx=i+1;
                Cellarr[i][j].posy=j+1;
            }
        }
    Cellarr[1][1].cstate = 1;
    Cellarr[1][2].cstate = 1;
    Cellarr[2][1].cstate = 1;
    return Cellarr;
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
    Cell** Cellarr = CreateDefautArr(FIELDMAX);
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

