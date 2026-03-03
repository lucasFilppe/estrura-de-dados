#include "item.h"
#include <stdio.h>

void ItemPrint(Item item) {
    printf("(%s|%d) -> ", item.nome, item.id);
}                                                                                                      

COMP ItemCompara(Item i1, Item i2) {
    if (strcmp(i1.nome, i2.nome) < 0)
        return MENOR;
    else if (strcmp(i1.nome, i2.nome) > 0)
        return MAIOR;
    else {
        if (i1.id < i2.id)
            return MENOR;
        else if (i1.id > i2.id)
            return MAIOR;
    }
        return IGUAL;
}
