// Insertion Sort.cpp
// 04Sorting.pdf

#include <iostream>
using namespace std;

void sort(int array[], int null, int size) {
    int N = size+1;
    int swapped = 0;
    for (int i = 1; i < N; i++) {
        for (int j = i; j > 0; j--) {
            if (array[j] < array[j - 1]) {
                swap(array[j], array[j - 1]);
                ++swapped;
            }
            else {
                break;
            }
        }
        if (swapped != N-1) {
            std::cout << array[i] << " " << array[i - swapped] << std::endl;
        }
        swapped = 0;
    }    
}

int main(int argc, char* argv[])
{
    int i;
    int a[10] = { 6, 4, 7, 5, 8, 2, 3, 9, 1, 0 };
    int N = 10;

    cout << "Initial: ";
    for (i = 0; i < N; i++)
        cout << a[i];
    cout << endl;
    sort(a, 0, N - 1);
    cout << "After: ";
    for (i = 0; i < N; i++)
        cout << a[i];
    cout << endl;
    return 0;
}