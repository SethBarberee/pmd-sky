#include "type_effectiveness.h"
#include "dungeon_util_static.h"
#include "overlay_29_0230A994.h"
#include "overlay_29_02318A4C.h"
#include "overlay_29_0233836C.h"
#include "type_matchup_table.h"
#include "dungeon.h"
#include "dungeon_pokemon_attributes.h"
#include "dungeon_util_static.h"
#include "item.h"
#include "overlay_29_0230A994.h"

extern struct dungeon *DUNGEON_PTR[];


bool8 ScrappyShouldActivate(struct entity *attacker, struct entity *defender, enum type_id attack_type)
{
    for (s16 i = 0; i < 2; i++)
    {
        bool8 scrappy_should_activate;
        struct monster *defender_monster = GetEntInfo(defender);
        if (AbilityIsActiveVeneer(attacker, ABILITY_SCRAPPY) &&
            defender_monster->types[i] == TYPE_GHOST &&
            (attack_type == TYPE_NORMAL || attack_type == TYPE_FIGHTING))
            scrappy_should_activate = TRUE;
        else
            scrappy_should_activate = FALSE;

        if (scrappy_should_activate)
        {
            DUNGEON_PTR[0]->last_damage_calc.scrappy_activated = TRUE;
            return TRUE;
        }
    }
    return FALSE;
}

bool8 IsTypeIneffectiveAgainstGhost(s32 type)
{
    if ((type == TYPE_NORMAL) || (type == TYPE_FIGHTING)) {
        return TRUE;
    }
    return FALSE;
}

bool8 GhostImmunityIsActive(struct entity *pokemon, struct entity* target, s32 index)
{
    bool32 flag;
    struct monster* info;

    info = target->info;
    if (info->types[index] == TYPE_GHOST) {
        if ((info->exposed) || (ExclusiveItemEffectIsActive__0230A9B8(pokemon, EXCLUSIVE_EFF_SCRAPPY))) {
            flag = TRUE;
        } else {
            flag = FALSE;
        }
        if (!flag) {
            return TRUE;
        }
    }
    return FALSE;
}


s16 GetTypeMatchup(struct entity *attacker, struct entity *defender, s16 target_type_idx, enum type_id attack_type)
{
    struct monster *defender_monster = GetEntInfo(defender);
    if ((defender_monster->miracle_eye == 1 || ExclusiveItemEffectIsActive__0230A9B8(attacker, EXCLUSIVE_EFF_MIRACLE_EYE)) && attack_type == TYPE_PSYCHIC && defender_monster->types[target_type_idx] == TYPE_DARK)
        return MATCHUP_NEUTRAL;

    if (attack_type == TYPE_GROUND)
    {
        if (GravityIsActive())
        {
            if (defender_monster->types[target_type_idx] == TYPE_FLYING)
                return MATCHUP_NEUTRAL;
        }
        else if (IsFloating(defender))
            return MATCHUP_IMMUNE;
    }

    return TYPE_MATCHUP_TABLE.matchups[attack_type][defender_monster->types[target_type_idx]];
}
