#include <iostream>
#include <stdlib.h>
using namespace std;

struct Node {
    Node(int data = 0) : data_(data), next_(nullptr), pre_(nullptr) {}

    int data_;
    Node *next_;
    Node *pre_;
};

class DoubleCircleLink {
public:
    DoubleCircleLink() {
        head_ = new Node();
        head_->next_ = head_;
        head_->pre_ = head_;
    }

    ~DoubleCircleLink() {
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
    void InsertHead(int val) {
        Node *node = new Node(val);

        node->next_ = head_->next_;
        head_->next_->pre_ = node;
        node->pre_ = head_;
        head_->next_ = node;
    }

    void InsertTail(int val) {
        Node *p = head_->pre_;
        Node *node = new Node(val);
        p->next_ = node;
        node->pre_ = p;
        node->next_ = head_;
        head_->pre_ = node;
    }

    void Remove(int val) {
        Node *p = head_->next_;
        while (p != head_) {
            if (p->data_ == val) {
                p->pre_->next_ = p->next_;
                p->next_->pre_ = p->pre_;

                delete p;
                return;
            } else {
                p = p->next_;
            }
        }
    }

    void RemoveAll(int val) {
        Node *p = head_->next_;
        while (p != head_) {
            if (p->data_ == val) {
                p->pre_->next_ = p->next_;
                p->next_->pre_ = p->pre_;

                Node *next = p->next_;
                delete p;
                p = next;
            } else {
                p = p->next_;
            }
        }
    }

    bool Find(int val) {
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
    Node *head_;
};

int main() {
    DoubleCircleLink dlink;
    dlink.InsertHead(100);
    dlink.InsertTail(20);
    dlink.InsertTail(12);
    dlink.InsertTail(78);
    dlink.InsertTail(32);
    dlink.InsertTail(7);
    dlink.InsertTail(90);
    dlink.show();
    dlink.InsertHead(200);
    dlink.show();

    dlink.Remove(200);
    dlink.show();
    dlink.Remove(78);
    dlink.show();

    dlink.InsertHead(1);
    dlink.InsertTail(1);
    dlink.InsertTail(1);
    dlink.InsertTail(1);
    dlink.show();
    dlink.RemoveAll(1);
    dlink.show();

    if (dlink.Find(32)) {
        cout << "find 32" << endl;
    } else {
        cout << "not find 32" << endl;
    }
}
