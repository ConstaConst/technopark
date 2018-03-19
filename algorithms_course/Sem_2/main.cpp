#include <iostream>


struct CPoint {
    int x = 0;
    int y = 0;
    bool operator<(const CPoint& other) { return x < other.x; }

    CPoint
};

/*
//Вариант 1. Использование оператора Б в сортировке.
void BubbleSort(CPoint* begin, CPoint* end)
{
    const int size = end -begin;
    for(int i = 0; i < size - 1; ++i) {
        for(int j = 0; j < size - 1 - i; ++j) {
            if(begin[j + 1] < begin[j]) {
                std::swap(begin[j + 1], begin[j]);
            }
        }
    }
}
*/
/*
//Вариант 2. Использование функции сравнения.
//Сравнение точек по Евклидовому расстоянию от (0, 0)
bool ComparePointsByDistanceFromZero(const CPoint& left, const CPoint& right) {
    return left.x * left.x + left.y * left.y < right.x * right.x + right.y * right.y;
}

void BubbleSort(CPoint* begin, CPoint* end, bool (*compareFunction)(const CPoint&, const CPoint&))
{
    const int size = end -begin;
    for(int i = 0; i < size - 1; ++i) {
        for(int j = 0; j < size - 1 - i; ++j) {
            if (compareFunction(begin[j + 1], begin[j])) {
                std::swap(begin[j + 1], begin[j]);
            }
        }
    }
}
*/

//Вариант 3. Использование функтора.
//Функтор, сравнивающий точки по расстоянию от некоторой заданной
class CMyFunctor {
public:
    explicit CMyFunctor( const CPoint& center): center(center);
    bool operator()(const CPoint& left, const CPoint& right) {
        return (left.x - center.x) * (left.x - center.x) + (left.y - center.y) * (left.y - center.y) <
                (right.x - center.x) * (right.x - center.x) + (right.y - center.y) * (right.y - center.y)
    }

private:
    CPoint center;
};

void BubbleSort(CPoint* begin, CPoint* end, const CMyFunctor& functor)
{
    const int size = end -begin;
    for(int i = 0; i < size - 1; ++i) {
        for(int j = 0; j < size - 1 - i; ++j) {
            if (functor(begin[j + 1], begin[j])) {
                std::swap(begin[j + 1], begin[j]);
            }
        }
    }
}



int main() {
    int size = 0;
    std::cin >> size;
    CPoint* points = new CPoint[size];

    for(int i = 0; i < size; ++i) {
        std::cin >> points[i].x >> points[i].y;
    }


    for(int i = 0; i < size; ++i) {
        std::cout << '(' << points[i].x << ',' << points[i].y << ')' << std::endl;
    }

    delete[] points;
}