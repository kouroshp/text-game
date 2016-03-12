#include "map.h"
#include "context.h"
#include "location.h"
#include "inventory.h"

void map_init(struct context *context)
{
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            context->map[x][y] = NULL;
        }
    }

    struct location *house = malloc(sizeof(*house));
    location_init(house, "Shack", "a dark ominous dwelling, old and forgotten.");
    struct item *key = item_object_new("Iron Key", 1);
    struct item *dagger = item_weapon_new("Iron Dagger", 3, 5);
    inventory_add(&house->inventory, key);
    inventory_add(&house->inventory, dagger);
    context->map[1][1] = house;
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

