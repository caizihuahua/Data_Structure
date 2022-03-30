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
    SqList l1,l2,l3;
    InitList(l1);
    ListInsert(l1,1,4);
    ListInsert(l1,2,6);
    ListInsert(l1,3,8);
    ListInsert(l1,4,10);
    InitList(l2);
    ListInsert(l2,1,3);
    ListInsert(l2,2,5);
    ListInsert(l2,3,9);
    ListInsert(l2,4,10);

    MergeLists(l1,l2,l3);
    ShowList(l3);
    return 0;
}