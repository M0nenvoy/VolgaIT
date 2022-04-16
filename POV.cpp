#include "POV.hpp"

void POV::display() {
    // Показываем персонажа
    map[position.y][position.x] = (character == Character::Ivan)
        ? MapObject::Ivan
        : MapObject::Elena;

    // Показываем то, что знаем.
    for (int row = 0; row < CAPACITY; row++) {
        for (int col = 0; col < CAPACITY; col++) {
            std::cout << static_cast<char>(map[row][col]);
        }
        std::cout << '\n';
    }
    // Меняем персонажа на свободное пространство.
    map[position.y][position.x] = MapObject::Passage;
}

bool POV::checkout(Direction direction) {
    Position disposition = direction2position(direction);
    Position newPosition = position + disposition;

    if (!world->canGo(character, direction)) {
        expose(newPosition, MapObject::Obstacle);
        return false;
    }
    expose(newPosition, MapObject::Passage);
    this->position = newPosition;

    return true;
}

void POV::lookAround() {
    Position left, right, top, bottom;
    left    = this->position + Position { -1,  0 };
    right   = this->position + Position {  1,  0 };
    top     = this->position + Position {  0, -1 };
    bottom  = this->position + Position {  0,  1 };

    expose (left,    world->canGo(character, Direction::Left)   ? MapObject::Passage : MapObject::Obstacle);
    expose (right,   world->canGo(character, Direction::Right)  ? MapObject::Passage : MapObject::Obstacle);
    expose (top,     world->canGo(character, Direction::Up)     ? MapObject::Passage : MapObject::Obstacle);
    expose (bottom,  world->canGo(character, Direction::Down)   ? MapObject::Passage : MapObject::Obstacle);
}
