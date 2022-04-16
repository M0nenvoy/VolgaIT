#pragma once

struct Position {
    int x, y;
    Position operator+(Position other) {
        return { x + other.x, y + other.y };
    }
    bool operator==(Position other) {
        return ( x == other.x && y == other.y );
    }
};

enum MapObject {
    Obstacle    = '#',
    Passage     = '.',
    Ivan        = '@',
    Elena       = '&',
    Unknown     = '?'
};
