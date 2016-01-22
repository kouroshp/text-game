#include "map.h"
#include "context.h"
#include "location.h"
#include "inventory.h"

void map_init(struct context* context)
{
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            context->map[x][y] = NULL;
        }
    }

    struct location* house = malloc(sizeof(struct location));
    location_init(house, "Shack", "a dark ominous dwelling, old and forgotten.");
    struct item* key = malloc(sizeof(struct item));
    key->name = "Iron Key";
    key->weight = 1;
    inventory_add(&house->inventory, key);
    context->map[1][1] = house;
}

void map_free(struct context* context)
{
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            if (context->map[x][y] != NULL) {
                free(context->map[x][y]);
            }
        }
    }
}

