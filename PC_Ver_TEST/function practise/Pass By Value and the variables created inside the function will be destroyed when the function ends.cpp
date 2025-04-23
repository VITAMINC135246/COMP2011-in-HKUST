#include <iostream>
using namespace std;

void increment(int x) { // x 是 main() 里变量 num 的副本
    x += 1; 
    cout << "Inside function: x = " << x << endl;
}

int main() {
    int num = 10;
    increment(num);
    cout << "Outside function: num = " << num << endl; // num 没变
    return 0;
}


