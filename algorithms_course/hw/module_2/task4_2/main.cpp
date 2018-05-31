/* 4_2. Порядковые статистики. Дано число N и N строк. Каждая строка содержит команду добавления
или удаления натуральных чисел, а также запрос на получение k-ой порядковой статистики. Команда добавления
числа A задается положительным числом A, команда удаления числа A задается отрицательным числом “-A”.
Запрос на получение k-ой порядковой статистики задается числом k. Требуемая скорость выполнения запроса - O(log n).

    in: 5           out:
        40 0             40
        10 1             40
        4 1              10
        -10 0            4
        50 2             50
 */

#include <iostream>
#include <cassert>


template <class T>
class AVLTree {
public:
    AVLTree() : root_(nullptr) {}
    ~AVLTree() { delete root_; }

    void add(const T& value);
    void remove(const T& value);
    T& searchKStatistics(size_t k) const;

private:
    struct Node {
        explicit Node(T data) : data_(data), height_(1), subtreeElementsCount_(1), left_(nullptr), right_(nullptr) {}
        ~Node() {
            delete left_;
            delete right_;
        }

        static Node* addNode(Node* root, const T& value);
        static Node* removeNode(Node* node, const T& value);
        static T& searchKStatistics(Node* node, size_t k);

        static size_t subtreeElemCount(const Node* node) {
            return node != nullptr ? node->subtreeElementsCount_ : 0;
        }
        static unsigned char height(const Node* node) {
            return static_cast<unsigned char>(node != nullptr ? node->height_ : 0);
        }
        static char balanceFactor(const Node* node) {
            assert(node != nullptr);

            return height(node->left_) - height(node->right_);
        }

        static void fixHeight(Node* node) {
            if (node == nullptr) {
                return;
            }
            unsigned char hL = height(node->left_);
            unsigned char hR = height(node->right_);
            node->height_ = static_cast<unsigned char>((hL < hR ? hR : hL) + 1);
        }
        static void fixSubtreeElemsCount(Node* node) {
            if (node == nullptr) {
                return;
            }
            node->subtreeElementsCount_ = 1;
            if (node->left_ != nullptr) {
                node->subtreeElementsCount_ += node->left_->subtreeElementsCount_;
            }
            if (node->right_ != nullptr) {
                node->subtreeElementsCount_ += node->right_->subtreeElementsCount_;
            }
        }
        static Node* rotateLeft(Node* p);
        static Node* rotateRight(Node* p);
        static Node* balance(Node* node);
        static Node* removeMin(Node* node, T& changeData);

        T data_;
        unsigned char height_;
        size_t subtreeElementsCount_;

        Node* left_;
        Node* right_;
    };

    Node* root_;
};

template<class T>
typename AVLTree<T>::Node* AVLTree<T>::Node::addNode(AVLTree::Node* root, const T& value) {
    if (root == nullptr) {
        return new Node(value);
    }
    if (value < root->data_) {
        root->left_ = addNode(root->left_, value);
    } else {
        root->right_ = addNode(root->right_, value);
    }
    fixSubtreeElemsCount(root);
    return balance(root);
}

template<class T>
typename AVLTree<T>::Node* AVLTree<T>::Node::removeNode(AVLTree::Node* node, const T& value) {
    if (node == nullptr) {
        return nullptr;
    }
    if (value == node->data_) {
        if (node->right_ == nullptr) {
            Node* left = node->left_;
            node->left_ = nullptr;
            delete node;
            return left;
        }
        if (node->left_ == nullptr) {
            Node* right = node->right_;
            node->right_ = nullptr;
            delete node;
            return right;
        }
        //Удаление узла с 2мя потомками: заменяем поле данных на поле минимального узла справа, удаляем правый узел и
        //при возвращении востанавливаем баланс.
        node->right_ = removeMin(node->right_, node->data_);

    } else if (value < node->data_) {
        node->left_ = removeNode(node->left_, value);
    } else {
        node->right_ = removeNode(node->right_, value);
    }

    return balance(node);
}

template<class T>
typename AVLTree<T>::Node* AVLTree<T>::Node::rotateLeft(AVLTree::Node* p) {
    assert(p != nullptr);

    Node* q = p->right_;
    p->right_ = q->left_;
    q->left_ = p;
    fixHeight(p);
    fixHeight(q);
    fixSubtreeElemsCount(p);
    fixSubtreeElemsCount(q);

    return q;
}

template<class T>
typename AVLTree<T>::Node* AVLTree<T>::Node::rotateRight(AVLTree::Node* p) {
    assert(p != nullptr);

    Node* q = p->left_;
    p->left_ = q->right_;
    q->right_ = p;
    fixHeight(p);
    fixHeight(q);
    fixSubtreeElemsCount(p);
    fixSubtreeElemsCount(q);

    return q;
}

template<class T>
typename AVLTree<T>::Node* AVLTree<T>::Node::balance(AVLTree::Node* node) {
    switch (balanceFactor(node)) {
        case 2:
            if (balanceFactor(node->left_) < 0) {
                node->left_ = rotateLeft(node->left_);
            }
            return rotateRight(node);
        case -2:
            if (balanceFactor(node->right_) > 0) {
                node->right_ = rotateRight(node->right_);
            }
            return rotateLeft(node);
        default:
            fixHeight(node);
            fixSubtreeElemsCount(node);
            return node;
    }
}

template<class T>
T& AVLTree<T>::Node::searchKStatistics(AVLTree::Node* node, size_t k) {
    if (subtreeElemCount(node->left_) == k) {
        return node->data_;
    }
    if (k < subtreeElemCount(node->left_)) {
        return searchKStatistics(node->left_, k);
    } else {
        return searchKStatistics(node->right_, k - subtreeElemCount(node->left_) - 1);
    }
}

template<class T>
typename AVLTree<T>::Node* AVLTree<T>::Node::removeMin(AVLTree::Node* node, T& changeData) {
    assert(node != nullptr);

    if (node->left_ != nullptr) {
        node->left_ = removeMin(node->left_, changeData);
    } else {
        changeData = node->data_;
        Node* right = node->right_;
        node->right_ = nullptr;
        delete node;
        return right;
    }

    return balance(node);
}


template<class T>
void AVLTree<T>::add(const T& value) {
    root_ = Node::addNode(root_, value);
}

template<class T>
void AVLTree<T>::remove(const T &value) {
    root_ = Node::removeNode(root_, value);
}

template<class T>
T& AVLTree<T>::searchKStatistics(size_t k) const {
    assert(k < root_->subtreeElementsCount_);

    return Node::searchKStatistics(root_, k);
}

int main() {
    AVLTree<int> avlTree;
    int n = 0;
    std::cin >> n;

    for(int i = 0; i < n; i++) {
        int value = 0;
        size_t k = 0;
        std::cin >> value >> k;
        if (value > 0) {
            avlTree.add(value);
        } else {
            avlTree.remove(-value);
        }
        std::cout << avlTree.searchKStatistics(k) << "\n";
    }
    return 0;
}