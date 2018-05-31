#include <iostream>
#include <cassert>


template <class T, class U>
class TreapNode {
public:
    TreapNode<T, U>(const T& key, const U& priority, TreapNode<T, U>* left, TreapNode<T, U>* right)
            : left_(left), right_(right), x_(key), y_(priority) {
    }
    ~TreapNode<T, U>() {
        delete left_;
        delete right_;
    }

    TreapNode<T, U>* AddNode(TreapNode<T, U>* new_node);
    void Print() {
        if (left_)
            left_->Print();
        std::cout << x_ << "|" << y_ << "  ";
        if (right_)
            right_->Print();
    }

private:
    static void Split(TreapNode<T, U>* node, const T& key, TreapNode<T, U>*& left, TreapNode<T, U>*& right);

    T x_;
    U y_;
    TreapNode<T, U>* left_;
    TreapNode<T, U>* right_;
};

template<class T, class U>
TreapNode<T, U>* TreapNode<T, U>::AddNode(TreapNode<T, U>* new_node) {
    TreapNode<T, U>* current_node = this;
    TreapNode<T, U>* current_parent = nullptr;
    bool is_current_left = false;

    while (current_node->y_ >= new_node->y_ && current_node != nullptr) {
        if (current_node->x_ >= new_node->x_) {
            current_node = current_node->right_;
            is_current_left = false;
        } else {
            current_node = current_node->left_;
            is_current_left = true;
        }
    }
    if (current_node == nullptr) {
        current_node = new_node;
    } else {
        Split(current_node, new_node->x_, new_node->left_, new_node->right_);
        current_node = new_node;
    }
}

template<class T, class U>
void TreapNode<T, U>::Split(TreapNode<T, U>* node, const T& key, TreapNode<T, U>*& left, TreapNode<T, U>*& right) {
    if (node == nullptr) {
        left = nullptr;
        right = nullptr;
    } else if (node->x_ >= key) {
        Split(node->left_, key, left, node->left_);
        right = node;
    } else {
        Split(node->right_, key, node->right_, right);
        left = node;
    }
}

template <class T, class U>
class Treap {
public:
    Treap<T, U>() : root_(nullptr) {
    }
    ~Treap() {
        delete root_;
    }

    void Add(const T& key, const U& priority);
    void Print() {
        if (root_) {
            root_->Print();
        }
    }

private:
    TreapNode<T, U>* root_;
};

template<class T, class U>
void Treap<T, U>::Add(const T& key, const U& priority) {
    if (root_ != nullptr) {
        root_ = root_->AddNode(new TreapNode<T, U>(key, priority, nullptr, nullptr));
    } else {
        root_ = new TreapNode<T, U>(key, priority, nullptr, nullptr);
    }
}


int main() {
    Treap<int, int> treap;
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x;
        std::cin >> y;
        treap.Add(x, y);
        treap.Print();
    }

    return 0;
}