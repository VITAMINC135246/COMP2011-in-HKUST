#include <iostream>     /* File: point-test.cpp */
using namespace std;
#include "point.h" 
#include "point-distance.cpp" 
//下一行为增添内容
#include "moving_point.cpp" 

int main()       /* To find the length of the sides of a triangle */
{
    Point a, b, c;
    //下一行为增添内容
    double dx, dy;
    cout << "Enter the co-ordinates of point A: "; cin >> a.x >> a.y;
    cout << "Enter the co-ordinates of point B: "; cin >> b.x >> b.y;
    cout << "Enter the co-ordinates of point C: "; cin >> c.x >> c.y;
    //下一行为增添内容
    cout << "Enter the displacement vector u wanted for all points: "; cin >> dx >>dy;

    cout << endl << "Results: " << endl;
    print_distance(a, b);
    print_distance(b, c);
    print_distance(c, a);

    move_point(a, dx, dy);
    move_point(b, dx, dy);
    move_point(c, dx, dy);
    return 0;
}
