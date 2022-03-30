#include <iostream>

using namespace std;

void fun(int a[]){
    a[0]=10;
}

int main(){
    int arr[4] = {1,2,3,4};
    fun(arr);
    cout<<arr[0]<<endl;
    return 0;
}