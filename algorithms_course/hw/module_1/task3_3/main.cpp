/*
3_3. Cледует написать структуру данных, обрабатывающую команды push* и pop*.
Реализовать очередь с помощью двух стеков. Использовать стек, реализованный с помощью динамического буфера.
Формат входных данных.
В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.
a = 1 - push front
a = 2 - pop front
a = 3 - push back
a = 4 - pop back
Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных, то ожидается “-1”.
Формат выходных данных.
Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
*/

#include <iostream>
#include <cstring>
#include <cassert>

//Шаблон класса Динамический массив, для динамического буфера
template <class T>
class DynamicArray {
public:
    DynamicArray(): buffer(nullptr), capacity(0), size(0) {}
    DynamicArray(const DynamicArray<T>& other) {
        size = other.size;
        capacity = other.capacity;
        buffer = new T[size];
        std::memcpy(buffer, other.buffer, sizeof(T) * size);
    }
    ~DynamicArray() { delete[] buffer; }

    DynamicArray<T>& operator=(const DynamicArray<T>& other) {
        if (this == &other)
            return *this;

        size = other.size;
        capacity = other.capacity;
        delete[] buffer;
        buffer = new T[size];
        std::memcpy(buffer, other.buffer, sizeof(T) * size);

        return *this;
    }
    void pushBack(const T& value) {
        if (size == capacity) {
            grow();
        }
        buffer[size++] = value;
    }
    T& popBack() {
        assert(!isEmpty());
        return buffer[--size];
    }
    bool isEmpty() {
        return size == 0;
    }

private:
    T* buffer;
    size_t capacity;
    size_t size;//Индекс элемента, идущего после последнего.

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
        std::memmove(newBuffer, buffer, sizeof(T) * size);
        delete[] buffer;
        buffer = newBuffer;
    }
};
//В Container должны быть реализованы функции: pushBack(), pushBack(), конструктор копирования, оператор присваивания:
template <class T,
        class Container = DynamicArray<T>>
class Stack {
public:
    Stack(): container(new Container) {}
    Stack(const Stack<T, Container>& other): container(new Container(*other.container)) {}
    ~Stack() { delete container; }

    Stack<T, Container>& operator=(const Stack<T, Container>& other) {
        if (this == &other)
            return *this;

        delete container;
        container = new Container(*other.container);

        return *this;
    }
    void push(const T& value) {
        container->pushBack(value);
    }
    T& pop() {
        return container->popBack();
    }
    bool isEmpty() {
        return container->isEmpty();
    }

private:
    Container* container;
};
//Шаблон очереди, реализованной на 2х стеках.
template <class T>
class Queue {
public:
    Queue(): inBuffer(new Stack<T>), outBuffer(new Stack<T>) {}
    Queue(const Queue<T>& other): inBuffer(new Stack<T>(*other.inBuffer)), outBuffer(new Stack<T>(*other.outBuffer)) {}
    ~Queue() {
        delete inBuffer;
        delete outBuffer;
    }

    Queue<T>& operator=(const Queue<T>& other) {
        if (this == &other)
            return *this;

        delete inBuffer;
        delete outBuffer;
        inBuffer = new Stack<T>(*other.inBuffer);
        outBuffer = new Stack<T>(*other.inBuffer);

        return *this;
    }
    void push(const T& value) {
        inBuffer->push(value);
    }
    T& pop() {
        assert(!isEmpty());
        //Если outBuffer пуст, заполням его значениями из inBuffer.
        if (outBuffer->isEmpty()) {
            while (!inBuffer->isEmpty()) {
                outBuffer->push(inBuffer->pop());
            }
        }
        return outBuffer->pop();
    }
    bool isEmpty() {
        return inBuffer->isEmpty() && outBuffer->isEmpty();
    }

private:
    Stack<T>* inBuffer;//Для push().
    Stack<T>* outBuffer;//Для pop().
};

//Возвращает true, если все команды отработали правильно, иначе - false.
bool checkQueueWorking(Queue<int>& queue, int n);

int main() {
    Queue<int> queue;
    int n = 0;
    std::cin >> n;

    if (checkQueueWorking(queue, n)) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }

    return 0;
}

bool checkQueueWorking(Queue<int>& queue, int n) {
    assert(queue.isEmpty() && n > 0);

    bool isCorrect = true;
    int command = 0;
    int value = 0;
    for (int i = 0; isCorrect && i < n; ++i) {
        std::cin >> command >> value;
        switch (command) {
            case 2://pop()
                if (queue.isEmpty() && value != -1 || !queue.isEmpty() && value != queue.pop()) {
                    isCorrect = false;
                }
                break;
            case 3://push()
                queue.push(value);
                break;
            default:
                isCorrect = false;
                break;
        }
    }

    return isCorrect;
}