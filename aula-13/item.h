
#ifndef ITEM_H
#define ITEM_H


typedef struct {
    char nome[16];
    int id;
} Item;

typedef enum {
    MENOR=0,
    IGUAL,
    MAIOR
} COMP;


void ItemPrint(Item item);
COMP ItemCompara(Item i1, Item i2);


void ItemPrint(Item item);


#endif // !ITEM_H