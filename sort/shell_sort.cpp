#include <iostream>
using namespace std;

void ShellSort(int arr[], int size) {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            int val = arr[i];
            int j = i - gap;
            for (; j >= 0; j -= gap) {
                if (arr[j] <= val) {
                    break;
                }
                arr[j + gap] = arr[j];
            }
            arr[j + gap] = val;
        }
    }
}

int main() {
    int arr[] = {9, 3, 7, 1, 8, 2, 5, 4, 6, 0};
    int n = sizeof(arr) / sizeof(arr[0]);
    ShellSort(arr, n);
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}
