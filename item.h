#ifndef ITEM_H
#define ITEM_H

typedef enum {
    OBJECT,
    WEAPON
} item_type;

struct item {
    const char *name;
    const char *description;
    unsigned int weight;
    item_type type;
    unsigned int damage;
};

struct item *item_object_new(const char *name, const char *description, unsigned int weight);
struct item *item_weapon_new(const char *name, const char *description, unsigned int weight, unsigned int damage);

#endif
