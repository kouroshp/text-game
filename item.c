#include <stdlib.h>
#include "item.h"

void item_free(struct item* item) {
    free(item->name);
}
