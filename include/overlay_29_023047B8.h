#ifndef PMDSKY_OVERLAY_29_023047B8_H
#define PMDSKY_OVERLAY_29_023047B8_H

#include "dungeon_mode.h"

// Checks if an entity pointer points to a valid entity (not entity type 0, which represents no entity).
// entity: entity pointer
// return: bool
bool8 EntityIsValid__023047B8(struct entity *entity);

#endif //PMDSKY_OVERLAY_29_023047B8_H
