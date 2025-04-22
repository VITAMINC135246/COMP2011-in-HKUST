#include <iostream>
using namespace std;


int factorial(int n)    /* factorial.cpp */
{
    if (n < 0)          // Error checking
        return -1;
    else if (n == 0)    // Base case; ending case too!
        return 1;
    else                // Recursive case
        return n * factorial(n-1);
}

int main(){
    int n;
    cin>>n;
    cout<<factorial(n);
    return 0;
}
