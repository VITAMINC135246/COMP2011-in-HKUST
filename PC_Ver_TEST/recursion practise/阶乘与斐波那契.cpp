//（基础）用递归分别实现 factorial 与 fibonacci，体会 base case 必须正确。
//（扩展）比较递归版与循环版在大输入下的运行效率差异。




#include <iostream>
using namespace std;

int factorial (int n){
    if (n == 1 || n == 0){ //曾经在这里犯过的错：n不可能同时等于1或者0， 所以不能写&&）
        return 1;
    }
    else if (n<0){
        return -1; //曾经在这里犯过的错:漏掉了n是负数的情况）
    }
    else{
        return n * factorial(n-1);
    }
}

int fibonacci(int n){
    int fn_0= 0;
    int fn_1 =1;
    int fn;

    if( n == 0){
        fn = fn_0;
    }

    else if (n == 1)
    {
        fn = fn_1;
    }

    else{
        /*for(int i = 2; i <= n; i++){
            fn = fn_1 + fn_0;

            fn_0 = fn_1;
            fn_1 = fn;

        }*/
       return fibonacci(n-1) + fibonacci (n-2);
    }
    

}
int main(){

    int n;

    cout<<"pls give me a number , i will tell u the factorial of it,"
    <<"and the number in fibonacci number at that position at the same time"<<endl;
    cin>>n;
    cout<<"the factorial of "<<n<<" is "<<factorial(n)<<endl;
    cout<<"the number in fibonacci number at position "<<n<<" is "<<fibonacci(n)<<endl;




    return 0;
}



//notes:
//1. 首先，写一个recursion 必须要有base case，否则会无限循环下去，直到stack overflow；
//2. 所以，要确保参数朝着“结束条件前进”，换言之，条件和base case要遥相呼应
//3. 其次，recursion的效率并不高，因为每次调用都要保存现场，所以在大输入下，效率会很低；