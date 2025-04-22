#include <iostream>
using namespace std;
const char NULL_CHAR = '\0';

bool is_letter(char c){
    if ((c >='a' && c <= 'z') ||(c >='A' && c <= 'Z') ){
        return true;}
    else return false;
    }


bool to_lower_case(char s[]){
    int i = 0;
    while (s[i] != '\0'){
        if(is_letter){
            if (s[i] >='a' && s[i] <= 'z'){
                s[i] = s[i];
            }
            if(s[i] >='A' && s[i] <= 'Z'){
                s[i] = s[i] - 32;
            }
        }
        else {return false;}
        i++;
    }
    return true;
}

int substring(const char s[], const char pattern[], int& start, int& end){
    int result1 = 0;
    int result2 = 0;
    for(int i = 0; i != '\0'; i++){
    while (s[i] == start){
        int j = 0;
        while(s[j] == end){
            result2 = (j-i) +1;
            result1 = (result2 > result1)? result2: result1;
        }
        j++;}
    }
    return result1;
    
}

void just_letters(char s[]){
    for (int i = 0; i != '\0'; i++){
        if (is_letter == 0){
            
        }


    }
}

int main()
{
const int N = 100;
char s1[N], s2[N], str_sum[N], pattern[N];
int start, end, length;
while (true)
{
cout << "Enter a string : ";
cin >> s1;
cout << "Enter the substring to search in the form of \"a*b\": ";
cin >> pattern;
length = substring(s1, pattern, start, end);
cout << "substring: " << length << " ; " << start << " , " << end << endl;
just_letters(s1);
cout << "s1 after calling just_letters: " << s1 << endl;
to_lower_case(s1);
cout << "s1 after calling to_lower_case: " << s1 << endl;
cout << "Enter another string to add: ";
cin >> s2;
just_letters(s2);
to_lower_case(s2);
add_strings(s1, s2, str_sum);
cout << str_sum endl << "\n\n--------------------------------" << endl;
}
return 0;
}