#include <iostream>
#include <cstring>
using namespace std;

//定义一个 Book 结构体，含 title(char[40])、price(double) 和 next(指向 Book 的指针)。注意 next 必须写在定义体里。

struct Book{
    char title[40]; 
    double price;
    struct Book* next; //在c++ 中，结构体的名称本身就是类型名，因此可以直接写Book * next
};

// 附加题：写一个链表[linked list], 超纲，可以先看到pointer里的linked list 再写。
int main() {
    // 创建两个 Book 节点
    Book book1, book2;

    // 初始化 book1
    strcpy(book1.title, "C++ Programming");
    book1.price = 59.99;
    book1.next = &book2; // book1 的 next 指向 book2

    // 初始化 book2
    strcpy(book2.title, "Data Structures");
    book2.price = 79.99;
    book2.next = nullptr; // book2 是链表的最后一个节点

    // 遍历链表
    Book* current = &book1;
    while (current != nullptr) {
        cout << "Title: " << current->title << ", Price: $" << current->price << endl;
        current = current->next; // 移动到下一个节点
    }

    return 0;
}