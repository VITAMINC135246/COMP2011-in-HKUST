#include <iostream>

using namespace std;

//写出 Point 型变量 a、b 的定义代码，不做初始化。
struct Point{
    double a;
    double b;//此时，a, b是垃圾值
};

//让用户键入一个点 (x,y) 并打印成 (x, y) 形式。禁止使用 printf。
int main(){
    Point point;
    cin >> point.a >> point.b;
    cout << "(" << point.a << ", " << point.b << ")" << endl;
}
