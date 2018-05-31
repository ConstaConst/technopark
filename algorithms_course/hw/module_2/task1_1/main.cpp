/*  1_1. Хэш-таблица.
Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае,
когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки
принадлежности данной строки множеству.

Для разрешения коллизий используйте квадратичное пробирование. i-ая проба
g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.

 in:    + hello     out:    OK
        + bye               OK
        ? bye               OK
        + bye               FAIL
        - bye               OK
        ? bye               FAIL
        ? hello             OK
 */


#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using std::string;

class StringHashTable {
public:
    StringHashTable();

    bool Has(const string& key) const;
    bool Add(const string& key);
    bool Remove(const string& key);

private:
    size_t StringHash(const string& key, size_t size) const;
    size_t QuadraticIncrement(size_t hash, size_t i, size_t size) const;
    void Grow();

    std::vector<string> table_;
    size_t elems_number_; //Количество реальных элементов в таблице.

    const size_t kInitSize_ = 8;
    const size_t kA_ = 3;//Как выбрать а? // Коэффициент многочлена Горнера (Взаимно простой с размером таблицы).
    const float kOccupancyFactor_ = 0.75;
    const string kDeletedSpace_ = "#$%&@DELETED#$%&@";
    const string kEmptySpace_ = "#$%&@EMPTY#$%&@";
};

StringHashTable::StringHashTable() {
    table_ = std::vector<string>(kInitSize_, kEmptySpace_);
    elems_number_ = 0;
}

bool StringHashTable::Has(const string& key) const {
    assert(key != kEmptySpace_ && key != kDeletedSpace_);

    size_t hash = StringHash(key, table_.size());
    for (size_t i = 0; i < table_.size() && table_[hash] != kEmptySpace_; ++i) {
        hash = QuadraticIncrement(hash, i, table_.size());
        if (table_[hash] == key) {
            return true;
        }
    }
    return false;
}

bool StringHashTable::Add(const string& key) {
    assert(key != kEmptySpace_ && key != kDeletedSpace_);

    if (float(elems_number_ + 1) / table_.size() >= kOccupancyFactor_) {
        Grow();
    }

    size_t hash = StringHash(key, table_.size());
    size_t firstDeleted = table_.size();
    for (size_t i = 0; i < table_.size() && table_[hash] != kEmptySpace_; ++i) {
        hash = QuadraticIncrement(hash, i, table_.size());
        if (table_[hash] == key) {
            return false;
        }
        if (firstDeleted == table_.size() && table_[hash] == kDeletedSpace_) {
            firstDeleted = hash;
        }
    }

    if (firstDeleted != table_.size()) {
        table_[firstDeleted] = key;
    } else {
        table_[hash] = key;
    }
    ++elems_number_;
    return true;
}

bool StringHashTable::Remove(const string& key) {
    assert(key != kEmptySpace_ && key != kDeletedSpace_);

    size_t hash = StringHash(key, table_.size());
    for (size_t i = 0; i < table_.size() && table_[hash] != kEmptySpace_; ++i) {
        hash = QuadraticIncrement(hash, i, table_.size());
        if (table_[hash] == key) {
            table_[hash] = kDeletedSpace_;
            --elems_number_;
            return true;
        }
    }
    return false;
}
// Хэш-функция для строки с использованием многочлена Горнера.
size_t StringHashTable::StringHash(const string& key, size_t size) const {
    assert(key != kEmptySpace_);

    size_t hash = 0;
    for (char i : key) {
        hash = (hash * kA_ + i) % size;
    }
    return hash;
}
//Для квадратичного пробирования.
size_t StringHashTable::QuadraticIncrement(size_t hash, size_t i, size_t size) const {
    return (hash + i) % size;
}
// При увеличении таблицы выполняем перехэширование реальных элементов.
void StringHashTable::Grow() {
    std::vector<string> new_table = std::vector<string>(table_.size() * 2, kEmptySpace_);

    for (const auto &key: table_) {
        if (key != kEmptySpace_ && key != kDeletedSpace_) {
            size_t hash = StringHash(key, new_table.size());
            for (size_t i = 0; i < new_table.size() && new_table[hash] != kEmptySpace_; ++i) {
                hash = QuadraticIncrement(hash, i, new_table.size());
            }
            new_table[hash] = key;
        }
    }

    table_ = new_table;
}


void test_hashTable(StringHashTable& hashTable);



int main() {
    StringHashTable hashTable;

    test_hashTable(hashTable);

    return 0;
}


void test_hashTable(StringHashTable& hashTable) {
    char command = 0;
    string key;
    while( std::cin >> command >> key ) {
        switch( command ) {
            case '?':
                std::cout << ( hashTable.Has(key) ? "OK" : "FAIL" ) << std::endl;
                break;
            case '+':
                std::cout << ( hashTable.Add(key) ? "OK" : "FAIL" ) << std::endl;
                break;
            case '-':
                std::cout << ( hashTable.Remove(key) ? "OK" : "FAIL" ) << std::endl;
                break;
            default:
                assert(false);
        }
    }
}