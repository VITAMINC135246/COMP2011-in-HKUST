#include <iostream>
#include <cmath>
using namespace std;


// Function to convert decimal to octal using recursion
int decimalToOctal(int n, int index) {
    
    if (n/8 == 0) {
        int y = n % 8;
        return y*pow(10,index); // Base case: stop recursion when n is 0
    }

    int x = n % 8; // Get the remainder of n divided by 8


    return ((x*pow(10,index)) + decimalToOctal(n / 8, index+1)); // Recursive call with n divided by 8

}

int main() {
    int decimalNumber;
    int index = 0;
    cout << "Enter a number pls ";
    cin >> decimalNumber;

    if (decimalNumber == 0) {
        cout << 0; // Special case for input 0
    } else {
        cout << "The octal representation is: "<<decimalToOctal(decimalNumber, index);
    }
    cout << endl;

    return 0;
}