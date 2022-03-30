## CHAP_2 线性表

---

### 线性表类型定义

```en
ADT List{
    data;
    relationship;
    function:
        InitList(& L)
        DestroyList(& L)
        ClearList(& L)
        ListEmpty(& L)
        ListLength(& L)
        GetElem(& L, i, &e)
        LocateElem(&L, e, compare())
        ProirElem(&L, cur_e, &pre_e)
        NetxElem(&L, cur_e, &next_e)
        ListInsert(&L, i, e)
        ListDelete(&L, i, &e)
        ListTraverse(&L, visit())
}
```

### other functions

> $A\cup B$

```C++
void union(List &la, List &lb){
    lena = ListLength(la);
    lenb = ListLength(lb);
    for(i=1;i<=lenb;i++){
        GetElem(lb,i,e);
        if(!LocateElem(la,e,equal)){
            ListInsert(la,++lena,e);
        }
    }
}
```

> Merge two ordered Lists

```C++
void MergeList(List la, List lb, List &lc){
    lena = ListLength(la);
    lenb = ListLength(lb);
    InitList(lc);
    /*
        k=1,k++ and k represents lenc+1
        k=0,++k and k represents lenc
    */
    i=j=k=1;
    while(i<=lena && j<=lenb){
        GetElem(la,i,ea);
        GetElem(lb,j,eb);
        if(ea<=eb){
            ListInsert(lc,k++,ea);
            i++;
        }else{
            ListInsert(lc,k++,eb);
            j++;
        }
    }
    while(i<=lena){
        GetElem(la,i++,ea);
        ListInsert(lc,k++,ea);
    }
    while(j<=lenb){
        GetElem(lb,j++,eb);
        ListInsert(lc,k++,eb);
    }
}
```