#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void RadixSort(int arr[], int size) {
    int maxData = arr[0];
    for (int i = 1; i < size; i++) {
        if (abs(arr[i]) > maxData) {
            maxData = abs(arr[i]);
        }
    }
    int len = to_string(maxData).size();
    vector<vector<int>> vecs;
    int mod = 10;
    int dev = 1;
    for (int i = 0; i < len; mod *= 10, dev *= 10, i++) {
        vecs.resize(20);
        for (int j = 0; j < size; j++) {
            int number = (arr[j] % mod) / dev + 10;
            vecs[number].push_back(arr[j]);
        }
        int idx = 0;
        for (vector<int> vec: vecs) {
            for (int v: vec) {
                arr[idx++] = v;
            }
        }
        vecs.clear();
    }
}

int main() {
    int arr[] = {9, 3, -7, 1, 8, -2, 5, -4, 6, 0};
    int n = sizeof(arr) / sizeof(arr[0]);
    RadixSort(arr, n);
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}
