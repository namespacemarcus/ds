#include <iostream>
using namespace std;

class LinkQueue {
public:
    LinkQueue() {
        head_ = new Node();
        head_->next_ = head_;
        head_->pre_ = head_;
    }

    ~LinkQueue() {
        Node *p = head_->next_;
        while (p != head_) {
            head_->next_ = p->next_;
            p->next_->pre_ = head_;
            delete p;

            p = head_->next_;
        }
        delete head_;
        head_ = nullptr;
    }

public:
    void push(int val) {
        Node *p = head_->pre_;
        Node *node = new Node(val);
        p->next_ = node;
        node->pre_ = p;
        node->next_ = head_;
        head_->pre_ = node;

        size_++;
    }

    void pop() {
        Node *p = head_->next_;
        head_->next_ = p->next_;
        p->next_->pre_ = head_;
        delete p;

        size_--;
    }

    int front() {
        if (head_->next_ == head_) {
            throw "Queue is empty!";
        }
        return head_->next_->data_;
    }

    int back() {
        if (head_->next_ == head_) {
            throw "Queue is empty!";
        }
        return head_->pre_->data_;
    }

    bool empty() {
        return head_->next_ == head_;
    }

    int size() {
        return size_;
    }

private:
    struct Node {
        Node(int data = 0) : data_(data), next_(nullptr), pre_(nullptr) {}

        int data_;
        Node *next_;
        Node *pre_;
    };

    Node *head_;

    int size_ = 0;
};

int main() {
    LinkQueue que;
    int arr[] = {12, 4, 56, 7, 89, 31, 53, 75};
    for (int v: arr) {
        que.push(v);
    }
    cout << que.size() << endl;  // 8

    cout << que.front() << endl; // 12
    cout << que.back() << endl;  // 75

    que.push(100);
    que.push(200);
    que.push(300);
    cout << que.front() << endl; // 12
    cout << que.back() << endl;  // 300

    while (!que.empty()) {
        cout << que.front() << " " << que.back() << endl;
        que.pop();
    }
}
