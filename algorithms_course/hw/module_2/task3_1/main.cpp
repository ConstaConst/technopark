/* 3_1. Вычислить разницу глубин наивного дерева поиска и декартового дерева. Разница может быть отрицательна.

Задача 3. Декартово дерево:
Дано число N < 106 и последовательность пар целых чисел из [-231..231] длиной N.
Построить декартово дерево из N узлов, характеризующихся парами чисел {Xi, Yi}.
Каждая пара чисел {Xi, Yi} определяет ключ Xi и приоритет Yi в декартовом дереве.
Добавление узла в декартово дерево выполняйте второй версией алгоритма, рассказанного на лекции:
При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим приоритетом. Затем разбейте найденное поддерево по ключу x так, чтобы в первом поддереве все ключи меньше x, а во втором больше или равны x. Получившиеся два дерева сделайте дочерними для нового узла (x, y). Новый узел вставьте на место узла P.

Построить также наивное дерево поиска по ключам Xi методом из задачи 2.

        in: 10          out: 2
            5 11
            18 8
            25 7
            50 12
            30 30
            15 15
            20 10
            22 5
            40 20
            45 9
 */



#include <iostream>
#include <cassert>
#include <queue>


template <class T>
class BasicTree {
public:
    BasicTree<T>() : root_(nullptr) {
    }
    ~BasicTree<T>();

    void Add(const T& value);
    int Height() const;

private:
    struct Node {
        Node(const T& value, Node* left, Node* right) : left_(left), right_(right), data_(value) {
        }

        T data_;
        Node* left_;
        Node* right_;
    };

    Node* root_;
};

template<class T>
BasicTree<T>::~BasicTree<T>() {
    if (root_ == nullptr) {
        return;
    }
    std::queue<Node*> recursion;
    recursion.push(root_);

    while (!recursion.empty()) {
        Node* node = recursion.front();
        recursion.pop();

        if (node->left_ != nullptr) {
            recursion.push(node->left_);
        }
        if (node->right_ != nullptr) {
            recursion.push(node->right_);
        }

        delete node;
    }

}

template<class T>
void BasicTree<T>::Add(const T& value) {
    if (root_ == nullptr) {
        root_ = new Node(value, nullptr, nullptr);
        return;
    }
    Node* current_node = root_;
    // Поиск места для вставки. Большие и равные узлу значения уходят в правое поддерево.
    while (true) {
        if (value >= current_node->data_) {
            if (current_node->right_ != nullptr) {
                current_node = current_node->right_;
            } else {
                current_node->right_ = new Node(value, nullptr, nullptr);
                return;
            }
        } else {
            if (current_node->left_ != nullptr) {
                current_node = current_node->left_;
            } else {
                current_node->left_ = new Node(value, nullptr, nullptr);
                return;
            }
        }
    }
}

template<class T>
int BasicTree<T>::Height() const {
    if (root_ == nullptr) {
        return 0;
    }
    std::queue<Node*> recursion;
    recursion.push(root_);
    int height = 1;

    while (!recursion.empty()) {

        size_t node_count = recursion.size();
        for (size_t i = 0; i < node_count; ++i) {
            Node* node = recursion.front();
            recursion.pop();
            if (node->left_ != nullptr) {
                recursion.push(node->left_);
            }
            if (node->right_ != nullptr) {
                recursion.push(node->right_);
            }
        }
        ++height;
    }
    //- 1, тк последний слой состоит из nullptr.
    return height - 1;
}


template <class T, class U>
class Treap {
private:
    struct Node;
public:
    Treap() : root_(nullptr) {
    }
    ~Treap() {
        delete root_;
    }

    void Add(const T& key, const T& priority);
    int Height() const;

private:
    struct Node {
        Node(const T& key, const U& priority) : x_(key), y_(priority), left_(nullptr), right_(nullptr) {
        }
        ~Node() {
            delete left_;
            delete right_;
        }

        int Height() const;

        T x_;
        U y_;
        Node* left_;
        Node* right_;
    };

    void Split(Node* node, const T& key, Node*& left, Node*& right);

    Node* root_;
};

template<class T, class U>
int Treap<T, U>::Node::Height() const {
    if (this == nullptr)
        return 0;
    int left_h = left_->Height();
    int right_h = right_->Height();
    return (left_h > right_h) ? left_h + 1 : right_h + 1;
}


template<class T, class U>
void Treap<T, U>::Split(Treap::Node* node, const T& key, Treap::Node*& left, Treap::Node*& right) {
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

template<class T, class U>
void Treap<T, U>::Add(const T& key, const T& priority) {
    Node* new_node = new Node(key, priority);

    if (root_ == nullptr) {
        root_ = new_node;
        return;
    }

    Node* current_node = root_;
    Node* current_parent = nullptr;
    bool is_current_left = false;

    while (current_node != nullptr && current_node->y_ >= new_node->y_) {
        current_parent = current_node;
        if (current_node->x_ < new_node->x_) {
            current_node = current_node->right_;
            is_current_left = false;
        } else {
            current_node = current_node->left_;
            is_current_left = true;
        }
    }

    Split(current_node, new_node->x_, new_node->left_, new_node->right_);
    if (current_parent != nullptr) {
        if (is_current_left) {
            current_parent->left_ = new_node;
        } else {
            current_parent->right_ = new_node;
        }
    } else {
        root_ = new_node;
    }

}

template<class T, class U>
int Treap<T, U>::Height() const {
    return root_ != nullptr ? root_->Height() : 0;
}


int main() {
    Treap<int, int> treap;
    BasicTree<int> tree;
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x;
        std::cin >> y;
        treap.Add(x, y);
        tree.Add(x);
    }

    std::cout << tree.Height() - treap.Height();

    return 0;
}