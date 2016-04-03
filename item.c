#include <stdlib.h>
#include "item.h"

struct item *item_object_new(char *name,  char *description, int weight)
{
    struct item *item = malloc(sizeof(*item));
    item->name = name;
    item->description = description;
    item->weight = weight;
    item->type = OBJECT;
    return item;
}

struct item *item_weapon_new(char *name, char *description, int weight, int damage)
{
    struct item *item = malloc(sizeof(*item));
    item->name = name;
    item->description = description;
    item->weight = weight;
    item->damage = damage;
    item->type = WEAPON;
    return item;
}
