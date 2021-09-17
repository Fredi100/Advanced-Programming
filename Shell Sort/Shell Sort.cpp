// Shell Sort.cpp
// 04Sorting.pdf

#include <iostream>
using namespace std;

void sort(int array[], int null, int size) {
    int N = size + 1;
    int incs[3] = {13, 4, 1};
    
    int swapped = 0;

    for (int k = 0; k < 3; k++){
        int h = incs[k];
        for (int i = h; i < N; i++) {
            for (int j = i; j >= h; j-= h) {
                if (array[j] < array[j - h]) {
                    swap(array[j], array[j - h]);
                    ++swapped;
                }
                else {
                    break;
                }
            }
            cout << array[i] << " " << array[i - (swapped * h)] << endl;
            swapped = 0;
        }
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