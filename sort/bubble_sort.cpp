#include <iostream>
using namespace std;

void BubbleSort(int arr[], int size) {
    for (int i = 0; i <= size - 2; i++) {
        bool flag = false;
        for (int j = 0; j <= size - 2 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                flag = true;
            }
        }
        if (flag == false) {
            return;
        }
    }
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

    BubbleSort(arr, 10);
    for (int v: arr) {
        cout << v << " ";
    }
    cout << endl;
}
