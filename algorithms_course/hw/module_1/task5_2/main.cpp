/*
5_2. Современники.
Группа людей называется современниками если был такой момент, когда они могли собраться вместе.
Для этого в этот момент каждому из них должно было  уже исполниться 18 лет, но ещё не исполниться 80 лет.
Дан список Жизни Великих Людей. Необходимо получить максимальное количество современников.
В день 18летия человек уже может принимать участие в собраниях, а в день 80 летия и в день смерти уже не может.
Замечание. Человек мог не дожить до 18-летия, либо умереть в день 18-летия. В этих случаях принимать участие в собраниях он не мог.
 in: 3                      out: 3
     2 5 1980 13 11 2055
     1 1 1982 1 1 2030
     2 1 1920 2 1 2000
 */
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>

//Контейнер для удобного хранения дат, которые будут точками на временной прямой.
class Date {
public:
    Date(int day = 0, int month = 0, int year = 0, bool finish = false):
            day(day),
            month(month),
            year(year),
            finish(finish) {}
    //Делаем 2 точки, удовлетворяющие условию [start, finish) (активная жизнь людей).
    friend void makeCapable(Date& start, Date& finish);
    friend  std::istream& operator>>(std::istream& in , Date& date);
    bool operator< (const Date& other) const;

    bool isFinish() const;

private:
    int day;
    int month;
    int year;
    bool finish;
};

std::istream& operator>>(std::istream& in, Date& date) {
    std::cin >> date.day >> date.month >> date.year;

    return in;
}
bool Date::operator<(const Date& other) const {
    if (year < other.year) {
        return true;
    } else if (year == other.year) {
        if (month < other.month) {
            return true;
        } else if (month == other.month) {
            if (day < other.day) {
                return true;
            } else if (day == other.day) {
                //смерть(или 80 лет) считаем меньше, тк в этот день человек не может встречаться.
                return finish;
            }
        }
    }
    return false;
}

//Сливание двух отсортированных буферов first и second в newBuffer, размер newBuffer должен быть >= first + second
//(самостоятельная функция, не связанная с mergeSort())
template<class T, class Compare>
void merge(T* firstBegin, T* firstEnd, T* secondBegin, T* secondEnd, T* newBuffer, Compare compare);
//Шаблон функции сортировки слияния без рекурсии (восходящей)
template <class T, class Compare = std::less<T>>
void mergeSort(T* first, T* last, Compare compare = std::less<T>());
//Поиск максимального количества современников
int findMaxGroup(Date* dateLine, int n);

int main() {
    int n = 0;
    std::cin >> n;
    n *= 2;
    auto dateLine = new Date[n];
    for (int i = 0; i < n; i += 2) {
        std::cin >> dateLine[i] >> dateLine[i + 1];
        makeCapable(dateLine[i], dateLine[i + 1]);
    }

    std::cout << findMaxGroup(dateLine, n);

    delete[] dateLine;
    return 0;
}

void makeCapable(Date& start, Date& finish) {
    Date elderlyAge = start;
    elderlyAge.year += 80;
    start.year += 18;//Делаем совершеннолетним, учитывая, что может умереть раньше
    if (finish < start) {
        start = finish;
    }
    //Если успел дожить до 80, смещаем finish
    if (elderlyAge < finish) {
        finish = elderlyAge;
    }
    finish.finish = true;
}

bool Date::isFinish() const {
    return finish;
}


template<class T, class Compare>
void merge(T* firstBegin, T* firstEnd, T* secondBegin, T* secondEnd, T* newBuffer, Compare compare) {
    assert(firstBegin != nullptr && firstEnd != nullptr
           && secondBegin != nullptr && secondEnd != nullptr && newBuffer != nullptr);
    int i = 0;
    //Пока не кончился один из буферов, кладем меньший элемент в результирующий
    while (firstEnd != firstBegin && secondEnd != secondBegin) {
        if (compare(*firstBegin, *secondBegin)) {
            newBuffer[i++] = *(firstBegin++);
        } else {
            newBuffer[i++] = *(secondBegin++);
        }
    }
    //Перемещаем оставшийся буфер
    if (firstBegin != firstEnd) {
        memcpy(newBuffer + i, firstBegin, (firstEnd - firstBegin) * sizeof(T));
    } else {
        memcpy(newBuffer + i, secondBegin, (secondEnd - secondBegin) * sizeof(T));
    }
}

template <class T, class Compare = std::less<T>>
void mergeSort(T* first, T* last, Compare compare) {
    assert(first != nullptr && last != nullptr);
    size_t size = last - first;
    //Парадигма - объединяй и властвуй, собираем из меких частей (1 + 1 -> 2 ... 2 + 2 -> 4 ... -> n)
    for (size_t partSize = 1; partSize < size; partSize *= 2) {
        for (size_t i = 0; i < size; i += partSize * 2) {
            if (i + partSize >= size) {
                break;
            }
            size_t mergeLast = (i + 2 * partSize > size ? size : i + 2 * partSize);// смотрим границу второй группы,
                                                                                // тк может выйти за пределы массива
            auto mergeBuffer = new T[mergeLast - i];
            merge(first + i, first + i + partSize, first + i + partSize, first + mergeLast, mergeBuffer, compare);
            memcpy(first + i, mergeBuffer, (mergeLast - i) * sizeof(T));
            delete[] mergeBuffer;
        }
    }
}

int findMaxGroup(Date* dateLine, int n) {
    assert(dateLine != nullptr && n > 0);

    mergeSort<Date>(dateLine, dateLine + n);
    //Cчитаем активной жизнью [start ... finish)
    //Если встречаем [ добавляем человека в текущую группу, ) - убираем; и запоминаем наибольшую
    int maxGroup = 0;
    int curGroup = 0;
    for (int i = 0; i < n; ++i) {
        if (dateLine[i].isFinish() == false) {
            curGroup++;
            if (curGroup > maxGroup) {
                maxGroup = curGroup;
            }
        } else {
            curGroup--;
        }
    }

    return maxGroup;
}

