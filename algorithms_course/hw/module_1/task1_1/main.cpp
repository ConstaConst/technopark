/*
1_1. Даны два массива целых чисел одинаковой длины A[0..n-1] и B[0..n-1].
Необходимо найти первую пару индексов i0 и j0, i0 ≤ j0, такую что A[i0] + B[j0] = max {A[i] + B[j], где 0 <= i < n, 0 <= j < n, i <= j}.
Время работы - O(n).
n ≤ 100000.
 in:4    4 -8 6 0   -10 3 1 1 out: 0 1
 */

#include <iostream>
#include <cassert>

//Основная функция, реализующая алгоритм поиска необходимой пары индексов
void searchMaxSum(const int *A, const int *B, int n, int &i0, int &j0);//????

int main() {
    //Ввод данных
    int n = 0;
    std::cin >> n;
    auto A = new int[n];
    auto B = new int[n];

    for (int i = 0; i < n; ++i) {
        std::cin >> A[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> B[i];
    }
    //Основная логика
    int i0 = 0, j0 = 0;//для записи результата
    searchMaxSum(A, B, n, i0, j0);
    //Вывод результата
    std::cout << i0 << ' ' << j0;

    delete[] A;
    delete[] B;

    return 0;
}

void searchMaxSum(const int * A, const int *B, int n, int &i0, int &j0) {
    //Проверка корректности входных значений
    assert(A != nullptr || B != nullptr || n > 0);

    //Начальная инициальзация искомых индексов
    i0 = j0 = n - 1;
    //Храним max j, тк сумма A[k] + B[k] может оказаться меньше A[i0] + B[j0], но A[k - a] + B[k] будет больше
    int maxJ = j0;

    for (int k = n - 2; k >= 0; --k) {
        if (B[k] >= B[maxJ]) {
            maxJ = k;
        }
        if (A[k] + B[maxJ] >= A[i0] + B[j0]) {
            i0 = k;
            j0 = maxJ;
        }
    }
}
