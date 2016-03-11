#include <stdlib.h>
#include "item.h"

struct item* item_object_new(char* name, int weight)
{
    struct item* item = malloc(sizeof(struct item));
    item->name = name;
    item->weight = weight;
    item->type = OBJECT;
    return item;
}

struct item* item_weapon_new(char* name, int weight, int damage)
{
    struct item* item = malloc(sizeof(struct item));
    item->name = name;
    item->weight = weight;
    item->damage = damage;
    item->type = WEAPON;
    return item;
}
