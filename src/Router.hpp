#pragma once

#include "fairy_tail.hpp"
#include "data_types.hpp"
#include "util.hpp"

#include <stack>
#include <string.h>

struct Crossroad {
    Position position;
    Direction direction;
};

// Структура данных, хранящая HISTORY_SIZE последних положений в неопределенном порядке.
// Оптимальный размер HISTORY_SIZE зависит от размера максимального свободного участка.
// Чтобы покрыть даже самый наихудщий вариант, составим размер истории равный числу
// всех клеток.
constexpr int HISTORY_SIZE = 100;
struct HistoryPosition {
    Position data[HISTORY_SIZE];

    HistoryPosition() {
        memset( data, 0, sizeof(data));
    }
    void push(Position position) {
        data[overwrite_offset] = position;
        if (++overwrite_offset > HISTORY_SIZE - 1)
            overwrite_offset = 0;
    }
    bool contains(Position position) {
        for (int i = 0; i < HISTORY_SIZE; i++) {
            if (position == data[i]) return true;
        }
        return false;
    }
private:
    int overwrite_offset = 0; // Какой элемент перезаписать следующим
};

constexpr Direction directions[4] = { Direction::Right,
                                      Direction::Up,
                                      Direction::Down,
                                      Direction::Left };
class Router {
    bool backtracking = false;
    std::stack<Crossroad>   crossroads;
    std::stack<Direction>   history_direction;
    HistoryPosition         history_position = HistoryPosition();

public:
    /** Получить указание, в каком направлении двигаться персонажу.
     *  После этого важно обновить переменную charPos ( переместить ее в указанном направлении ).
     *  Также важно вызывать эту функцию с одним и тем же миром и персонажем.
     *  Учитывая все это, было бы умно использовать эту функцию в обертке какого-то класса,
     *  который бы .
     */
    Direction update(Fairyland * world, Character character, Position charPos) {
        if (backtracking) return backtrack(world, character, charPos);
        return explore(world, character, charPos);
    }
private:
    Direction backtrack(Fairyland * world, Character character, Position charPos);

    Direction explore(Fairyland * world, Character character, Position charPos);

    // Записать метаинформацию для объекта и вернуть
    // направление.
    Direction returnPassage(Direction passage, Position charPos);
};
