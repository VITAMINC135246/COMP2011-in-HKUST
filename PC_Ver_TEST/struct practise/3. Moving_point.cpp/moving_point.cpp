// 从lec里学到point-test.cpp，  point-distance.cpp ， point.h， 尝试写一个完成一个 move_point(Point& p,double dx,double dy)：把点平移后返回 void。测试：让用户输入 A 点，再输入位移向量，输出新坐标。
// 需要的file都在文件夹里，主要的都应该写在这。
// poin_test 已经经过稍加修改


#include <iostream>
#include <cstring>
using namespace std;


void move_point(Point& p, double dx, double dy) {
    p.x += dx;
    p.y += dy;
    cout<<"the point now is"<<"("<<p.x<<", "<<p.y<<")";
}


