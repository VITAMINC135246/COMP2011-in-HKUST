#include <iostream>
using namespace std;
int X(int &a, int &b)
{
    return ++a + b--;
}
int &Y(int &c, int d)
{
    int &tmp = d;
    d += c;
    c -= tmp;
    return c;
}
int Z(const int &e, int &f)
{
    int tmp = e;
    const int &tmp2 = f;
    f += e;
    tmp -= tmp2;
    return tmp;
}
int main()
{
    int a = 2, b = 5;
    const int c = 3;
    cout << Z(Y(a, c), Y(b, c)) << " ";
    cout << a << " ";
    cout << b << endl;
    return 0;
}