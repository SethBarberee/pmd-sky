#include "overlay_29_023296F8.h"
#include "dungeon_logic_5.h"
#include "enums.h"
#include "move_orb_effects.h"
#include "moves_2.h"
#include "overlay_29_02320764.h"
#include "special_move_types.h"

extern const struct StatIndex ATK_STAT_IDX;

extern const struct StatIndex SPATK_STAT_IDX;

extern s32 DealDamage(struct entity *attacker, struct entity *defender, struct move *move, s32 damageMultiplier, enum item_id item_id);

extern bool8 DungeonRandOutcomeUserTargetInteraction(struct entity *user, struct entity *target, s16 chance);

#ifdef JAPAN
extern bool8 DefenderAbilityIsActiveMoveEffects__02328634(struct entity *attacker, struct entity *defender, enum ability_id ability_id);
#else
extern bool8 DefenderAbilityIsActiveMoveEffects__02328634(struct entity *attacker, struct entity *defender, enum ability_id ability_id, bool8 attacker_ability_enabled);
#endif


extern const s16 THUNDERSHOCK_PARALYZE_CHANCE;


bool8 DoMoveBoostDefense2(struct entity* attacker, struct entity* defender, struct move* move, enum item_id item_id)
{
    BoostDefensiveStat(attacker, defender, ATK_STAT_IDX, 2);

    return TRUE;
}


bool8 DoMoveWarp(struct entity* attacker, struct entity* defender, struct move* move, enum item_id item_id)
{
    TryWarp(attacker, defender, 0, 0);

    return TRUE;
}

bool8 DoMoveThundershock(struct entity* attacker, struct entity* defender, struct move* move, enum item_id item_id)
{
    bool8 result = FALSE;

    if (DealDamage(attacker, defender, move, 0x100, item_id) != 0) {
        result = TRUE;
        if (DungeonRandOutcomeUserTargetInteraction(attacker, defender, THUNDERSHOCK_PARALYZE_CHANCE)) {
            TryInflictParalysisStatus(attacker, defender, FALSE, FALSE);
        }
    }

    return result;
}

bool8 DoMoveThunderWave(struct entity* attacker, struct entity* defender, struct move* move, enum item_id item_id)
{
    enum type_id move_type;

    move_type = GetMoveTypeForMonster(attacker, move);
#ifdef JAPAN
     if ((move_type == GetMoveType(move)) && (DefenderAbilityIsActiveMoveEffects__02328634(attacker, defender, ABILITY_MOTOR_DRIVE) != 0)) {
#else
    if ((move_type == GetMoveType(move)) && (DefenderAbilityIsActiveMoveEffects__02328634(attacker, defender, ABILITY_MOTOR_DRIVE, 1) != 0)) {
#endif
        
        ActivateMotorDrive(defender);
        return TRUE;
    }
    TryInflictParalysisStatus(attacker, defender, 1, 0);
    return TRUE;
}

bool8 DoMoveZapCannon(struct entity* attacker, struct entity* defender, struct move* move, enum item_id item_id)
{
    bool8 result = FALSE;

    if (DealDamage(attacker, defender, move, 0x100, item_id) != 0) {
        result = TRUE;
        if (DungeonRandOutcomeUserTargetInteraction(attacker, defender, 0)) {
            TryInflictParalysisStatus(attacker, defender, FALSE, FALSE);
        }
    }

    return result;
}
