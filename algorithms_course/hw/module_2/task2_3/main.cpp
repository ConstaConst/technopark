/* 2_3. Выведите элементы в порядке post-order (снизу вверх).
Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Рекурсия запрещена.
        in: 3       out:
            2 1 3       1 3 2

            3
            1 2 3       3 2 1

            3
            3 1 2       2 1 3
*/

#include <iostream>
#include <cassert>
#include <stack>
#include <queue>


template <class T>
class BasicTree {
public:
    BasicTree<T>() : root_(nullptr) {
    }
    ~BasicTree<T>();

    void Add(const T& value);
    void PostOrderPrint() const;

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
    if (root_ != nullptr) {
        std::queue<Node *> recursion;
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
}

template<class T>
void BasicTree<T>::Add(const T& value) {
    if (root_ != nullptr) {
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
    } else {
        root_ = new Node(value, nullptr, nullptr);
    }
}

template<class T>
void BasicTree<T>::PostOrderPrint() const {
    if (root_ != nullptr) {
        // Замена рекурсии на стек. Second параметр в pair нужен для отслеживания направления движения: 0 - идем влево,
        // 1 - вправо, 2 - посетили все поддеревья - можно обрабатывать данные.
        std::stack<std::pair<Node*, char>> recursion;
        recursion.push(std::make_pair(root_, 0));

        while(!recursion.empty()) {
            std::pair<Node*, char> current_node = recursion.top();

            switch (current_node.second) {
                case 0:
                    ++recursion.top().second;
                    if (current_node.first->left_ != nullptr) {
                        recursion.push(std::make_pair(current_node.first->left_, 0));
                    }
                    break;
                case 1:
                    ++recursion.top().second;
                    if (current_node.first->right_ != nullptr) {
                        recursion.push(std::make_pair(current_node.first->right_, 0));
                    }
                    break;
                case 2:
                    std::cout << current_node.first->data_ << std::endl;
                    recursion.pop();
                    break;
            }
        }
    }
}



int main() {
    BasicTree<int> tree;
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int elem;
        std::cin >> elem;
        tree.Add(elem);
    }

    tree.PostOrderPrint();

    return 0;
}