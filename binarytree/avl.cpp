#include <iostream>
using namespace std;

template <typename T>
class AVLTree {
public:
    AVLTree() : root_(nullptr) {}

    void preOrder() {
        preOrder(root_);
        cout << endl;
    }

    void inOrder() {
        inOrder(root_);
        cout << endl;
    }

    void insert(const T &val) {
        root_ = insert(root_, val);
    }

    void remove(const T &val) {
        root_ = remove(root_, val);
    }

private:
    struct Node {
        Node(T data = T())
            : data_(data),
              left_(nullptr),
              right_(nullptr),
              height_(1) {}

        T data_;
        Node *left_;
        Node *right_;
        int height_;
    };

    Node *root_;

    int getHeight(Node *node) {
        return node == nullptr ? 0 : node->height_;
    }

    Node *rightRotate(Node *node) {
        Node *child = node->left_;
        node->left_ = child->right_;
        child->right_ = node;
        node->height_ =
            max(getHeight(node->left_), getHeight(node->right_)) + 1;
        child->height_ =
            max(getHeight(child->left_), getHeight(child->right_)) + 1;
        return child;
    }

    Node *leftRotate(Node *node) {
        Node *child = node->right_;
        node->right_ = child->left_;
        child->left_ = node;

        node->height_ =
            max(getHeight(node->left_), getHeight(node->right_)) + 1;
        child->height_ =
            max(getHeight(child->left_), getHeight(child->right_)) + 1;
        return child;
    }

    Node *leftrightRotate(Node *node) {
        node->left_ = leftRotate(node->left_);
        return rightRotate(node);
    }

    Node *rightleftRotate(Node *node) {
        node->right_ = rightRotate(node->right_);
        return leftRotate(node);
    }

    Node *insert(Node *node, const T &val) {
        if (node == nullptr) {
            return new Node(val);
        }

        if (node->data_ > val) {
            node->left_ = insert(node->left_, val);
            if (getHeight(node->left_) - getHeight(node->right_) > 1) {
                if (getHeight(node->left_->left_) >=
                    getHeight(node->left_->right_)) {
                    node = rightRotate(node);
                } else {
                    node = leftrightRotate(node);
                }
            }
        } else if (node->data_ < val) {
            node->right_ = insert(node->right_, val);
            if (getHeight(node->right_) - getHeight(node->left_) > 1) {
                if (getHeight(node->right_->right_) >=
                    getHeight(node->right_->left_)) {
                    node = leftRotate(node);
                } else {
                    node = rightleftRotate(node);
                }
            }
        } else {
            ;
        }
        node->height_ =
            max(getHeight(node->left_), getHeight(node->right_)) + 1;
        return node;
    }

    Node *remove(Node *node, const T &val) {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->data_ > val) {
            node->left_ = remove(node->left_, val);
            if (getHeight(node->right_) - getHeight(node->left_) > 1) {
                if (getHeight(node->right_->right_) >=
                    getHeight(node->right_->left_)) {
                    node = leftRotate(node);
                } else {
                    node = rightleftRotate(node);
                }
            }
        } else if (node->data_ < val) {
            node->right_ = remove(node->right_, val);
            if (getHeight(node->left_) - getHeight(node->right_) > 1) {
                if (getHeight(node->left_->left_) >=
                    getHeight(node->left_->right_)) {
                    node = rightRotate(node);
                } else {
                    node = leftrightRotate(node);
                }
            }
        } else {
            if (node->left_ != nullptr && node->right_ != nullptr) {
                if (getHeight(node->left_) >= getHeight(node->right_)) {
                    Node *pre = node->left_;
                    while (pre->right_ != nullptr) {
                        pre = pre->right_;
                    }
                    node->data_ = pre->data_;
                    node->left_ = remove(node->left_, pre->data_);
                } else {
                    node->right_ = remove(node->right_, val);
                    Node *post = node->right_;
                    while (post->left_ != nullptr) {
                        post = post->left_;
                    }
                    node->data_ = post->data_;
                    node->right_ = remove(node->right_, post->data_);
                }
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
        }
        node->height_ = max(getHeight(node->left_), getHeight(node->right_));
        return node;
    }

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
};

int main() {
    AVLTree<int> avl;
    for (int i = 1; i <= 10; i++) {
        avl.insert(i);
    }
    avl.preOrder();
    avl.inOrder();

    avl.remove(9);
    avl.remove(10);
    avl.preOrder();
    avl.inOrder();
    return 0;
}
