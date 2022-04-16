#pragma once

#include "data_types.hpp"
#include "fairy_tail.hpp"
#include "util.hpp"

#include <string.h>

/*
 * Класс для хранения и изображения текущих знаний о карте одного из персонажей.
 */

// Массив 22 на 22, т.к. учитываем то, что персонаж может начать с края, но считать, что он в середине.
// Это оправдывает 20 элементов. И еще два, чтобы отображать края карты как препядствия.
constexpr int CAPACITY = 22;

class POV {
private:
    // Карта
    MapObject map[CAPACITY][CAPACITY];

    // Изначальное положение персонажа на карте
    Position position = { 10, 10 };

    const Character character;
    Fairyland * world;

public:
    POV(Character character, Fairyland * world) :
        character(character),
        world(world)
    {
        // Учтем, что изначально мы не знаем свое окружение
        memset(map, MapObject::Unknown, sizeof(map));

        // Но, очевидно, что персонаж начинает на свободной клетке
        map[position.y][position.x] = MapObject::Passage;
    }

    Fairyland * getWorld() {
        return world;
    }

    Position getPosition() {
        return this->position;
    }

    // Изобразить в stdout представление об окружении персонажа.
    void display();

    /** Обновить сведение о том, какого типа клетка находится
     * по координатам `position`
     */
    void expose(Position position, MapObject mapObj) {
        map[position.y][position.x] = mapObj;
    }

    /** Проверить есть ли в направлении `direction` свободное пространство
     * и обновить видинее персонажа
     * @return Удалось ли переместить персонажа
     */
    bool checkout(Direction direction);

    /* Определить вид клеток вокруг персонажа */
    void lookAround();
};
