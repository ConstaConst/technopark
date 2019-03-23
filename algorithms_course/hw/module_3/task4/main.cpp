/* Задача 4. «Пятнашки»
Написать алгоритм для решения игры в “пятнашки”. Решением задачи является приведение к виду:
[ 1  2  3  4 ]
[ 5  6  7  8 ]
[ 9  10 11 12]
[ 13 14 15 0 ]
где 0 задает пустую ячейку.
Достаточно найти хотя бы какое-то решение. Число перемещений костяшек не обязано быть минимальным.
Формат входных данных
Начальная расстановка.
Формат выходных данных
Если решение существует, то в первой строке выходного файла выведите минимальное число перемещений костяшек,
которое нужно сделать, чтобы достичь выигрышной конфигурации, а во второй строке выведите соответствующую
последовательность ходов: L означает, что костяшка сдвинулась влево, R – вправо, U – вверх, D – вниз.
Если таких последовательностей несколько, то выведите любую из них. Если же выигрышная конфигурация недостижима,
то выведите в выходной файл одно число −1.
    in: 1 2 3 4         out: 1
        5 6 7 8              U
        9 10 11 0
        13 14 15 12
 */


#include <iostream>
#include <array>
#include <cassert>
#include <cstring>
#include <unordered_map>
#include <set>
#include <queue>
#include <algorithm>

const char FieldSize = 16;
const std::array<char, FieldSize> FinishField = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};

class GameState {
public:
    explicit GameState(const std::array<char, FieldSize>& _field) : field(_field) {
        emptyPos = -1;
        for( int i = 0; i < FieldSize; i++ )
            if( field[i] == 0 )
                emptyPos = i;
        assert( emptyPos != -1 );
    }
    GameState(const GameState& state) {
        (*this) = state;
    }

    bool isComplete() const {
        return field == FinishField;
    }

    bool isValid() const {
        int inv = 0;
        for (int i = 0; i<16; ++i)
            if (field[i])
                for (int j = 0; j<i; ++j)
                    if (field[j] > field[i])
                        ++inv;

        inv += 1 + emptyPos / 4;

        return inv % 2 == 0;
    }
    //Расчитывает минимальное количество перемещений до своей позиции для каждой костяшки
    int heuristic() const {
        int h = 0;
        int fullDist = 0;
        for (int i = 0; i < field.size(); ++i) {
            if (field[i] != 0) {
                fullDist = abs(field[i] - 1 - i);
            } else {
                fullDist = 16 - i;
            }
            h += fullDist / 4;
            fullDist %= 4;
            if (fullDist == 3) {
                h += 2;
            } else {
                h += fullDist;
            }
        }

        return h;
    }

    bool canMoveLeft() const {
        return emptyPos % 4 != 3;
    }
    bool canMoveRight() const {
        return emptyPos % 4 != 0;
    }
    bool canMoveUp() const {
        return emptyPos < 12;
    }
    bool canMoveDown() const {
        return emptyPos > 4;
    }

    GameState moveLeft() const {
        assert(canMoveLeft());

        GameState leftState(*this);
        std::swap(leftState.field[emptyPos], leftState.field[emptyPos + 1]);
        leftState.emptyPos++;
        return leftState;
    }
    GameState moveRight() const {
        assert(canMoveRight());

        GameState rightState(*this);
        std::swap(rightState.field[emptyPos], rightState.field[emptyPos - 1]);
        rightState.emptyPos--;
        return rightState;
    }
    GameState moveUp() const {
        assert(canMoveUp());

        GameState upState(*this);
        std::swap(upState.field[emptyPos], upState.field[emptyPos + 4]);
        upState.emptyPos += 4;
        return upState;
    }
    GameState moveDown() const {
        assert(canMoveDown());

        GameState downState(*this);
        std::swap(downState.field[emptyPos], downState.field[emptyPos - 4]);
        downState.emptyPos -= 4;
        return downState;
    }

    bool operator==(const GameState& state) const {
        return field == state.field;
    }
    //Наоборот, тк приоритет больше, если эвристика меньше
    bool operator<(const GameState& state) const {
        return heuristic() > state.heuristic();
    }
    GameState& operator=(const GameState& state) = default;

    friend struct StateHash;

private:
    std::array<char, FieldSize> field{};
    char emptyPos{};
};

struct StateHash {
    size_t operator()(const GameState& state) const
    {
        size_t hash = 0;
        for (int i : state.field) {
            hash = (hash * 31 + i);
        }

        return hash;
    }
};

std::string getSolution(const std::array<char, FieldSize>& field) {
    //std::unordered_map<GameState, char, StateHash> visited;
    std::unordered_map<GameState, std::string, StateHash> visited;
    GameState startState(field);

    std::priority_queue<GameState> queue;
    queue.emplace(startState);
    visited[startState] = "";

    GameState finishState(FinishField);
    while (!(queue.top() == finishState)) {
        GameState currentState = queue.top();
        queue.pop();

        if(currentState.canMoveLeft()) {
            GameState leftState = currentState.moveLeft();
            if(visited.find(leftState) == visited.end()) {
                queue.emplace(leftState);
                visited[leftState] = visited[currentState] + "L";
            }
        }
        if(currentState.canMoveRight()) {
            GameState rightState = currentState.moveRight();
            if(visited.find(rightState) == visited.end()) {
                queue.emplace(rightState);
                visited[rightState] = visited[currentState] + "R";
            }
        }
        if(currentState.canMoveUp()) {
            GameState upState = currentState.moveUp();
            if( visited.find(upState) == visited.end() ) {
                queue.emplace(upState);
                visited[upState] = visited[currentState] + "U";
            }
        }
        if(currentState.canMoveDown()) {
            GameState downState = currentState.moveDown();
            if( visited.find(downState) == visited.end() ) {
                queue.emplace(downState);
                visited[downState] = visited[currentState] + "D";
            }
        }
    }

    return visited[finishState];
}

int main() {
    std::array<char, FieldSize> field{};
    int pos = 0;
    for (int i = 0; i < 16; i++) {
        std::cin >> pos;
        field[i] = static_cast<char>(pos);
    }

    if (!GameState(field).isValid()) {
        std::cout << -1 << std::endl;
        return 0;
    }

    std::string solution = getSolution(field);
    std::cout << solution.size() << "\n" << solution << std::endl;
    return 0;
}