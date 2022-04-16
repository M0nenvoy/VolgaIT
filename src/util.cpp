#include "util.hpp"

Position direction2position(Direction direction) {
    switch (direction) {
        case (Direction::Left)  : return { -1,  0 };
        case (Direction::Right) : return {  1,  0 };
        case (Direction::Up)    : return {  0, -1 };
        case (Direction::Down)  : return {  0,  1 };
        case (Direction::Pass)  : return {  0,  0 };
    }
}

Direction reverseDirection(Direction direction) {
    switch (direction) {
        case (Direction::Left)  : return Direction::Right;
        case (Direction::Right) : return Direction::Left;
        case (Direction::Up)    : return Direction::Down;
        case (Direction::Down)  : return Direction::Up;
        case (Direction::Pass)  : return Direction::Pass;
    }
}
