#include <cmath>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

template <typename T, typename Compare = less<T>>
class BSTree {
    friend void test01();
    friend void test03();

public:
    BSTree() : root_(nullptr) {}

    ~BSTree() {
        if (root_ != nullptr) {
            queue<Node *> q;
            q.push(root_);
            while (!q.empty()) {
                Node *front = q.front();
                q.pop();
                if (front->left_ != nullptr) {
                    q.push(front->left_);
                }
                if (front->right_ != nullptr) {
                    q.push(front->right_);
                }
                delete front;
            }
        }
    }

public:
    void n_insert(const T &val) {
        if (root_ == nullptr) {
            root_ = new Node(val);
            return;
        }
        Node *parent = nullptr;
        Node *cur = root_;
        while (cur != nullptr) {
            if (val == cur->data_) {
                return;
            } else if (Compare()(val, cur->data_)) {
                parent = cur;
                cur = cur->left_;
            } else {
                parent = cur;
                cur = cur->right_;
            }
        }
        if (Compare()(val, parent->data_)) {
            parent->left_ = new Node(val);
        } else if (!Compare()(val, parent->data_)) {
            parent->right_ = new Node(val);
        }
    }

    void insert(const T &val) {
        root_ = insert(root_, val);
    }

    void n_remove(const T &val) {
        if (root_ == nullptr) {
            return;
        }
        Node *parent = nullptr;
        Node *cur = root_;
        while (cur != nullptr) {
            if (val == cur->data_) {
                break;
            } else if (Compare()(val, cur->data_)) {
                parent = cur;
                cur = cur->left_;
            } else {
                parent = cur;
                cur = cur->right_;
            }
        }
        if (cur == nullptr) {
            cout << "Node to be deleted not found" << endl;
            return;
        }
        if (cur->left_ != nullptr && cur->right_ != nullptr) {
            parent = cur;
            Node *pre = cur->left_;
            while (pre->right_ != nullptr) {
                parent = pre;
                pre = pre->right_;
            }
            cur->data_ = pre->data_;
            cur = pre;
        }

        Node *child = cur->left_;
        if (child == nullptr) {
            child = cur->right_;
        }
        if (parent == nullptr) {
            root_ = child;
        }
        if (parent->left_ == cur) {
            parent->left_ = child;
        } else {
            parent->right_ = child;
        }
        delete cur;
    }

    void remove(const T &val) {
        root_ = remove(root_, val);
    }

    bool n_query(const T &val) {
        Node *cur = root_;
        while (cur != nullptr) {
            if (cur->data_ == val) {
                return true;
            } else if (Compare()(val, cur->data_)) {
                cur = cur->left_;
            } else {
                cur = cur->right_;
            }
        }
        return false;
    }

    bool query(const T &val) {
        return query(root_, val) != nullptr;
    }

    void preOrder() {
        cout << "[Recursive] Pre-order Traversal: ";
        preOrder(root_);
        cout << endl;
    }

    void n_preOrder() {
        cout << "[Non-Recursive] Pre-order Traversal: ";
        if (root_ == nullptr) {
            return;
        }
        stack<Node *> s;
        s.push(root_);
        while (!s.empty()) {
            Node *top = s.top();
            s.pop();
            cout << top->data_ << " ";
            if (top->right_ != nullptr) {
                s.push(top->right_);
            }
            if (top->left_ != nullptr) {
                s.push(top->left_);
            }
        }
        cout << endl;
    }

    void inOrder() {
        cout << "[Recursive] In-order Traversal: ";
        inOrder(root_);
        cout << endl;
    }

    void n_inOrder() {
        cout << "[Non-Recursive] In-order Traversal: ";
        if (root_ == nullptr) {
            return;
        }
        stack<Node *> s;
        Node *cur = root_;
        while (cur != nullptr) {
            s.push(cur);
            cur = cur->left_;
        }
        while (!s.empty()) {
            Node *top = s.top();
            s.pop();
            cout << top->data_ << " ";
            cur = top->right_;
            while (cur != nullptr) {
                s.push(cur);
                cur = cur->left_;
            }
        }
        cout << endl;
    }

    void postOrder() {
        cout << "[Recursive] Post-order Traversal: ";
        postOrder(root_);
        cout << endl;
    }

    void n_postOrder() {
        cout << "[Non-Recursive] Post-order Traversal: ";
        if (root_ == nullptr) {
            return;
        }
        stack<Node *> s1;
        stack<Node *> s2;
        s1.push(root_);
        while (!s1.empty()) {
            Node *top = s1.top();
            s1.pop();
            s2.push(top);
            if (top->left_ != nullptr) {
                s1.push(top->left_);
            }
            if (top->right_ != nullptr) {
                s1.push(top->right_);
            }
        }
        while (!s2.empty()) {
            cout << s2.top()->data_ << " ";
            s2.pop();
        }
        cout << endl;
    }

    int high() {
        return high(root_);
    }

    int number() {
        return number(root_);
    }

    void levelOrder() {
        cout << "[Recursive] Level-order Traversal: ";
        int h = high();
        for (int i = 0; i < h; ++i) {
            levelOrder(root_, i);
        }
        cout << endl;
    }

    void n_levelOrder() {
        cout << "[Non-Recursive] Level-order Traversal: ";
        if (root_ == nullptr) {
            return;
        }
        queue<Node *> que;
        que.push(root_);
        while (!que.empty()) {
            Node *front = que.front();
            que.pop();

            cout << front->data_ << " ";
            if (front->left_ != nullptr) {
                que.push(front->left_);
            }
            if (front->right_ != nullptr) {
                que.push(front->right_);
            }
        }
        cout << endl;
    }

    void SearchVal_Interval(vector<T> &vec, int begin, int end) {
        SearchVal_Interval(root_, vec, begin, end);
    }

    bool isBST() {
        Node *pre = nullptr;
        return isBST(root_, pre);
    }

    bool isChildTree(BSTree<T, Compare> &child) {
        if (child.root_ == nullptr) {
            return true;
        }
        Node *cur = root_;
        while (cur != nullptr) {
            if (cur->data_ == child.root_->data_) {
                break;
            } else if (cur->data_ < child.root_->data_) {
                cur = cur->right_;
            } else {
                cur = cur->left_;
            }
        }
        if (cur == nullptr) {
            return false;
        }
        return isChildTree(cur, child.root_);
    }

    int getLCA(int val1, int val2) {
        Node *node = getLCA(root_, val1, val2);
        if (node == nullptr) {
            throw "no LCA";
        } else {
            return node->data_;
        }
    }

    void mirrorInvert() {
        mirrorInvert(root_);
    }

    bool mirrorSymmetric() {
        if (root_ == nullptr) {
            return true;
        }
        return mirrorSymmetric(root_->left_, root_->right_);
    }

    void rebuild(int pre[], int i, int j, int in[], int m, int n) {
        root_ = _rebuild(pre, i, j, in, m, n);
    }

    bool isBalance() {
        return isBalance02(root_) == -1 ? false : true;
    }

    int getKthFromEnd(int k) {
        int count = 1;
        Node *node = getKthFromEnd(root_, k, count);
        if (node == nullptr) {
            throw "no!";
        } else {
            return node->data_;
        }
    }

private:
    struct Node {
        Node(T data = T()) : data_(data), left_(nullptr), right_(nullptr) {}

        T data_;
        Node *left_;
        Node *right_;
    };

    Node *root_;

    void preOrder(Node *node) {
        if (node != nullptr) {
            cout << node->data_ << " ";
            preOrder(node->left_);
            preOrder(node->right_);
        }
    }

    void inOrder(Node *node) {
        if (node != nullptr) {
            inOrder(node->left_);
            cout << node->data_ << " ";
            inOrder(node->right_);
        }
    }

    void postOrder(Node *node) {
        if (node != nullptr) {
            postOrder(node->left_);
            postOrder(node->right_);
            cout << node->data_ << " ";
        }
    }

    int high(Node *node) {
        if (node == nullptr) {
            return 0;
        }
        int left = high(node->left_);
        int right = high(node->right_);
        return left > right ? left + 1 : right + 1;
    }

    int number(Node *node) {
        if (node == nullptr) {
            return 0;
        }
        int leftNumber = number(node->left_);
        int rightNumber = number(node->right_);
        return leftNumber + rightNumber + 1;
    }

    void levelOrder(Node *node, int h) {
        if (node == nullptr) {
            return;
        }
        if (h == 0) {
            cout << node->data_ << " ";
        }
        levelOrder(node->left_, h - 1);
        levelOrder(node->right_, h - 1);
    }

    Node *insert(Node *node, const T &val) {
        if (node == nullptr) {
            return new Node(val);
        }
        if (node->data_ == val) {
            return node;
        } else if (Compare()(node->data_, val)) {
            node->right_ = insert(node->right_, val);
            return node;
        } else {
            node->left_ = insert(node->left_, val);
            return node;
        }
    }

    Node *remove(Node *node, const T &val) {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->data_ == val) {
            if (node->left_ != nullptr && node->right_ != nullptr) {
                Node *pre = node->left_;
                while (pre->right_ != nullptr) {
                    pre = pre->right_;
                }
                node->data_ = pre->data_;
                node->left_ = remove(node->left_, pre->data_);
            } else {
                if (node->left_ != nullptr) {
                    Node *left = node->left_;
                    delete node;
                    return left;
                } else if (node->right_ != nullptr) {
                    Node *right = node->right_;
                    delete node;
                    return right;
                } else {
                    return nullptr;
                }
            }
        } else if (Compare()(val, node->data_)) {
            node->left_ = remove(node->left_, val);
            return node;
        } else {
            node->right_ = remove(node->right_, val);
            return node;
        }
    }

    Node *query(Node *node, const T &val) {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->data_ == val) {
            return node;
        } else if (Compare()(val, node->data_)) {
            return query(node->left_, val);
        } else {
            return query(node->right_, val);
        }
    }

    void SearchVal_Interval(Node *node, vector<T> &vec, int begin, int end) {
        if (node == nullptr) {
            return;
        }
        if (node->data_ > begin) {
            SearchVal_Interval(node->left_, vec, begin, end);
        }

        if (node->data_ >= begin && node->data_ <= end) {
            vec.push_back(node->data_);
        }

        if (node->data_ < end) {
            SearchVal_Interval(node->right_, vec, begin, end);
        }
    }

    bool isBST(Node *node, Node *&pre) {
        if (node == nullptr) {
            return true;
        }
        if (!isBST(node->left_, pre)) {
            return false;
        }
        if (pre != nullptr) {
            if (Compare()(node->data_, pre->data_)) {
                return false;
            }
        }
        pre = node;
        return isBST(node->right_, pre);
    }

    bool isChildTree(Node *father, Node *child) {
        if (father == nullptr && child == nullptr) {
            return true;
        }
        if (father == nullptr) {
            return false;
        }
        if (child == nullptr) {
            return true;
        }
        if (father->data_ != child->data_) {
            return false;
        }
        return isChildTree(father->left_, child->left_) &&
               isChildTree(father->right_, child->right_);
    }

    Node *getLCA(Node *node, int val1, int val2) {
        if (node == nullptr) {
            return nullptr;
        }
        if (Compare()(node->data_, val1) && Compare()(node->data_, val2)) {
            return getLCA(node->right_, val1, val2);
        } else if (Compare()(val1, node->data_) &&
                   Compare()(val2, node->data_)) {
            return getLCA(node->left_, val1, val2);
        } else {
            return node;
        }
    }

    void mirrorInvert(Node *node) {
        if (node == nullptr) {
            return;
        }
        Node *temp;
        temp = node->left_;
        node->left_ = node->right_;
        node->right_ = temp;
        mirrorInvert(node->left_);
        mirrorInvert(node->right_);
    }

    bool mirrorSymmetric(Node *l, Node *r) {
        if (l == nullptr && r == nullptr) {
            return true;
        }
        if (l == nullptr || r == nullptr) {
            return false;
        }
        if (l->data_ != r->data_) {
            return false;
        }
        bool L = mirrorSymmetric(l->left_, r->right_);
        bool R = mirrorSymmetric(l->right_, r->left_);
        return L && R;
    }

    Node *_rebuild(int pre[], int i, int j, int in[], int m, int n) {
        if (i > j || m > n) {
            return nullptr;
        }
        Node *node = new Node(pre[i]);
        for (int k = m; k <= n; k++) {
            if (in[k] == pre[i]) {
                node->left_ = _rebuild(pre, i + 1, i + (k - m), in, m, k - 1);
                node->right_ = _rebuild(pre, i + (k - m) + 1, j, in, k + 1, n);
                return node;
            }
        }
        return node;
    }

    bool isBalance01(Node *node) {
        if (node == nullptr) {
            return true;
        }
        if (!isBalance(node->left_)) {
            return false;
        }
        if (!isBalance(node->right_)) {
            return false;
        }
        int left = high(node->left_);
        int right = high(node->right_);
        return abs(left - right) <= 1;
    }

    int isBalance02(Node *node) {
        if (node == nullptr) {
            return 0;
        }
        int L = isBalance02(node->left_);
        if (L == -1) {
            return -1;
        }
        int R = isBalance02(node->right_);
        if (R == -1) {
            return -1;
        }
        return abs(L - R) > 1 ? -1 : max(L, R) + 1;
    }

    Node *getKthFromEnd(Node *node, int k, int &count) {
        if (node == nullptr) {
            return nullptr;
        }
        Node *L = getKthFromEnd(node->right_, k, count);
        if (L != nullptr) {
            return L;
        }

        if (count == k) {
            return node;
        }
        count++;

        Node *R = getKthFromEnd(node->left_, k, count);
        if (R != nullptr) {
            return R;
        }
        return nullptr;
    }
};

void test01() {
    int arr[] = {58, 24, 67, 0, 34, 62, 69, 5, 41, 64, 78};
    BSTree<int> bst;
    for (int v: arr) {
        bst.insert(v);
    }

    using Node = BSTree<int>::Node;
    BSTree<int> child;
    child.root_ = new Node(67);
    Node *node1 = new Node(62);
    Node *node2 = new Node(69);
    child.root_->left_ = node1;
    child.root_->right_ = node2;
    cout << boolalpha << bst.isChildTree(child) << endl;

    Node *node3 = new Node(60);
    node1->left_ = node3;
    cout << boolalpha << bst.isChildTree(child) << endl;
}

void test02() {
    int arr[] = {58, 24, 67, 0, 34, 62, 69, 5, 41, 64, 78};
    BSTree<int> bst;
    for (int v: arr) {
        bst.insert(v);
    }
    cout << bst.getLCA(5, 41) << endl;
    cout << bst.getLCA(64, 41) << endl;
}

void test03() {
    using Node = BSTree<int>::Node;
    BSTree<int> bst;
    bst.root_ = new Node(40);
    Node *node1 = new Node(20);
    Node *node2 = new Node(20);
    Node *node3 = new Node(10);
    Node *node4 = new Node(15);
    Node *node5 = new Node(15);
    Node *node6 = new Node(10);

    bst.root_->left_ = node1;
    bst.root_->right_ = node2;
    node1->left_ = node3;
    node1->right_ = node4;
    node2->left_ = node5;
    node2->right_ = node6;
    cout << boolalpha << bst.mirrorSymmetric() << endl;

    Node *node7 = new Node(88);
    node6->left_ = node7;
    cout << boolalpha << bst.mirrorSymmetric() << endl;
}

void test04() {
    BSTree<int> bst;
    int pre[] = {58, 24, 0, 5, 34, 41, 67, 62, 64, 69, 78};
    int in[] = {0, 5, 24, 34, 41, 58, 62, 64, 67, 69, 78};
    bst.rebuild(pre, 0, 10, in, 0, 10);
    bst.preOrder();
    bst.inOrder();
}

int main() {
    int arr[] = {58, 24, 67, 0, 34, 62, 69, 5, 41, 64, 78};
    BSTree<int> bst;
    for (int v: arr) {
        bst.insert(v);
    }
    bst.preOrder();
    bst.n_preOrder();
    bst.inOrder();
    bst.n_inOrder();
    bst.postOrder();
    bst.n_postOrder();
    bst.levelOrder();
    bst.n_levelOrder();
    cout << bst.high() << endl;
    cout << bst.number() << endl;

    cout << boolalpha << bst.query(12) << endl;
    bst.n_insert(12);
    cout << boolalpha << bst.query(12) << endl;

    vector<int> vec;
    bst.SearchVal_Interval(vec, 10, 60);
    for (int v: vec) {
        cout << v << " ";
    }
    cout << endl;

    cout << "Subtree Test: " << endl;
    test01();

    cout << "LCA Test: " << endl;
    test02();

    cout << "Mirror Inversion: " << endl;
    bst.inOrder();
    bst.mirrorInvert();
    bst.inOrder();

    cout << "Mirror Symmetry Test: " << endl;
    test03();

    cout << "Rebuild BST from Pre-order and In-order: " << endl;
    test04();

    cout << "Balance Tree Test: " << endl;
    int A[] = {58, 24, 67, 0, 34, 62, 69, 5, 41, 64, 78};
    BSTree<int> b;
    for (int v: A) {
        b.insert(v);
    }
    cout << boolalpha << b.isBalance() << endl;
    b.insert(12);
    cout << boolalpha << b.isBalance() << endl;

    cout << "Get Kth Node from End in In-order Traversal: " << endl;
    b.inOrder();
    cout << b.getKthFromEnd(4) << endl;

    return 0;
}
