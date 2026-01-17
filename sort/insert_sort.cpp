#include <iostream>
using namespace std;

void InsertSort(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        int val = arr[i];
        int j = i - 1;
        for (; j >= 0; j--) {
            if (arr[j] <= val) {
                break;
            }
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = val;
    }
}

int main() {
    int arr[] = {9, 3, 7, 1, 8, 2, 5, 4, 6, 0};
    int n = sizeof(arr) / sizeof(arr[0]);
    InsertSort(arr, n);
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}
