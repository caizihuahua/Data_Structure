#pragma once

#include <cstdlib>
#include <iostream>

#include "Triple.h"
#include "Ds.h"

template <typename T>
struct Triple
{
    T* data;
};

/*
templete must be defined in .hpp file
and the template function act as inline function
*/

template <typename T>
Status InitTriple(Triple<T> &triple, T t1, T t2, T t3){
    triple.data = (T*)malloc(3*sizeof(T));
    triple.data[0] = t1;
    triple.data[1] = t2;
    triple.data[2] = t3;
    return OK;
}

template <typename T>
Status DestroyTriple(Triple<T> &triple){
    free(triple.data);
    triple.data = NULL;
    return OK;
}

// noway to judge whether or not the triple is initialized
template <typename T>
Status Get (Triple<T> triple, int i, T &e){
    if(i>=1 && i<=3){
            e = triple.data[i-1];
            return OK;
    }else{
        exit(OVERFLOW);
    }
}

template <typename T>
Status Put(Triple<T> &triple, int i, T e){
    if(i>=1 && i<=3){
            triple.data[i-1] = e;
            return OK;
    }else{
        exit(OVERFLOW);
    }
}

template <typename T>
Status IsAscending (Triple<T> triple, Status (*compare)(T t1,T t2)){
    if(!compare(triple.data[0],triple.data[1]) && !compare(triple.data[1],triple.data[2])){
        return TRUE;
    }else{
        return FALSE;
    }
}

template <typename T>
Status IsDescending (Triple<T> triple, Status (*compare)(T t1,T t2)){
    if(compare(triple.data[0],triple.data[1]) && compare(triple.data[1],triple.data[2])){
        return TRUE;
    }else{
        return FALSE;
    }
}

template<typename T, typename Cmp>
int aaa(const T &a, const T &b, Cmp cmp);

template <typename T>
Status Max (Triple<T> triple, T &e, Status (*compare)(T t1,T t2)){
    if(compare(triple.data[0],triple.data[1])){
        if(compare(triple.data[0],triple.data[2])){
            e = triple.data[0];
        }else{
            e = triple.data[2];
        }
    }else{
        if(compare(triple.data[1],triple.data[2])){
            e = triple.data[1];
        }else{
            e = triple.data[2];
        }
    }
    return OK;
}

template <typename T>
Status Min (Triple<T> triple, T &e, Status (*compare)(T t1,T t2)){
    if(!compare(triple.data[0],triple.data[1])){
        if(!compare(triple.data[0],triple.data[2])){
            e = triple.data[0];
        }else{
            e = triple.data[2];
        }
    }else{
        if(!compare(triple.data[1],triple.data[2])){
            e = triple.data[1];
        }else{
            e = triple.data[2];
        }
    }
    return OK;
}

template <typename T>
Status ShowTriple (Triple<T> triple){
    if(triple.data){
        for(int i=0;i<3;i++){
            std::cout << triple.data[i] << std::endl;
        }
        return OK;
    }else{
        exit(OVERFLOW);
    }
}