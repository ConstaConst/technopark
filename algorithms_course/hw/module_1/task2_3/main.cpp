/*
2_3. Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию. A[0..n-1] и B[0..m-1]. n >> m.
Найдите их пересечение. Требуемое время работы: O(m * log m), где m - позиция элемента B[m-1] в массиве A.
В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска элемента B[i-1].
n, m ≤ 10000.
in: 5           out: 1 3 5
    3
    1 2 3 4 5
    1 3 5
 */

#include <iostream>
#include <cassert>

//Поиск пересечения, которое записывается в result
void searchOfIntersection(const int* A, int n, const int* B, int m, int* result, int& resultCount);
//Бинарный поиск, возвращает индекс элемента, если он есть в массиве, иначе возвращает позицию первого бОльшего,
//если value самый большой элемент, возвращается n
int binarySearch(const int* arr, int count, int value);
//Поиск верхней границы для value в массиве А, граница всегда больше value
int searchOfTopSide(const int* A, int n, int value);

int main() {

    //Ввод данных
    int n = 0;
    int m = 0;
    std::cin >> n >> m;
    auto A = new int[n];
    auto B = new int[m];
    for (int i = 0; i < n; ++i) {
        std::cin >> A[i];
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> B[i];
    }
    //Выделение места под результат
    auto result = new int[m];
    int resultCount = 0;
    searchOfIntersection(A, n, B, m, result, resultCount);
    //Вывод результата
    for (int i = 0; i < resultCount; ++i) {
        std::cout << result[i] << ' ';
    }

    delete[] A;
    delete[] B;
    delete[] result;

    return 0;
}

void searchOfIntersection(const int* A, int n, const int* B, int m, int* result, int& resultCount) {
    //Проверка входных данных
    assert(A != nullptr && n > 0 && B != nullptr && m > 0 && result != nullptr);
    resultCount = 0;
    //Ищем границы поиска: bottomSide - предыдущий результат поиска, topSide - searchOfTopSide()
    //должно выполняться равенство A[bottomSide] <= B[i] < A[topSide]
    int bottomSide = 0;
    int topSide = 1;
    for (int i = 0; i < m && bottomSide < n; ++i) {
        topSide = searchOfTopSide(A + bottomSide, n - bottomSide, B[i]) + bottomSide;
        bottomSide = binarySearch(A + bottomSide, topSide - bottomSide, B[i]) + bottomSide;
        if (bottomSide < n && A[bottomSide] == B[i]) {
            result[resultCount++] = B[i];
            bottomSide++;
        }
    }
}

int binarySearch(const int* arr, int count, int value) {
    //Проверка входных данных
    assert(arr != nullptr && count > 0);

    int left = 0;
    int right = count;

    while (left < right) {
        int middle = (left + right) / 2;
        if (value <= arr[middle]) {
            right = middle;
        } else {
            left = middle  + 1;
        }
    }
    return left;
}

int searchOfTopSide(const int* A, int n, int value) {
    //Проверка входных данных
    assert(A != nullptr && n > 0);
    //Смотрим элементы А по индексам 2^n, пока не найдем первый бОльший value
    int topSide = 1;
    while (topSide < n && A[topSide] <= value) {
        topSide *= 2;
    }
    //Наибольшее значение, которое возвращается, - n
    return topSide >= n ? n : topSide;
}