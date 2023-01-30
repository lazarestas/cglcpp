#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace std;
int poscalc(int x, int max){
    return ((abs(x)-x)/2*max+x%max);
}
void
int main(){


    cout << poscalc(-1,10) << " -1" << endl;
    cout << poscalc(10,10) << " 10" << endl;
    cout << poscalc(9,10) << " 9" << endl;
    return 0;
}