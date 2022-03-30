#pragma once

#include "../../Chap1_Intro/src/Ds.h"

#define LIST_INIT_SIZE 100
#define LIST_INCREMENT 10

struct SqList
{
    int* elem;
    int len;
    int listsize;
};

Status InitList(SqList &L);

Status DestroyList(SqList &L);

Status ClearList(SqList &L);

Status ListEmpty(SqList L);

Status ListLength(SqList L);

Status GetElem(SqList L, int i, int e);

Status LocateElem(SqList L, int e, Status (*compare)(int e1,int e2) );

Status ProirElem(SqList L, int cur_e, int &pre_e);

Status NextElem(SqList L, int cur_e, int &next_e);

Status ListInsert(SqList &L, int i, int e);

Status ListDelete(SqList &L, int i, int &e);

Status ListTraverse(SqList &L, void(*visit)(int e));

Status ShowList(SqList L);