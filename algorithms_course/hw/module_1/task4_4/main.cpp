/*
4_4. Скользящий максимум.
Решение всех задач данного раздела предполагает использование кучи, реализованной в виде класса.
Дан массив натуральных чисел A[0..n), n не превосходит 10^8. Так же задан размер некоторого окна (последовательно расположенных элементов массива) в этом массиве k, k<=n.
Требуется для каждого положения окна (от 0 и до n-k) вывести значение максимума в окне.
Скорость работы O(n log n), память O(n).
Формат входных данных. Вначале вводится n - количество элементов массива. Затем вводится n строк со значением каждого элемента. Затем вводится k  - размер окна.
Формат выходных данных. Разделенные пробелом значения максимумов для каждого положения окна.
in: 9                   out: 8 8 8 10 10 10
    0 7 3 8 4 5 10 4 6
    4
 */

#include <iostream>
#include <cstring>
#include <cassert>


//Шаблон класса Динамический массив, для динамического буфера
template <class T>
class DynamicArray {
public:
    DynamicArray(): buffer(nullptr), capacity(0), elemNumber(0) {}
    DynamicArray(const DynamicArray<T>& other) {
        elemNumber = other.elemNumber;
        capacity = other.capacity;
        buffer = new T[elemNumber];
        std::memcpy(buffer, other.buffer, sizeof(T) * elemNumber);
    }
    ~DynamicArray() { delete[] buffer; }

    DynamicArray<T>& operator=(const DynamicArray<T>& other) {
        if (this == &other)
            return *this;

        elemNumber = other.elemNumber;
        capacity = other.capacity;
        delete[] buffer;
        buffer = new T[elemNumber];
        std::memcpy(buffer, other.buffer, sizeof(T) * elemNumber);

        return *this;
    }
    void pushBack(const T& value) {
        if (elemNumber == capacity) {
            grow();
        }
        buffer[elemNumber++] = value;
    }
    T& popBack() {
        assert(!isEmpty());
        return buffer[--elemNumber];
    }
    bool isEmpty() const {
        return elemNumber == 0;
    }
    size_t size() const {
        return elemNumber;
    }
    T& operator[] (const int index) {
        return buffer[index];
    }
    const T& operator[] (const int index) const {
        return buffer[index];
    }

private:
    T* buffer;
    size_t capacity;
    size_t elemNumber;//Индекс элемента, идущего после последнего(число элементов).

    const size_t DEFAULT_SIZE = 8;//Начальный размер буфера.
    const size_t MULT = 2;//Множитель увеличения размера.
    //Функция, увеличивающая размер буфера.
    void grow() {
        if (capacity != 0) {
            capacity *= MULT;
        } else {
            capacity = DEFAULT_SIZE;
        }

        auto newBuffer = new T[capacity];
        std::memmove(newBuffer, buffer, sizeof(T) * elemNumber);
        delete[] buffer;
        buffer = newBuffer;
    }
};

template <class T,
        class Container = DynamicArray<T>,
        class Compare = std::less<T>>
class Heap {
public:
    Heap(): container(new Container) {}
    Heap(const Heap<T, Container, Compare>& other): container(new Container(*other.container)) {}
    ~Heap() { delete container; }

    Heap<T, Container, Compare>& operator=(const Heap<T, Container, Compare>& other) {
        if (this == &other)
            return *this;

        delete container;
        container = new Container(*other.container);

        return *this;
    }
    void push(const T& value) {
        container->pushBack(value);
        siftUp(container->size() - 1);
    }
    T pop() {
        assert(!isEmpty());

        T result = (*container)[0];

        (*container)[0] = container->popBack();
        if (!isEmpty()) {
            siftDown(0);
        }

        return result;
    }

    T& top() {
        assert(!isEmpty());

        return (*container)[0];
    }
    bool isEmpty() {
        return container->isEmpty();
    }

private:
    Container* container;
    Compare compare;

    void siftUp(size_t index) {
        assert(index < container->size());

        while (index > 0) {
            size_t parent = (index - 1) / 2;
            if (!compare((*container)[parent], (*container)[index])) {
                return;
            }
            std::swap((*container)[index], (*container)[parent]);
            index = parent;
        }
    }
    void siftDown(size_t index) {
        assert(index < container->size());

        while (index < container->size()) {
            size_t left = 2 * index + 1;
            size_t right = 2 * index + 2;

            size_t largest = index;
            if (left < container->size() && compare((*container)[largest], (*container)[left])) {
                largest = left;
            }
            if (right < container->size() && compare((*container)[largest],(*container)[right])) {
                largest = right;
            }

            if (largest == index) {
                return;
            }
            std::swap((*container)[largest], (*container)[index]);
            index = largest;
        }
    }
};

struct Pair {
    Pair(int value = 0, int index = 0): value(value), index(index) {}
    int index;
    int value;
    bool operator<(const Pair& other) const {
        return value < other.value;
    }
};

void slidingMax(const int* A, int n, int k);

int main() {
    int n = 0;
    std::cin >> n;
    auto A = new int[n];
    for(int i = 0; i < n; ++i) {
        std::cin >> A[i];
    }
    int k = 0;
    std::cin >> k;

    slidingMax(A, n, k);

    delete[] A;

    return 0;
}

void slidingMax(const int* A, int n, int k) {
    assert(A != nullptr && n > 0 && k > 0);

    Heap<Pair> heap;
    for (int i = 0; i < k; ++i) {
        heap.push(Pair(A[i], i));
    }
    std::cout << heap.top().value << ' ';
    for (int i = 0; i + k < n; ++i) {
        heap.push(Pair(A[i + k], i + k));
        while (heap.top().index <= i) {
            heap.pop();
        }
        std::cout << heap.top().value << ' ';
    }
}