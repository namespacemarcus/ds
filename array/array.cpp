#include <iostream>
#include <time.h>
#include <string.h>
using namespace std;

class Array {
public:
    Array(int size = 10) : mCur(0), mCap(size) {
        mpArr = new int[mCap];
    }

    ~Array() {
        delete[] mpArr;
        mpArr = nullptr;
    }

public:
    void push_back(int val) {
        if (mCur == mCap) {
            expand(2 * mCap);
        }
        mpArr[mCur++] = val;
    }

    void pop_back() {
        if (mCur == 0) {
            return;
        }
        mCur--;
    }

    void insert(int pos, int val) {
        if (pos < 0 || pos > mCur) {
            return;
        }
        if (mCur == mCap) {
            expand(2 * mCap);
        }
        for (int i = mCur - 1; i >= pos; i--) {
            mpArr[i + 1] = mpArr[i];
        }
        mpArr[pos] = val;

        mCur++;
    }

    void erase(int pos) {
        if (pos < 0 || pos > mCur - 1) {
            return;
        }
        for (int i = pos + 1; i <= mCur - 1; i++) {
            mpArr[i - 1] = mpArr[i];
        }
        mCur--;
    }

    int find(int val) {
        for (int i = 0; i < mCur; i++) {
            if (mpArr[i] == val) {
                return i;
            }
        }
        return -1;
    }

    void show() const {
        for (int i = 0; i < mCur; i++) {
            cout << mpArr[i] << " ";
        }
        cout << endl;
    }

private:
    void expand(int size) {
        int *p = new int[size];
        memcpy(p, mpArr, sizeof(int) * mCap);
        delete[] mpArr;

        mpArr = p;
        mCap = size;
    }

private:
    int *mpArr;
    int mCap;
    int mCur;
};

int main() {
    Array arr;
    srand(time(0));
    for (int i = 0; i < 10; i++) {
        arr.push_back(rand() % 100);
    }
    arr.show();

    arr.pop_back();
    arr.show();

    arr.insert(0, 100);
    arr.show();

    arr.insert(10, 200);
    arr.show();

    int pos = arr.find(100);
    if (pos != -1) {
        arr.erase(pos);
        arr.show();
    }
    return 0;
}
