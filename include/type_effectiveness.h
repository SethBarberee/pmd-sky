#ifndef PMDSKY_TYPE_EFFECTIVENESS_H
#define PMDSKY_TYPE_EFFECTIVENESS_H

#include "dungeon_mode.h"

// Checks whether Scrappy should activate.
// Scrappy activates when the ability is active on the attacker, the move type is Normal or Fighting, and the defender is a Ghost type.
bool8 ScrappyShouldActivate(struct entity *attacker, struct entity *defender, enum type_id attack_type);
bool8 IsTypeIneffectiveAgainstGhost(s32 type);
bool8 GhostImmunityIsActive(struct entity *pokemon, struct entity* target, s32 index);

s16 GetTypeMatchup(struct entity *attacker, struct entity *defender, s16 target_type_idx, enum type_id attack_type);

#endif //PMDSKY_TYPE_EFFECTIVENESS_H
