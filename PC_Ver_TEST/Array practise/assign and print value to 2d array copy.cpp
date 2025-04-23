#include <iostream>
using namespace std;

void fill2D(int arr[][3], int rows){
    for (int i = 0; i <rows; i++){
        for (int j = 0; j <3; j++){
            cout<<"pls give me a number."<<endl;
            cin>>arr[i][j];
        }
    }
}

void print2D(const int arr[][3], int rows){
    for (int i = 0; i <rows; i++){
        for (int j = 0; j <3; j++){
            cout<<arr[i][j]<<endl;
        }
    }
}

int main(){
    int rows =2;
    int arr[2][3] = {1, 2, 3};
    fill2D(arr, rows);
    print2D(arr, rows);
    return 0;
}