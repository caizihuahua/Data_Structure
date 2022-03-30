#include <iostream>

#include "Triple.h"


Status compare(int t1, int t2){
    return t1-t2>0?TRUE:FALSE;
}

int main(){
    Triple<int> t;
    InitTriple(t,3,4,5);
    ShowTriple(t);
    DestroyTriple(t);
    ShowTriple(t);
    return 0;
}