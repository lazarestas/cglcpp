#include <cctype>
#include <fstream>
#include "logic.h"
#include "console.h"
#include <windows.h>
using namespace std;

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

