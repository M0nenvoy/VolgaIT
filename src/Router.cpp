#include "Router.hpp"

Direction Router::returnPassage(Direction passage, Position charPos) {

    history_direction.push(passage);
    history_position.push(charPos);

    return passage;
}

Direction Router::backtrack(Fairyland * world, Character character, Position charPos) {
    Direction direction = reverseDirection(history_direction.top());

    // Вернулись к развилке.
    if ( charPos == crossroads.top().position ) {

        // На этот раз выбираем другой путь на развилке
        Direction direction = crossroads.top().direction;

        backtracking = false;
        crossroads.pop();
        return returnPassage(direction, charPos);
    }

    history_direction.pop();
    history_position.push(charPos);
    return direction;
}
Direction Router::explore(Fairyland * world, Character character, Position charPos) {
    // Направления, куда можно двигаться в данный момент в порядке приоритета
    // (исключаем движение в обратном направлении)
    Direction passages[4];
    int passagesFound = 0;

    // Движение обратное последнему
    Direction lastDirectionReverse = history_direction.empty()
        ? Direction::Pass
        : reverseDirection(history_direction.top());

    for (int dir = 0; dir < 4; dir++) {
        Direction current = directions[dir]; // Исследуемое направление
        bool passage = world->canGo(character, current);

        // Местоположение после движения согласно исследуемому направлению
        Position future = charPos + direction2position(current);
        // Считаем валидным исследуемое направление если...
        if (passage                                     // 1) Следуя ему возможно переместиться на свободную клетку
           && (directions[dir] != lastDirectionReverse) // 2) Не вернемся просто на предыдущее положение
           && !history_position.contains(future))       // 3) Не вернемся в одно из последних положений (предотвращает хождение кругами)
            { passages[passagesFound++] = current; }
    }

    if (passagesFound == 0) {
        // Если мы не нашли подходящего пути, то меняем состояние на `backtracking`
        // В этом состоянии персонаж будет возвращаться назад до тех пор, пока не
        // наткнется на последнюю записанную развилку.

        backtracking = true;
        return backtrack(world, character, charPos);
    }

    Direction passageChosen = passages[0];

    if (passagesFound != 1) {
        // Встретив развилку, выберем ту, которая с большей вероятностью приведет нас
        // к правому краю, и запишем в стек остальные.
        for (int i = 1; i < passagesFound; i++) { // Заполняем с конца согласно приоритету.
            Crossroad crossroad = { charPos, passages[i] };
            crossroads.push(crossroad);
        }
    }

    return returnPassage(passageChosen, charPos);
}
