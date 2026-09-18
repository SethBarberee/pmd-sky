#include "main_0200F798.h"
#include "item.h"
#include "item_util_4.h"
#include "main_0200D81C.h"
#include "main_0200EDC0.h"

extern struct bag_items* BAG_ITEMS_PTR_MIRROR;

struct flags_and_held_by
{
        // 0x0: flags: 1-byte bitfield
        u8 flags;
        // bool8 f_exists : 1;  // Validity flag
        // bool8 f_in_shop : 1; // In a Kecleon Shop
        // bool8 f_unpaid : 1;  // Picked up from a Kecleon Shop but not paid for yet
        // bool8 f_sticky : 1;  // Sticky
        // bool8 f_set : 1;     // Usable by L+R
        // bool8 flag_unk5 : 1;
        // // For stolen items to recover from outlaws (has red X)? Could be for other items for other
        // // types of missions? (Uncertain)
        // bool8 f_unk_mission_item1 : 1;
        // // For stolen items to recover from outlaws (has red X)? Could be for other items for other
        // // types of missions? (Uncertain) Definitely used temporarily when sorting the items in
        // // storage.
        // bool8 f_unk_mission_item2 : 1;
        // 0x1: For bag items. 0 for none, 1 if held by the leader, 2 for the second party member, etc.
        u8 held_by;
};

struct item_u16 {

    union flags_held_by
    {
        struct flags_and_held_by fhb;
        u16 flags_held_by_u16;
    } flag_held;
    
    // 0x2: Only for stackable items. Will be 0 if unapplicable. For Poké, this is an "amount code"
    // rather than the literal amount (see MONEY_QUANTITY_TABLE)
    u16 quantity;
    u16 id; // 0x4
};

void RemoveEmptyItems(struct item *, s32);
void sub_020582E0(void);
void SetItemAcquired(struct item*);

u32 RemoveFirstUnequippedItemOfType(s16 type)
{
    return RemoveItemNoHoleCheck(GetFirstUnequippedItemOfType(type));
}

void RemoveAllItems(void)
{
    struct item *item;
    s32 index;

    for(index = 0, item = &BAG_ITEMS_PTR_MIRROR->bag_items->bag_items[0]; index < INVENTORY_SIZE; index++, item++)
    {    
        ItemZInit(item);
    }
}

void RemoveAllItemsStartingAt(s32 _index)
{
    s32 index;
    struct item *item;

    for(index = _index, item = &BAG_ITEMS_PTR_MIRROR->bag_items->bag_items[index]; index < INVENTORY_SIZE; index++, item++)
    {
        if (item->held_by != 0) {
            sub_020582E0();
        }
        ItemZInit(&BAG_ITEMS_PTR_MIRROR->bag_items->bag_items[index]);
    }
    
    RemoveEmptyItems(BAG_ITEMS_PTR_MIRROR->bag_items->bag_items, INVENTORY_SIZE);
}

void SpecialProcAddItemToBag(struct bulk_item *bulkItem)
{
    struct item item;

    BulkItemToItem(&item, bulkItem);
    AddItemToBag(&item, 0);
}

bool8 AddItemToBagNoHeld(struct item *item)
{
    return AddItemToBag(item, FALSE);
}

bool8 AddItemToBag(struct item* item, bool8 held_by)
{
    s32 capacity;
    s32 index;
    s32 flag;

    struct item_u16* item_1 = (struct item_u16 *)item;
    struct item_u16* bag_item;

    bag_item = (struct item_u16 *)BAG_ITEMS_PTR_MIRROR->bag_items->bag_items;
    capacity = GetCurrentBagCapacity();
    
    for(index = 0; index < capacity; index++, bag_item++)
    {
        if (bag_item->flag_held.fhb.flags & ITEM_FLAG_EXISTS) {
            flag = TRUE;
        } else {
            flag = FALSE;
        }
        if (!(flag & 0xFF)) {
            bag_item->flag_held.flags_held_by_u16 = item_1->flag_held.flags_held_by_u16;
            bag_item->quantity = item_1->quantity;
            bag_item->id = item_1->id;
            bag_item->flag_held.fhb.held_by = held_by;
            SetItemAcquired((struct item *)item);
            return TRUE;
        }
    }
    return FALSE;
}

void CleanStickyItemsInBag(void)
{
    struct item* item;
    
    item = BAG_ITEMS_PTR_MIRROR->bag_items->bag_items;
    
    for(s32 index = 0; index < INVENTORY_SIZE; index++, item++)
    {
        item->flags &= ~ITEM_FLAG_STICKY;   
    }
}

s16 CountStickyItemsInBag(void) 
{
    s32 isSticky;
    s32 itemExists;
    u8 flags;
    struct item* item;

    s32 count = 0;
    item = BAG_ITEMS_PTR_MIRROR->bag_items->bag_items;
    for(s32 index = 0; index < INVENTORY_SIZE; index++, item++)
    {
        flags = item->flags;
        if (flags & ITEM_FLAG_EXISTS) {
            itemExists = TRUE;
        } else {
            itemExists = FALSE;
        }
        if (itemExists & 0xFF) {
            if (flags & ITEM_FLAG_STICKY) {
                isSticky = TRUE;
            } else {
                isSticky = FALSE;
            }
            if (isSticky & 0xFF) {
                count += 1;
            }
        }
    }
    return count;
}

void sub_0200F9B4(u8 *arg0)
{
    bool32 itemExists;
    bool8 heldBy;
    struct item* item;

    item = BAG_ITEMS_PTR_MIRROR->bag_items->bag_items;
    
    for(s32 index = 0; index < INVENTORY_SIZE; index++, item++)
    {
        if (item->flags & ITEM_FLAG_EXISTS) {
            itemExists = TRUE;
        } else {
            itemExists = FALSE;
        }
        if (itemExists & 0xFF) {
            heldBy = item->held_by;
            if (heldBy) {
                item->held_by = arg0[heldBy];
            }
        }
    }
}

void sub_0200FA0C(u8 *arg0, u32 arg1)
{
    bool32 itemExists;
    bool8 heldBy;
    struct item* item;

    item = BAG_ITEMS_PTR_MIRROR->inventories[arg1].bag_items;
    
    for(s32 index = 0; index < INVENTORY_SIZE; index++, item++)
    {
        if (item->flags & ITEM_FLAG_EXISTS)
        {
            itemExists = TRUE;
        } else {
            itemExists = FALSE;
        }
        if (itemExists & 0xFF) {
            heldBy = item->held_by;
            if (heldBy) {
                item->held_by = arg0[heldBy];
            }
        }
    }
}

bool8 TransmuteHeldItemInBag(struct item* held_item)
{
    bool32 itemExists;
    struct item_u16 *held_item_1 = (struct item_u16*) held_item;
    struct item_u16 *item = (struct item_u16 *) BAG_ITEMS_PTR_MIRROR->bag_items->bag_items;
    
    for(s32 index = 0; index < INVENTORY_SIZE; index++, item++)
    {
        if (item->flag_held.fhb.flags & ITEM_FLAG_EXISTS)
        {
            itemExists = TRUE;
        } else {
            itemExists = FALSE;
        }
        if ((itemExists & 0xFF) && (item->flag_held.fhb.held_by == held_item_1->flag_held.fhb.held_by)) {
            item->flag_held.flags_held_by_u16 = held_item_1->flag_held.flags_held_by_u16;
            item->quantity = held_item_1->quantity;
            item->id = held_item_1->id;
            return TRUE;
        }
    }
    return FALSE;
}

void SetFlagsForHeldItemInBag(bool8 isHeldItem, u8 _flags) {
    bool32 itemExists;
    struct item* item;

    if (!isHeldItem) return;

    item = BAG_ITEMS_PTR_MIRROR->bag_items->bag_items;
    
    for(s32 index = 0; index < INVENTORY_SIZE; index++, item++)
    {
        if (item->flags & ITEM_FLAG_EXISTS) 
        {
            itemExists = TRUE;
        } else {
            itemExists = FALSE;
        }
        if ((itemExists & 0xFF) && (item->held_by == isHeldItem)) {
            item->flags |= _flags;
        }
    }
}

bool8 RemoveHolderForItemInBag(struct item *item)
{
    bool32 itemExists;
    struct item* bag_item;

    bag_item = BAG_ITEMS_PTR_MIRROR->bag_items->bag_items;
    for(s32 index = 0; index < INVENTORY_SIZE; index++, bag_item++)
    {
        if (bag_item->flags & ITEM_FLAG_EXISTS) {
            itemExists = TRUE;
        } else {
            itemExists = FALSE;
        }
        if ((itemExists & 0xFF) && (AreItemsEquivalent(bag_item, item, 1))) {
            bag_item->held_by = FALSE;
            bag_item->flags = item->flags;
            return TRUE;
        }
    }
    return FALSE;
}
