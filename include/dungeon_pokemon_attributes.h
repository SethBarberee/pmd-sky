#ifndef PMDSKY_DUNGEON_POKEMON_ATTRIBUTES_H
#define PMDSKY_DUNGEON_POKEMON_ATTRIBUTES_H

#include "dungeon_mode.h"

// Checks if a monster does not have the Gastro Acid status.
bool8 NoGastroAcidStatus(struct entity *entity, enum ability_id ability_id);
// Checks if a monster has a certain ability that isn't disabled by Gastro Acid.
bool8 AbilityIsActive(struct entity *entity, enum ability_id ability_id);

#endif //PMDSKY_DUNGEON_POKEMON_ATTRIBUTES_H
