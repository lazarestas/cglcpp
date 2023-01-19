#include <iostream>
#include <iomanip>


using namespace std;
const int FIELDMAX = 9;
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
void PrintDaField(const Cell arr**,const int max){
    cout << "guess its start of the field" << endl;
    for (int i = 0; i<max;i++){
        for (int j = 0; j<max;j++){
            cout <<setfill('0') << setw(1)<< arr[i][j];
        }
        cout << endl;
    }
    cout << "guess its end of the field" << endl;
}
int main() {
    cout << "there is a start to anything(placeholder)" << endl;
    //let's fix the field dimensions 4 now
    Cell Cellarr[FIELDMAX][FIELDMAX];
    for (int i = 0; i<FIELDMAX;i++){
        for (int j = 0; j<FIELDMAX;j++){
        Cellarr[i][j].cstate=0;
        }
    }
    PrintDaField(Cellarr,FIELDMAX);

    return 0;
}

