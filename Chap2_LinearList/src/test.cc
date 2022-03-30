#include <iostream>

#include "SqList.h"

void show(int a){
    std::cout <<"hhh" << a <<std::endl;
    return;
}

Status equal(int a,int b){
    return a==b;
}

int main(){
    SqList l;
    InitList(l);
    ListInsert(l,1,4);
    ListInsert(l,2,6);
    ListInsert(l,3,8);
    ListInsert(l,4,10);
    int a = 4;
    if(LocateElem(l,a,equal)){
        std::cout << "yes" << std::endl;
    }

    return 0;
}