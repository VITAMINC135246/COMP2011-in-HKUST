#include <iostream>
using namespace std;


void calc_expression(int a, int b, int& diff, int& product, float& float_quotient){
    

    cout<<"the diff of two numbers after swapping is: "<< (diff = a-b)<<"\n"
    << "the product of two numbers after swapping is: "<< (product = a*b)<<"\n"
    << "and the float_quotient is: "<< (float_quotient = (a/(float)b))<<endl;
    
}


int main(){
    int a,b;
    int diff, product;
    float float_quotient;
    cout<<"pls give me two numbers."<<endl;
    cin>>a>>b;
    calc_expression(a,b,diff,product,float_quotient);

    return 0;
}