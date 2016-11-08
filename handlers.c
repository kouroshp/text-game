#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include "handlers.h"
#include "command.h"
#include "context.h"
#include "inventory.h"
#include "map.h"

static void move_player(struct context *context, int x, int y);

void handlers_init(struct vector *commands)
{
    command_add(commands, "exit", &handler_quit);
    command_add(commands, "quit", &handler_quit);
    command_add(commands, "inventory", &inventory_handler_show);
    command_add(commands, "pickup", &inventory_handler_pickup);
    command_add(commands, "drop", &inventory_handler_drop);
    command_add(commands, "attack", &player_handler_attack);
    command_add(commands, "equip", &player_handler_equip);
    command_add(commands, "move", &map_handler_move);
    command_add(commands, "where", &map_handler_where);
    command_add(commands, "look", &map_handler_look);
}

void handlers_free(struct vector *commands)
{
    for (int i = 0; i < commands->size; i++) {
        free(vector_get(commands, i));
    }
}

int handler_quit(struct vector *args, struct context *context)
{
    if (context->player.in_combat) {
        puts("Coward.");
    }
    return 1;
}

int inventory_handler_show(struct vector *args, struct context *context)
{
    inventory_contents_print(&context->player.inventory);
    return 0;
}

int inventory_handler_pickup(struct vector *args, struct context *context)
{
    if (args->size == 1) {
        puts("Pick up what?");
        return 0;
    }

    struct location *location = context->map[context->player.position.x][context->player.position.y];
    if (location == NULL || (location != NULL && location->inventory.size == 0)) {
        puts("There is nothing here to pick up...");
        return 0;
    }

    // Pick up item from location's inventory
    struct item *item = inventory_remove(&location->inventory, vector_get(args, 1));
    if (item != NULL) {
        if (!inventory_add(&context->player.inventory, item)) {
            puts("Your inventory is full!");
            // Put it back
            inventory_add(&location->inventory, item);
            return 0;
        }
    }
    else {
        puts("You can't pick up that...");
    }

    return 0;
}

int inventory_handler_drop(struct vector *args, struct context *context)
{
    if (args->size == 1) {
        puts("Drop what?");
        return 0;
    }

    struct item *item = inventory_remove(&context->player.inventory, vector_get(args, 1));
    if (item == NULL) {
        puts("You don't have that in your inventory...");
        return 0;
    }

    struct location *location = context->map[context->player.position.x][context->player.position.y];
    if (location == NULL || (location != NULL && location->inventory.size + item->weight > location->inventory.capacity)) {
        puts("You can't drop anything here...");
        // Put it back
        inventory_add(&context->player.inventory, item);
        return 0;
    }

    inventory_add(&location->inventory, item);
    return 0;
}

int map_handler_move(struct vector *args, struct context *context)
{
    if (context->player.in_combat == true) {
        puts("You cannot move while in combat");
        return 0;
    }

    char *direction;

    if (args->size > 1) {
        direction = vector_get(args, 1);
    }
    else {
        direction = "forward";
    }

    if (strncasecmp(direction, "forward", strlen("forward")) == 0) {
        move_player(context, 0, 1);
    }
    else if (strncasecmp(direction, "backward", strlen("backward")) == 0) {
        move_player(context, 0, -1);
    }
    else if (strncasecmp(direction, "left", strlen("left")) == 0) {
        move_player(context, -1, 0);
    }
    else if (strncasecmp(direction, "right", strlen("right")) == 0) {
        move_player(context, 1, 0);
    }

    return 0;
}

int map_handler_where(struct vector *args, struct context *context)
{
    struct location *location = context->map[context->player.position.x][context->player.position.y];

    if (location->area != NULL) {
        printf("You are in %s\n", location->area->description);
    }
    else {
        puts("You are outside.");
    }

    return 0;
}

int map_handler_look(struct vector *args, struct context *context)
{
    struct location *location = context->map[context->player.position.x][context->player.position.y];

    if (location != NULL) {
        if (location->inventory.size > 0) {
            puts("You see something in the darkness...");
            inventory_contents_print(&location->inventory);
        }
        if (location->people.size > 0) {
            puts("There is someone here...");
            for (int i = 0; i < location->people.size; i++) {
                struct person *p = vector_get(&location->people, i);
                printf("%s\n", p->name);
            }
        }
        else {
            puts("There is no one here...");
        }
    }
    return 0;
}

int player_handler_attack(struct vector *args, struct context *context)
{
    if (args->size == 1) {
        puts("Attack who?");
        return 0;
    }

    struct location *location = context->map[context->player.position.x][context->player.position.y];
    if (location == NULL) {
        puts("There is no one here...");
        return 0;
    }

    struct person *person = NULL;

    for (int i = 0; i < location->people.size; i++) {
        struct person *p = vector_get(&location->people, i);
        if (strncasecmp(p->name, vector_get(args, 1), strlen(p->name)) == 0) {
            person = p;
            break;
        }
    }

    if (person == NULL) {
        puts("There's no one here with that name...");
        return 0;
    }

    struct item *weapon = context->player.weapon;

    if (weapon == NULL) {
        puts("You do not have a weapon equipped...");
        return 0;
    }
    if (weapon->type != WEAPON) {
        printf("You can't attack someone with a %s...\n", weapon->description);
        return 0;
    }

    if (person->health <= 0) {
        printf("%s is already dead...\n", person->name);
        return 0;
    }

    context->player.in_combat = true;
    person->health -= weapon->damage;
    if (person->health <= 0) {
        printf("You have killed %s\n", person->name);
        context->player.in_combat = false;
    }
    else {
        printf("You attack %s with your %s causing %d damage\n", person->name, weapon->description, weapon->damage);
        printf("%s's health is now %d\n", person->name, person->health);

        // Enemy responds
        if (person->weapon != NULL) {
            context->player.health -= person->weapon->damage;
            printf("%s counter-attacks with their %s causing %d damage\n", person->name, person->weapon->description, person->weapon->damage);

            if (context->player.health <= 0) {
                puts("You died");
                return 1;
            }
            printf("Your health is now %d\n", context->player.health);
        }
    }
    return 0;
}

int player_handler_equip(struct vector *args, struct context *context)
{
    struct item *item = inventory_get(&context->player.inventory, vector_get(args, 1));
    context->player.weapon = item;
    return 0;
}

static void move_player(struct context *context, int x, int y)
{
    int px = context->player.position.x;
    int py = context->player.position.y;

    if (px + x > 10 ||
        px + x < 0  ||
        py + y > 10 ||
        py + y < 0)
    {
        puts("This is uncharted land, you step back into safety");
        return;
    }

    struct location *current  = context->map[px][py];
    struct location *new = context->map[px + x][py + y];

    if (current->area != NULL && new->area != current->area && !current->exit) {
        puts("You can't walk through walls...");
        return;
    }

    context->player.position.x += x;
    context->player.position.y += y;
}
