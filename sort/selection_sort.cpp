#include <iostream>
using namespace std;

void SelectSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int min = arr[i];
        int k = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < min) {
                min = arr[j];
                k = j;
            }
        }
        if (k != i) {
            int tmp = arr[i];
            arr[i] = arr[k];
            arr[k] = tmp;
        }
    }
}

int main() {
    int arr[] = {9, 3, 7, 1, 8, 2, 5, 4, 6, 0};
    int n = sizeof(arr) / sizeof(arr[0]);
    SelectSort(arr, n);
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}
