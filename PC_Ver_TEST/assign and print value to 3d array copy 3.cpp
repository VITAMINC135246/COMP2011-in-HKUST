#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void fill2D(int arr[][3][4], int rows){
    srand(time(0)); // 设置随机数种子
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < 3; j++){
            for (int k = 0; k < 4; k++){
                arr[i][j][k] = rand() % 100; // 生成0到99之间的随机数
            }
        }
    }
}

void print2D(const int arr[][3][4], int rows){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < 3; j++){
            for (int k = 0; k < 4; k++){
                cout << arr[i][j][k] << endl;
            }
        }
    }
}

int main(){
    int rows =2;
    int arr[2][3][4] = {1, 2, 3};
    fill2D(arr, rows);
    print2D(arr, rows);
    return 0;
}