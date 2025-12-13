#ifndef ITEM_H
#define ITEM_H


typedef struct {
    char nome[16];
    int id;
} Item;


void ItemPrint(Item item);


#endif // !ITEM_H
