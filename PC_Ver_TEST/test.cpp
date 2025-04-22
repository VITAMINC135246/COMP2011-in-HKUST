#include <iostream>
using namespace std;


void multidimensional_array_function(){
    static int arr[2][3] = {1,2,3};
    cout<<"the value of arr[0][0] is: "<<arr[0][0]<<endl;
    cout<<"the value of arr[0][1] is: "<<arr[0][1]<<endl;
    cout<<"the value of arr[0][2] is: "<<arr[0][2]<<endl;
    cout<<"the value of arr[1][0] is: "<<arr[1][0]<<endl;
    cout<<"the value of arr[1][1] is: "<<arr[1][1]<<endl;
    cout<<"the value of arr[1][2] is: "<<arr[1][2]<<endl;
}


int main(){
    multidimensional_array_function();
    return 0;
}