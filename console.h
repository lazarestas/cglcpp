//
// Created by Stas on 27.03.2023.
//

#ifndef CONWAY_CONSOLE_H
#define CONWAY_CONSOLE_H
#include <iostream>
#include "include/color.hpp"
#include "logic.h"
#include <fstream>
using namespace std;
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
int LoadFromFile(Cell**);
int SaveToFile(Cell**);


void PrintDaField(Cell** arr){

    for (int i = 0; i<FIELDMAXh;i++){
        for (int j = 0; j<FIELDMAXw;j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}
int LoadFromFile(Cell** Cellarr){
    ifstream source(R"(D:\Work\pycharm\cglcpp\cglsource.txt)");
    int cstate;
    if (source.is_open()){
        for (int i = 0; i<FIELDMAXh;i++){
            for (int j = 0; j<FIELDMAXw;j++){
                source >> cstate;
                Cellarr[i][j].cstate = cstate;
            }
        }
    } else {
        cout << "Error loading file cglsource.txt" << endl;
        return -2;
    }
    source.close();
    return 0;
}
int SaveToFile(Cell** Cellarr){
    ofstream result(R"(D:\Work\pycharm\cglcpp\cglresult.txt)");
    if (result.is_open()){
        for (int i = 0; i<FIELDMAXh;i++){
            for (int j = 0; j<FIELDMAXw;j++){
                result << Cellarr[i][j].cstate << " ";
            }
            result << endl;
        }
    } else {
        cout << "Error loading file cglresult.txt" << endl;
        return -2;
    }
    result.close();
    return 0;
}

void MenuControlLines(){
    cout << hue::aqua << "(S)tart(step) simulation" << endl;
    cout << "(P)ause simulation"<< endl;
    cout << "(L)oad simulation from file"<< endl;
    cout << "S(a)ve simulation to file" << endl;
    cout << "(E)xit" << hue::reset << endl;
}

#endif //CONWAY_CONSOLE_H
