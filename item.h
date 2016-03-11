#ifndef ITEM_H
#define ITEM_H

typedef enum {
    OBJECT,
    WEAPON
} item_type;

struct item {
    char* name;
    int weight;
    item_type type;
    int damage;
};

struct item* item_object_new(char* name, int weight);
struct item* item_weapon_new(char* name, int weight, int damage);

#endif
