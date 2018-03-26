/*
6_1. Реализуйте стратегию выбора опорного элемента “медиана трёх”.
Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
    Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n.
Требуется найти k-ю порядковую статистику. т.е. напечатать число,
которое бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве.
    Напишите нерекурсивный алгоритм.
    Требования к дополнительной памяти: O(n). Требуемое среднее время работы: O(n).
Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.
Описание для случая прохода от начала массива к концу:
    -Выбирается опорный элемент. Опорный элемент меняется с последним элементом массива.
    -Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного.
Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат нерассмотренные элементы.
Последним элементом лежит опорный.
    -Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
    -Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
    -Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j.
Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
    -В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.

    in: 10 4                    out: 5
        1 2 3 4 5 6 7 8 9 10
*/
#include <iostream>
#include <cassert>


//Поиск медианы трех, выбирает среедний элемент из a[i], a[j], a[k] и возвращает его индекс.
template <class T, class Compare = std::less<T>>
size_t medianOfTree(const T* a, size_t i, size_t j, size_t k, Compare compare = std::less<T>());

//Деление массива на 2 части по pivot.
template <class T, class Compare = std::less<T>>
size_t partition(T* a, size_t n, Compare compare = std::less<T>());

//Возращает элемент, который бы стоял на k-ом месте в отсортированном массиве.
template <class T, class Compare = std::less<T>>
T& searchKStatistic(T* a, size_t n, size_t k, Compare compare = std::less<T>());


int main() {
    size_t n = 0;
    size_t k = 0;
    std:: cin >> n >> k;
    auto a = new int[n];
    for (size_t i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::cout << searchKStatistic<int>(a, n, k);

    delete[] a;

    return 0;
}

template <class T, class Compare = std::less<T>>
size_t medianOfTree(const T* a, size_t i, size_t j, size_t k, Compare compare) {
    assert(a != nullptr);
    if (compare(a[j], a[i])) {
        if (compare(a[k], a[i])) {
            return (compare(a[k], a[j])) ? j : k;
        } else {
            return i;
        }
    } else if (compare(a[k], a[j])) {
        return (compare(a[k], a[i])) ? i : k;
    } else {
        return j;
    }
}
template <class T, class Compare = std::less<T>>
size_t partition(T* a, size_t n, Compare compare) {
    assert(a != nullptr);

    std::swap(a[n - 1], a[medianOfTree(a, 0, n / 2, n - 1, compare)]);
    size_t pivot = n - 1;

    size_t i = 0;
    for (size_t j = 0; j != pivot; ++j) {
        if (!compare(a[pivot], a[j])) {
            std::swap(a[i++], a[j]);
        }
    }

    std::swap(a[pivot], a[i]);

    return i;
}

template <class T, class Compare = std::less<T>>
T& searchKStatistic(T* a, size_t n, size_t k, Compare compare) {
    assert(a != nullptr && k <= n - 1);

    size_t left = 0;
    size_t right = n;
    size_t pivot = 0;

    while (k != (pivot = partition(a + left, right - left, compare) + left)) {//+left (чтобы получить индекс в исходном массиве)
        // , тк partition() вернет индекс в массиве [a + left ... a + right)
        //Выбор стороны
        if (k < pivot) {
            right = pivot;
        } else {
            left = pivot + 1;
        }
    }

    return a[pivot];
}
