#include <iostream>		/* File: bsearch-main.cpp */
using namespace std;	

const int NOT_FOUND = -1;      /* File: bsearch.cpp */

int bsearch(const int data[ ], // sorted in ascending order
            int first,         // lower bound index
            int last,          // upper bound index
            int value)         // value to search
{
    if (last < first)          // Base case #1
        return NOT_FOUND;

    int mid = (first + last)/2;

    if (data[mid] == value)
        return mid;             // Base case #2

    else if (data[mid] > value) // Search the lower half
        return bsearch(data, first, mid-1, value);

    else                        // Search the upper half
        return bsearch(data, mid+1, last, value);
}


int data[] = { 3, 5, 7, 9, 11, 13, 15, 17 };

int main()	
{
    int x;
    int num_data = sizeof(data)/sizeof(int);

    while (cin >> x)
	cout << bsearch(data, 0, num_data-1, x) << endl;
	
    return 0;
}
