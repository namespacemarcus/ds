#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

class CircleLink {
public:
    CircleLink() {
        head_ = new Node();
        tail_ = head_;
        head_->next_ = head_;
    }

    ~CircleLink() {
        Node *p = head_->next_;
        while (p != head_) {
            head_->next_ = p->next_;
            delete p;
            p = head_->next_;
        }
        delete head_;
    }

public:
    void InsertTail(int val) {
        Node *node = new Node(val);
        node->next_ = tail_->next_;
        tail_->next_ = node;

        tail_ = node;
    }

    void InsertHead(int val) {
        Node *node = new Node(val);
        node->next_ = head_->next_;
        head_->next_ = node;
        if (node->next_ == head_) {
            tail_ = node;
        }
    }

    void Remove(int val) {
        Node *pre = head_;
        Node *p = head_->next_;
        while (p != head_) {
            if (p->data_ == val) {
                pre->next_ = p->next_;
                delete p;
                if (pre->next_ == head_) {
                    tail_ = pre;
                }
                return;
            } else {
                p = p->next_;
                pre = pre->next_;
            }
        }
    }

    bool find(int val) {
        Node *p = head_->next_;
        while (p != head_) {
            if (p->data_ == val) {
                return true;
            } else {
                p = p->next_;
            }
        }
        return false;
    }

    void show() {
        Node *p = head_->next_;
        while (p != head_) {
            cout << p->data_ << " ";
            p = p->next_;
        }
        cout << endl;
    }

private:
    struct Node {
        Node(int data = 0) : data_(data), next_(nullptr) {}

        int data_;
        Node *next_;
    };

    Node *head_;
    Node *tail_;
};

int main() {
    CircleLink clink;
    srand(time(NULL));
    clink.InsertHead(100);
    for (int i = 0; i < 10; i++) {
        clink.InsertTail(rand() % 100);
    }
    clink.InsertTail(200);
    clink.show();

    clink.Remove(200);
    clink.show();

    if (clink.find(200)) {
        cout << "find it!" << endl;
    } else {
        cout << "not find" << endl;
    }
}
