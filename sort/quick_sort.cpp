#include <iostream>
using namespace std;

int Partition(int arr[], int left, int right) {
    int pivot = arr[left];

    while (left < right) {
        while (left < right && arr[right] >= pivot) {
            right--;
        }
        if (left < right) {
            arr[left] = arr[right];
        }
        while (left < right && arr[left] <= pivot) {
            left++;
        }
        if (left < right) {
            arr[right] = arr[left];
        }
    }
    arr[left] = pivot;
    return left;
}

void QuickSort(int arr[], int left, int right) {
    if (left >= right) {
        return;
    }
    int pos = Partition(arr, left, right);
    QuickSort(arr, left, pos - 1);
    QuickSort(arr, pos + 1, right);
}

int main() {
    srand(time(NULL));
    int arr[10];
    for (int i = 0; i < 10; i++) {
        arr[i] = rand() % 100 + 1;
    }
    for (int v: arr) {
        cout << v << " ";
    }
    cout << endl;

    QuickSort(arr, 0, 9);
    for (int v: arr) {
        cout << v << " ";
    }
    cout << endl;
}
