#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

struct Node {
    Node(int data = 0) : data_(data), next_(nullptr) {};
    int data_;
    Node *next_;
};

class Clink {
public:
    Clink() {
        head_ = new Node();
    }

    ~Clink() {
        Node *p = head_;
        while (p != nullptr) {
            head_ = head_->next_;
            delete p;
            p = head_;
        }
        head_ = nullptr;
    }

public:
    void InsertTail(int val) {
        Node *p = head_;
        while (p->next_ != nullptr) {
            p = p->next_;
        }

        Node *node = new Node(val);
        p->next_ = node;
    }

    void InsertHead(int val) {
        Node *node = new Node(val);
        node->next_ = head_->next_;
        head_->next_ = node;
    }

    void Remove(int val) {
        Node *p = head_->next_;
        Node *pre = head_;
        while (p != nullptr) {
            if (p->data_ == val) {
                pre->next_ = p->next_;
                delete p;
                return;
            } else {
                p = p->next_;
                pre = pre->next_;
            }
        }
    }

    void RemoveAll(int val) {
        Node *p = head_->next_;
        Node *pre = head_;
        while (p != nullptr) {
            if (p->data_ == val) {
                pre->next_ = p->next_;
                delete p;
                p = pre->next_;
            } else {
                p = p->next_;
                pre = pre->next_;
            }
        }
    }

    void show() {
        Node *p = head_->next_;
        while (p != NULL) {
            cout << p->data_ << " ";
            p = p->next_;
        }
        cout << endl;
    }

    friend void reverseLink(Clink &link);
    friend void MergeLink(Clink &link1, Clink &link2);
    friend bool IsLinkHasCircle(Node *head, int &val);
    friend bool IsLinkHasMerge(Node *head1, Node *head2, int &val);

private:
    Node *head_;
};

void reverseLink(Clink &link) {
    Node *p = link.head_->next_;
    if (p == nullptr) {
        return;
    }
    link.head_->next_ = nullptr;
    while (p != nullptr) {
        Node *q = p->next_;

        p->next_ = link.head_->next_;
        link.head_->next_ = p;

        p = q;
    }
}

void MergeLink(Clink &link1, Clink &link2) {
    Node *p = link1.head_->next_;
    Node *q = link2.head_->next_;
    Node *last = link1.head_;
    link2.head_->next_ = nullptr;
    while (p != nullptr && q != nullptr) {
        if (p->data_ < q->data_) {
            last->next_ = p;
            p = p->next_;
            last = last->next_;
        } else {
            last->next_ = q;
            q = q->next_;
            last = last->next_;
        }
    }
    if (p != nullptr) {
        last->next_ = p;
    } else {
        last->next_ = q;
    }
}

bool IsLinkHasCircle(Node *head, int &val) {
    Node *fast = head;
    Node *slow = head;

    while (fast != nullptr && fast->next_ != nullptr) {
        slow = slow->next_;
        fast = fast->next_->next_;
        if (slow == fast) {
            fast = head;
            while (fast != slow) {
                slow = slow->next_;
                fast = fast->next_;
            }
            val = slow->data_;
            return true;
        }
    }
    return false;
}

bool IsLinkHasMerge(Node *head1, Node *head2, int &val) {
    int cnt1 = 0, cnt2 = 0; // 记录两链表的长度
    Node *p = head1->next_;
    Node *q = head2->next_;
    while (p != nullptr) {
        cnt1++;
        p = p->next_;
    }
    while (q != nullptr) {
        cnt2++;
        q = q->next_;
    }
    p = head1;
    q = head2;
    if (cnt1 > cnt2) {
        int offset = cnt1 - cnt2;
        while (offset > 0) {
            p = p->next_;
            offset--;
        }
    } else {
        int offset = cnt2 - cnt1;
        while (offset > 0) {
            q = q->next_;
            offset--;
        }
    }
    while (p != nullptr && q != nullptr) {
        if (p == q) {
            val = p->data_;
            return true;
        }
        p = p->next_;
        q = q->next_;
    }
    return false;
}

int main() {
    Clink link;
    srand(time(0));
    for (int i = 0; i < 10; i++) {
        int val = rand() % 100;
        link.InsertHead(val);
        cout << val << " ";
    }
    cout << endl;
    link.show();

    link.InsertTail(200);
    link.show();

    link.Remove(200);
    link.show();

    link.InsertHead(23);
    link.InsertHead(23);
    link.InsertHead(23);
    link.InsertTail(23);
    link.InsertTail(23);
    link.show();
    link.RemoveAll(23);
    link.show();

    // Clink link2;
    // srand(time(0));
    // for (int i = 0; i < 10; i++) {
    //     int val = rand() % 100;
    //     link2.InsertTail(val);
    // }
    // link2.show();
    // reverseLink(link);
    // link2.show();

    // int arr[] = {25, 37, 52, 78, 88, 92, 98, 108};
    // int brr[] = {13, 23, 40, 56, 62, 77, 109};
    // Clink link11;
    // Clink link22;
    // for (int v: arr) {
    //     link11.InsertTail(v);
    // }
    // for (int v: brr) {
    //     link22.InsertTail(v);
    // }
    // link11.show();
    // link22.show();

    // MergeLink(link11, link22);
    // link11.show();

    // Node head;
    // Node n1(25), n2(67), n3(32), n4(18);
    // head.next_ = &n1;
    // n1.next_ = &n2;
    // n2.next_ = &n3;
    // n3.next_ = &n4;
    // n4.next_ = &n2;
    // int val;
    // if (IsLinkHasCircle(&head, val)) {
    //     cout << "The linked list contains a cycle, and the entry node of the
    //     "
    //             "cycle is: "
    //          << val << endl;
    // }

    // Node head1;
    // Node n1(25), n2(67), n3(32), n4(18);
    // head1.next_ = &n1;
    // n1.next_ = &n2;
    // n2.next_ = &n3;
    // n3.next_ = &n4;

    // Node head2;
    // Node n5(31);
    // head2.next_ = &n5;
    // n5.next_ = &n3;

    // int val;
    // if (IsLinkHasMerge(&head1, &head2, val)) {
    //     cout << "The linked lists intersect, and the intersection node is: "
    //          << val << endl;
    // }
}
