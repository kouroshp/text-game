#ifndef ITEM_H
#define ITEM_H

typedef enum {
    OBJECT,
    WEAPON
} item_type;

struct item {
    char *name;
    char *description;
    int weight;
    item_type type;
    int damage;
};

struct item *item_object_new(char *name, char *description, int weight);
struct item *item_weapon_new(char *name, char *description, int weight, int damage);

#endif
