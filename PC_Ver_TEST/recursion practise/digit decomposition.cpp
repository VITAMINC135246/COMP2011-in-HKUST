//写一个递归函数，输入一个正整数 n，输出它的每一位（从高位到低位或反过来都行）。
//进一步，用递归数位拆解判断一个数是否回文数（例如 12321）



#include <iostream>
using namespace std;

void print_number(int n, int& counter){
    if (n == 0){
        cout<<"0"<<endl;
        counter++;
        return;
    }
    if (1 <= n && n <= 9){
        cout<<n;
        counter++;
        return;
    }
    
    print_number(n/10, counter);
    cout<<n%10;
    counter++;
    }




bool Palindrometest(int n){
    int counter = 0;
    print_number(n, counter);
    char char_array[counter+1];

    int temp = n; 
    int index = 0;
    
    while (temp > 0) {
        char_array[index++] = temp % 10 + '0';  // 
        temp /= 10;
    }


    int j = 0;
    int k = counter-1;

    for(; j < k; j++, k--) {
        if (char_array[j] != char_array[k]) { // 只在不匹配时返回 false
            return false;
        }
    }
    return true; // 全部匹配才返回 true
    
}

int main(){

    int n; 
    
    cout<<"give me a number pls, i will tell it is a palindrome number or not!"<<endl;
    cin>>n;



    bool result = Palindrometest(n); 
    if (result) {
        cout << "It is a palindrome!" << endl;
    } else {
        cout << "Sorry, it isn't a palindrome!" << endl;
    }

    return 0;
}






















/* GPT写的
#include <iostream>
using namespace std;

// 递归打印 n 的每一位（从高到低）
void print_number(int n) {
    if (n < 10) {
        cout << n << endl;
        return;
    }
    print_number(n / 10);
    cout << n % 10 << endl;
}

// 递归辅助函数，用于判断回文
bool is_palindrome_helper(int n, int &reversed, int original) {
    if (n == 0) return original == reversed; // 递归结束时比较

    reversed = reversed * 10 + (n % 10); // 逆序构建新数字
    return is_palindrome_helper(n / 10, reversed, original);
}

// 判断是否为回文数
bool is_palindrome(int n) {
    if (n < 0) return false; // 负数不可能是回文数
    int reversed = 0;
    return is_palindrome_helper(n, reversed, n);
}

// 主函数
int main() {
    int n; 
    cout << "Give me a number, I will check if it is a palindrome!" << endl;
    cin >> n;

    cout << "The digits of " << n << " are:" << endl;
    print_number(n); // 递归打印数字每一位

    if (is_palindrome(n)) {
        cout << "It is a palindrome!" << endl;
    } else {
        cout << "Sorry, it isn't a palindrome!" << endl;
    }

    return 0;
}
*/