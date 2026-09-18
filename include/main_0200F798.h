#ifndef PMDSKY_MAIN_0200F798_H
#define PMDSKY_MAIN_0200F798_H

#include "item.h"

struct item *GetFirstUnequippedItemOfType(s16 type);
u32 RemoveItemNoHoleCheck(struct item *item);

u32 RemoveFirstUnequippedItemOfType(s16 type);
void RemoveAllItems(void);
void RemoveAllItemsStartingAt(s32 _index);
void SpecialProcAddItemToBag(struct bulk_item *bulkItem);
bool8 AddItemToBagNoHeld(struct item *item);
bool8 AddItemToBag(struct item* item, bool8 held_by);
void CleanStickyItemsInBag(void);
s16 CountStickyItemsInBag(void);
void sub_0200F9B4(u8 *arg0);

#endif
