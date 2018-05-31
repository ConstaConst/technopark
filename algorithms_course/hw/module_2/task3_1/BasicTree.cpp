//
// Created by mks on 17.04.18.
//


template <class T>
class Node {
public:
    Node<T>(const T& value, Node<T>* left, Node<T>* right) : left_(left), right_(right), data_(value) {
    }
    ~Node() {
        delete left_;
        delete right_;
    }

    void AddNode(const T& value);

private:
    Node<T>* left_;
    Node<T>* right_;
    T data_;
};

template<class T>
void Node<T>::AddNode(const T& value) {
    Node<T>* current_node = this;
    while (true) {
        if (value >= current_node->data_) {
            if (current_node->right_ != nullptr) {
                current_node = current_node->right_;
            } else {
                current_node->right_ = new Node<T>(value, nullptr, nullptr);
                return;
            }
        } else {
            if (current_node->left_ != nullptr) {
                current_node = current_node->left_;
            } else {
                current_node->left_ = new Node<T>(value, nullptr, nullptr);
                return;
            }
        }
    }
}

template <class T>
class BasicTree {
public:
    BasicTree<T>() : root_(nullptr) {
    }
    ~BasicTree<T>() {
        delete root_;
    }

    void Add(const T& value);

private:
    Node<T>* root_;
};

template<class T>
void BasicTree<T>::Add(const T& value) {
    if (root_ != nullptr) {
        root_->AddNode(value);
    } else {
        root_ = new Node<T>(value, nullptr, nullptr);
    }
}
