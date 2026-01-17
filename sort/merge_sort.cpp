#include <iostream>
using namespace std;

void Merge(int arr[], int begin, int mid, int end) {
    int *p = new int[end - begin + 1];
    int idx = 0;
    int i = begin;
    int j = mid + 1;
    while (i <= mid && j <= end) {
        if (arr[i] <= arr[j]) {
            p[idx++] = arr[i++];
        } else {
            p[idx++] = arr[j++];
        }
    }
    while (i <= mid) {
        p[idx++] = arr[i++];
    }
    while (j <= end) {
        p[idx++] = arr[j++];
    }
    for (i = begin, j = 0; i <= end; i++, j++) {
        arr[i] = p[j];
    }

    delete[] p;
}

void MergeSort(int arr[], int begin, int end) {
    if (begin >= end) {
        return;
    }
    int mid = (begin + end) / 2;
    MergeSort(arr, begin, mid);
    MergeSort(arr, mid + 1, end);
    Merge(arr, begin, mid, end);
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

    MergeSort(arr, 0, 9);
    for (int v: arr) {
        cout << v << " ";
    }
    cout << endl;
}
