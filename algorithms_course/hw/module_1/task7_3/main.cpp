/*
7_3. Binary MSD для long long.
Дан массив неотрицательных целых 64-разрядных чисел. Количество чисел не больше 10^6.
Отсортировать массив методом MSD по битам (бинарный QuickSort).
 in: 3              out: 4 7 1000000
     4 1000000 7

 */

#include <iostream>
#include <cassert>

#define LL_MAX_BIT 63

//Возвращает position бит.
template <class T>
bool getBit(T* value, size_t position);
//MSD binary quick sort.
template <class T>
void binaryQuickSort(T* begin, T* end, size_t maxBit);

int main() {
    int n = 0;
    std::cin >> n;
    auto array =  new unsigned long long[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> array[i];
    }

    binaryQuickSort<unsigned long long>(array, (array + n), LL_MAX_BIT);
    for (int i = 0; i < n; ++i) {
        std::cout << array[i] << " ";
    }

    delete[] array;
    return 0;
}

template <class T>
bool getBit(T& value, size_t position) {
    return (value >> position) & 1;
}

template <class T>
void binaryQuickSort(T* begin, T* end, size_t maxBit) {
    assert(begin != nullptr && end != nullptr);
    //Деление по maxBit на 0..01..1.
    T* i = begin;
    for (T* j = begin; j < end; ++j) {
        if (getBit<T>(*j, maxBit) == 0) {
            std::swap(*(i++), *j);
        }
    }
    //Рекурсивно он поделенных частей.
    if ((end - begin) > 1) {
        binaryQuickSort<T>(begin, i, maxBit - 1);
        binaryQuickSort<T>(i, end, maxBit - 1);
    }
}