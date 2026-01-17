#include <functional>
#include <iostream>
#include <string.h>
using namespace std;

class PriorityQueue {
public:
    using Compare = function<bool(int, int)>;

    PriorityQueue(int cap = 20, Compare comp = greater<int>())
        : size_(0),
          cap_(cap),
          comp_(comp) {
        que_ = new int[cap_];
    }

    PriorityQueue(Compare comp) : size_(0), cap_(20), comp_(comp) {
        que_ = new int[cap_];
    }

    ~PriorityQueue() {
        delete[] que_;
        que_ = nullptr;
    }

public:
    void push(int val) {
        if (size_ == cap_) {
            int *p = new int[2 * cap_];
            memcpy(p, que_, cap_ * sizeof(int));
            delete[] que_;
            que_ = p;
            cap_ *= 2;
        }
        if (size_ == 0) {
            que_[size_] = val;
        } else {
            shiftUp(size_, val);
        }
        size_++;
    }

    void pop() {
        if (size_ == 0) {
            throw "container is empty!";
        }
        size_--;
        if (size_ > 0) {
            shiftDown(0, que_[size_]);
        }
    }

    bool empty() const {
        return size_ == 0;
    }

    int top() const {
        if (size_ == 0) {
            throw "container is empty!";
        }
        return que_[0];
    }

    int size() const {
        return size_;
    }

private:
    void shiftUp(int i, int val) {
        while (i > 0) {
            int father = (i - 1) / 2;
            if (comp_(val, que_[father])) {
                que_[i] = que_[father];
                i = father;
            } else {
                break;
            }
        }
        que_[i] = val;
    }

    void shiftDown(int i, int val) {
        while (i <= (size_ / 2 - 1)) {
            int child = 2 * i + 1;
            if (child + 1 < size_ && comp_(que_[child + 1], que_[child])) {
                child = child + 1;
            }
            if (comp_(que_[child], val)) {
                que_[i] = que_[child];
                i = child;
            } else {
                break;
            }
        }
        que_[i] = val;
    }

private:
    int *que_;
    int size_;
    int cap_;
    Compare comp_;
};

int main() {
    PriorityQueue que1;
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        que1.push(rand() % 100);
    }
    while (!que1.empty()) {
        cout << que1.top() << " ";
        que1.pop();
    }
    cout << endl;

    PriorityQueue que2([](int a, int b) { return a < b; });
    for (int i = 0; i < 10; i++) {
        que2.push(rand() % 100);
    }
    while (!que2.empty()) {
        cout << que2.top() << " ";
        que2.pop();
    }
    cout << endl;
}
