#include <iostream>
#include <cstring>
using namespace std;

    bool palindrome(const char x[]) {
        int j = 0;
        // An index reading the array from top (left)
        int k = strlen(x)- 1; // An index reading the array from bottom (right)
        for ( ; j < k; ++j,--k)
        if (x[j] != x[k])
        return false;
        return true;
        }

int main(){

    const int MAX_LINE_LEN = 255; char whole_line[MAX_LINE_LEN+1];
    

    cout<<"give me an intersting word pls, i will tell it is a palindrome number or not!"<<endl;
    
    while (cin.getline(whole_line, MAX_LINE_LEN+1, '\n')//cin.getline的具体作用在于：用户输入不限制于空格。
    //以这行代码为例子，用户输入的单词每一个都会计入whole_line这个C String中，直到达到储量上限，MAX_Line_LEN,或是看到'\n'回车键
    || cin.gcount() == MAX_LINE_LEN) // Input ends with max #chars


    {
        cout << whole_line << endl
        << boolalpha << palindrome(whole_line) << endl;
        cin.clear();
        }
        return 0;
        }


/*NOTES:
1. 最主要的思想来做回文数 的问题。一是将用户的输入转换为cstring，无论是数字还是word。二就是用for loop来做判断，返回值即可；
*/