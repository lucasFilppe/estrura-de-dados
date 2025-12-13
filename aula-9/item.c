
#include "item.h"

#include <stdio.h>

void ItemPrint(Item item) {
    printf("(%s|%d)", item.nome, item.id);
}