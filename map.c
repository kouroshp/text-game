#include "map.h"
#include "context.h"
#include "location.h"
#include "inventory.h"

void map_init(struct context *context)
{
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            struct location *location = malloc(sizeof(*location));
            location_init(location);
            context->map[x][y] = location;
        }
    }

    struct area *house = malloc(sizeof(*house));
    area_init(house, "Shack", "a dark ominous dwelling, old and forgotten.");
    context->map[1][1]->area = house;
    context->map[1][2]->area = house;
    context->map[2][1]->area = house;
    context->map[2][2]->area = house;

    struct location *location = context->map[1][1];
    location->exit = true;
    struct item *key = item_object_new("key", "Iron Key", 1);
    struct item *dagger = item_weapon_new("dagger", "Iron Dagger", 3, 5);
    inventory_add(&location->inventory, key);
    inventory_add(&location->inventory, dagger);
    struct person *george = malloc(sizeof(*george));
    person_init(george, "George");
    vector_add(&location->people, george);
    struct item *club = item_weapon_new("club", "Club", 8, 10);
    george->weapon = club;
}

void map_free(struct context *context)
{
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            if (context->map[x][y] != NULL) {
                location_free(context->map[x][y]);
                free(context->map[x][y]);
            }
        }
    }
}

