#include <iostream>
using namespace std;


void swap(int& A, int& B){
    int temp;
    temp = A;
    A=B;
    B = temp;
}


void swap_and_sum(int a, int b, int& sum, int& A, int& B){
    
    swap(A,B);

    sum = A + B;

    cout<<"the value of two numbers after swapping is: "<<A<<","<<B<<endl;
    cout<<"and the sum is"<<sum<<endl;
}


int main(){
    int a,b;
    int sum;
    cout<<"pls give me two numbers."<<endl;
    cin>>a>>b;
    swap_and_sum(a,b,sum,a,b);

    return 0;
}