//
// Created by Stas on 27.03.2023.
//

#ifndef CONWAY_CONSOLE_H
#define CONWAY_CONSOLE_H

#include <iostream>
#include "include/color.hpp"
#include "logic.h"
#include <fstream>


//override << operator to output Cell cstate
std::ostream& operator << (std::ostream &os, const Cell &p){
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
void PrintDaField(Cell**&);
void LoadFromFile(Cell**&);
void SaveToFile(Cell**&);


void PrintDaField(Cell**& arr){

    for (int i = 0; i<FIELDMAXh;i++){
        for (int j = 0; j<FIELDMAXw;j++){
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
void LoadFromFile(Cell**& Cellarr){
    std::ifstream source(R"(D:\Work\pycharm\cglcpp\cglsource.txt)");
    int cstate;
    if (source.is_open()){
        for (int i = 0; i<FIELDMAXh;i++){
            for (int j = 0; j<FIELDMAXw;j++){
                source >> cstate;
                Cellarr[i][j].cstate = cstate;
            }
        }
    } else {
        std::cout << "Error loading file cglsource.txt" << std::endl;
        exit(2);
    }
    source.close();
    return;
}
void SaveToFile(Cell**& Cellarr){
    std::ofstream result(R"(D:\Work\pycharm\cglcpp\cglresult.txt)");
    if (result.is_open()){
        for (int i = 0; i<FIELDMAXh;i++){
            for (int j = 0; j<FIELDMAXw;j++){
                result << Cellarr[i][j].cstate << " ";
            }
            result << std::endl;
        }
    } else {
        std::cout << "Error loading file cglresult.txt" << std::endl;
        exit (3);
    }
    result.close();
    return;
}

void MenuControlLines(){
    std::cout << hue::aqua << "(S)tart(step) simulation" << std::endl;
    std::cout << "(P)ause simulation"<< std::endl;
    std::cout << "(L)oad simulation from file"<< std::endl;
    std::cout << "S(a)ve simulation to file" << std::endl;
    std::cout << "(E)xit" << hue::reset << std::endl;
}

#endif //CONWAY_CONSOLE_H
