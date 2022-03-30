#include <cstdlib>
#include <iostream>

#include "SqList.h"

Status InitList(SqList &L){
    L.elem = (int*) malloc(LIST_INIT_SIZE*sizeof(int));
    if(L.elem==NULL) return ERROR;
    L.len = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}

Status DestroyList(SqList &L){
    free(L.elem);
    L.elem = NULL;
    L.len = 0;
    L.listsize = 0;
    return OK;
}

Status ClearList(SqList &L){
    if(DestroyList(L) && InitList(L))
        return OK;
    else return ERROR;
}

Status ListEmpty(SqList L){
    return L.elem==NULL;
}

int ListLength(SqList L){
    return L.len;
}

Status GetElem(SqList L, int i, int e){
    if(i>=1 && i<=L.len){
        e = L.elem[i-1];
        return OK;
    }else{
        return ERROR;
    }
}

Status LocateElem(SqList L, int e, Status (*compare)(int e1,int e2) ){
    for (int i=0;i<L.len;i++){
        if(compare(e,L.elem[i])) return TRUE;
    }
    return FALSE;
}

Status ProirElem(SqList L, int cur_e, int &pre_e){
    for(int i=1;i<L.len;i++){
        if(L.elem[i] == cur_e){
            pre_e = L.elem[i-1];
            return TRUE;
        }
    }
    return FALSE;
}

Status NextElem(SqList L, int cur_e, int &next_e){
    for(int i=0;i<L.len-1;i++){
        if(L.elem[i]==cur_e){
            next_e = L.elem[i+1];
            return TRUE;
        }
    }
    return FALSE;
}

Status ListInsert(SqList &L, int i, int e){
    if(i>=1 && i<=L.len+1){
        if(L.len == L.listsize){
            L.elem = (int*) realloc(L.elem,(L.len+LIST_INCREMENT)*sizeof(int));
            if(L.elem == NULL) return OVERFLOW;
            L.listsize += LIST_INCREMENT;
        }
        for(int j=L.len-1;j>=i-1;j--){
            L.elem[j+1] = L.elem[j];
        }
        L.elem[i-1] = e;
        L.len++;
        return OK;
    }else{
        return ERROR;
    }
}

Status ListDelete(SqList &L, int i, int &e){
    if(i>=1 && i<=L.len){
        e = L.elem[i-1];
        for(int j=i-1;j<L.len;j++){
            L.elem[j] = L.elem[j+1];
        }
        L.len--;
        return OK;
    }else{
        return ERROR;
    }
}

Status ListTraverse(SqList &L, void(*visit)(int e)){
    for(int i=0;i<L.len;i++){
        visit(L.elem[i]);
    }
    return OK;
}

Status ShowList(SqList L){
    for(int i=0;i<L.len;i++){
        std::cout << L.elem[i] << std::endl;
    }
    return OK;
}

Status MergeLists(SqList La, SqList Lb, SqList &Lc){
    int i,j,k;
    i=j=k=0;
    InitList(Lc);
    while(i<La.len && j<Lb.len){
        if(La.elem[i] > Lb.elem[j]){
            ListInsert(Lc,++k,Lb.elem[j++]);
        }else{
            ListInsert(Lc,++k,La.elem[i++]);
        }
    }
    while(i<La.len){
        ListInsert(Lc,++k,La.elem[i++]);
    }
    while(j<Lb.len){
        ListInsert(Lc,++k,Lb.elem[j++]);
    }
    return OK;
}