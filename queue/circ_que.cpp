#include <iostream>
using namespace std;

class Queue {
public:
    Queue(int size = 10) : cap_(size), front_(0), rear_(0) {
        rQue = new int[cap_];
    }

    ~Queue() {
        delete[] rQue;
        rQue = nullptr;
    }

public:
    void push(int val) {
        if ((rear_ + 1) % cap_ == front_) {
            expand(2 * cap_);
        }
        rQue[rear_] = val;
        rear_ = (rear_ + 1) % cap_;
    }

    void pop() {
        if (front_ == rear_) {
            throw "Queue is empty";
        }
        front_ = (front_ + 1) % cap_;
    }

    int front() const {
        if (front_ == rear_) {
            throw "Queue is empty";
        }
        return rQue[front_];
    }

    int back() const {
        if (front_ == rear_) {
            throw "Queue is empty";
        }

        return rQue[((rear_ - 1) + cap_) % cap_];
    }

    bool empty() {
        return front_ == rear_;
    }

    int size() {
        /*
        int size = 0;
        for (int i = front_; i != rear_; i = (i + 1 % cap_)) {
            size++;
        }
        return size;
        */

        return ((rear_ + cap_ - front_) % cap_);
    }

private:
    void expand(int size) {
        int *p = new int[size];
        int i = 0;
        int j = front_;
        for (; j != rear_; i++, j = (j + 1) % cap_) {
            p[i] = rQue[j];
        }
        delete[] rQue;
        rQue = p;
        cap_ = size;
        front_ = 0;
        rear_ = i;
    }

private:
    int *rQue;
    int cap_;
    int front_;
    int rear_;
};

int main() {
    Queue que;
    int arr[] = {12, 4, 56, 7, 89, 31, 53, 75};
    for (int v: arr) {
        que.push(v);
    }
    cout << que.size() << endl;

    cout << que.front() << endl;
    cout << que.back() << endl;

    que.push(100);
    que.push(200);
    que.push(300);
    cout << que.front() << endl;
    cout << que.back() << endl;

    while (!que.empty()) {
        cout << que.front() << " " << que.back() << endl;
        que.pop();
    }
}
