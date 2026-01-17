#include <iostream>
using namespace std;

class LinkStack {
public:
    LinkStack() : cnt_(0) {
        head_ = new Node();
    }

    ~LinkStack() {
        Node *p = head_;
        while (p != nullptr) {
            head_ = head_->next_;
            delete p;
            p = head_;
        }
    }

public:
    void push(int val) {
        Node *node = new Node(val);
        node->next_ = head_->next_;
        head_->next_ = node;

        cnt_++;
    }

    void pop() {
        if (head_->next_ == nullptr) {
            throw "stack is empty!";
        }
        Node *p = head_->next_;
        head_->next_ = p->next_;
        delete p;

        cnt_--;
    }

    int top() const {
        if (head_->next_ == nullptr) {
            throw "stack is empty!";
        }
        return head_->next_->data_;
    }

    bool empty() {
        return head_->next_ == nullptr;
    }

    // int size() {
    //	if (head_->next_ == nullptr) {
    //		return 0;
    //	}
    //	Node* p = head_->next_;
    //	int cnt = 0;
    //	while (p != nullptr) {
    //		cnt++;
    //		p = p->next_;
    //	}
    //	return cnt;
    // }

    int size() const {
        return cnt_;
    }

private:
    struct Node {
        Node(int data = 0) : data_(data), next_(nullptr) {}

        int data_;
        Node *next_;
    };

    Node *head_;
    int cnt_ = 0;
};

int main() {
    int arr[] = {12, 4, 56, 7, 89, 31, 53, 75};
    LinkStack s;
    for (int v: arr) {
        s.push(v);
    }
    cout << s.size() << endl;
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
}
