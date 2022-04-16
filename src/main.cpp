#include "fairy_tail.hpp"

#include "Router.hpp"
#include "data_types.hpp"
#include "POV.hpp"

#include <cstdlib>
#include <ctime>
#include <cstring>

/*
 * Пусть Иван посетит каждую клетку, пока Елена стоит на месте.
 */

int main()
{
    Fairyland world;
    Router router;
    POV povIvan     = POV(Character::Ivan, &world);

    for ( int i = 0; i < 1000; i++ ) {
        std::cout << "Turn " << i << '\n';
        povIvan.display();
        Direction direction = router.update(&world, Character::Ivan, povIvan.getPosition());
        povIvan.lookAround();
        povIvan.checkout(direction);

        bool meet = world.go(direction, Direction::Pass);
        if (meet) { // Елена и Иван встретились
            std::cout << "Елена и Иван встретились за " << world.getTurnCount() << " ходов.\n";

            // Совершим небольшой трюк, чтобы показать Елену на карте
            Position elenaPosition = povIvan.getPosition();
            povIvan.checkout( reverseDirection(direction) ); // переместим Ивана назад
            povIvan.expose( elenaPosition, MapObject::Elena ); // и на его месте покажем елену
            povIvan.display();

            break;
        }
    }

    return 0;
}
