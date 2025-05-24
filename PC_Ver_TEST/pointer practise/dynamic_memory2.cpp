#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;


int main(){
    int* p=new int(42); delete p; cout<<*p;
}
