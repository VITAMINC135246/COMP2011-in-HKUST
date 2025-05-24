#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

void alloc_demo(){
    double* a = new double;
    *a = M_PI;
    cout<<"*a is"<< *a << " and the address in heap is "<< a<< endl;
    delete a;
}


int main(){
    alloc_demo();
    return 0;
}