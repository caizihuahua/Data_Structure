#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct {
    // 1234.567
    // num={7,6,5,4,3,2,1}  dot=3
    vector<int> num;
    // the position of the dot
    int dot;
} Bign;

// alignment of the bign with precision
void ali(Bign& bign,int precision){
    while(bign.dot<precision){
        bign.num.insert(bign.num.begin(),0);
        bign.dot++;
    }
    if(bign.dot>precision){
        reverse(bign.num.begin(),bign.num.end());
        while(bign.dot>precision){
            bign.num.pop_back();
            bign.dot--;
        }
        reverse(bign.num.begin(),bign.num.end());
    }
}

// initiation with integer
void init_b(Bign& b ,int n){
    while(n){
        b.num.push_back(n%10);
        n /= 10;
    }
    b.dot = 0;
}

// b1+b2, result maintained in b1
void plus_b(Bign& b1,Bign& b2,int precision){
    ali(b1,precision);
    ali(b2,precision);
    int carry = 0;
    int index = 0;
    while(index<b2.num.size() && index<b1.num.size()){
        int tmp = carry + b1.num.at(index) + b2.num.at(index);
        carry = tmp/10;
        b1.num.at(index) = tmp%10;
        index++;
    }
    while(index < b2.num.size()){
        int tmp = carry + b2.num.at(index);
        carry = tmp/10;
        b1.num.push_back(tmp%10);
        index++;
    }
    while(index < b1.num.size()){
        int tmp = carry + b1.num.at(index);
        carry = tmp/10;
        b1.num.at(index) = tmp%10;
        index++;
    }
    if(carry!=0){
        b1.num.push_back(carry);
    }
}

// b1-b2 b1 must bigger than b2
// result maintained in b1
void minus_b(Bign& b1,Bign& b2,int precision){
    ali(b1,precision);
    ali(b2,precision);
    for(int i=0;i<b2.num.size();i++){
        int tmp = b1.num.at(i) - b2.num.at(i);
        if(tmp < 0){
            tmp += 10;
            // -1 ? this is a problem
            b1.num.at(i+1)--;
        }
        b1.num.at(i) = tmp;
    }
    while(b1.num.size()>precision){
       if(b1.num.back()==0){
           b1.num.pop_back();
       }else{
           break;
       }
   }
}

// n must less than 10
// no initiation with res
void _mul_10(Bign b,int n,Bign& res){
    int carry = 0;
    for(int i=0;i<b.num.size();i++){
        int tmp = carry + b.num.at(i) * n;
        res.num.push_back(tmp%10);
        carry = tmp/10;
    }
    while(carry!=0){
        res.num.push_back(carry%10);
        carry /= 10; 
    }
    res.dot = b.dot;
}


void _mul_bb(Bign& b1,Bign& b2,int precesion){
    Bign res;
    res.dot = 0;
    int carry = 0;
    for(int i=0;i<b2.num.size();i++){
        Bign bigtmp;
        _mul_10(b1,b2.num.at(i),bigtmp);
        bigtmp.dot -= i;
        plus_b(res,bigtmp,precesion);
    }
    b1.num.clear();
    for(int i=0;i<res.num.size();i++){
        b1.num.push_back(res.num.at(i));
    }
    b1.dot = res.dot;
}

void mul_b(Bign& b1,int n,int precision){
    Bign b2;
    init_b(b2,n);
    _mul_bb(b1,b2,precision);
}

void div_b(Bign& b,int n,int precision){
    vector<int> res;
    ali(b,precision);
    int tmp = 0;
    for(int i=b.num.size()-1;i>=0;i--){
        tmp += b.num.at(i);
        while(tmp/n == 0){
            res.push_back(0);
            i--;
            if(i<0) break;
            tmp = tmp*10+b.num.at(i);
        }
        res.push_back(tmp/n);
        tmp = 10*(tmp%n);
    }
    while(res.size()!=b.num.size()){
        res.pop_back();
    }
    b.num.clear();
    while(res.size()!=0){
        b.num.push_back(res.back());
        res.pop_back();
    }
    b.dot = precision;
   while(b.num.size()>precision){
       if(b.num.back()==0){
           b.num.pop_back();
       }else{
           break;
       }

   }
}

void show(Bign& b){
    for(int i=b.num.size()-1;i>=b.dot;i--){
        cout << b.num.at(i);
    }
    cout << ".";
    for(int i=b.dot-1;i>=0;i--){
        cout<<b.num.at(i);
    }
    cout<<endl;
}

bool num_eql_zero(Bign& b){
    for(int i=0;i<b.num.size();i++){
        if(b.num.at(i)!=0){
            return false;
        }
    }
    return true;
}


int main(){
    Bign res;
    init_b(res,0);
    int precision = 1000;

    int index = 1;
    while(true){
        int tmp = index*2-1;
        Bign b1,b2;
        init_b(b1,1);
        init_b(b2,1);
        div_b(b1,tmp,precision);
        div_b(b2,tmp,precision);
        while(tmp!=0){
            div_b(b1,5,precision);
            div_b(b2,239,precision);
            tmp--;
        }
        mul_b(b1,16,precision);
        mul_b(b2,4,precision);
        minus_b(b1,b2,precision);
        if(num_eql_zero(b1)){
            break;
        }
        if(index%2==1){
            plus_b(res,b1,precision);
        }else{
            minus_b(res,b1,precision);
        }
        index++;
        show(res);
    }
    show(res);
    return 0;

}