#include <string.h>
#include <jansson.h>
#include "map.h"
#include "context.h"
#include "location.h"
#include "inventory.h"
#include "vector.h"

static void populate_map(struct context *context, json_t *json);
static void populate_inventory(struct inventory *inventory, json_t *json);
static void populate_people(struct vector *people, json_t *json);

void map_init(struct context *context, json_t *data)
{
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            struct location *location = malloc(sizeof(*location));
            location_init(location);
            context->map[x][y] = location;
        }
    }

    vector_init(&context->areas, sizeof(struct area *));
    populate_map(context, data);
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

    for (int i = 0; i < context->areas.size; i++) {
        free(vector_get(&context->areas, i));
    }
    vector_free(&context->areas);
}

static void populate_map(struct context *context, json_t *json)
{
    for (int i = 0; i < json_array_size(json); i++) {
        json_t *object = json_array_get(json, i);
        json_t *name = json_object_get(object, "name");
        json_t *description = json_object_get(object, "description");

        struct area *area = malloc(sizeof(*area));
        area_init(area, json_string_value(name), json_string_value(description));
        vector_add(&context->areas, area);

        json_t *locations = json_object_get(object, "locations");

        for (int i = 0; i < json_array_size(locations); i++) {
            json_t *l = json_array_get(locations, i);
            json_t *x = json_object_get(l, "x");
            json_t *y = json_object_get(l, "y");
            json_t *exit = json_object_get(l, "exit");
            json_t *inventory = json_object_get(l, "inventory");
            json_t *people = json_object_get(l, "people");

            struct location *location = context->map[json_integer_value(x)][json_integer_value(y)];
            location->area = area;
            location->exit = json_boolean_value(exit);

            populate_inventory(&location->inventory, inventory);
            populate_people(&location->people, people);
        }
    }
}

static void populate_inventory(struct inventory *inventory, json_t *json)
{
    for (int i = 0; i < json_array_size(json); i++) {
        json_t *object = json_array_get(json, i);
        json_t *type = json_object_get(object, "type");
        json_t *name = json_object_get(object, "name");
        json_t *description = json_object_get(object, "description");
        json_t *weight = json_object_get(object, "weight");

        struct item *item;

        if (strncmp(json_string_value(type), "weapon", strlen("weapon")) == 0) {
            json_t *damage = json_object_get(object, "damage");
            item = item_weapon_new(json_string_value(name), json_string_value(description), json_integer_value(weight), json_integer_value(damage));
        }
        else {
            item = item_object_new(json_string_value(name), json_string_value(description), json_integer_value(weight));
        }

        inventory_add(inventory, item);
    }
}

static void populate_people(struct vector *people, json_t *json)
{
    for (int i = 0; i < json_array_size(json); i++) {
        json_t *object = json_array_get(json, i);
        json_t *name = json_object_get(object, "name");
        json_t *inventory = json_object_get(object, "inventory");
        json_t *weapon = json_object_get(object, "weapon");

        struct person *person = malloc(sizeof(*person));
        person_init(person, json_string_value(name));
        populate_inventory(&person->inventory, inventory);
        struct item *w = inventory_get(&person->inventory, json_string_value(weapon));
        if (w != NULL) {
            person->weapon = w;
        }

        vector_add(people, person);
    }
}
