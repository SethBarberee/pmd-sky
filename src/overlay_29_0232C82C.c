#include "overlay_29_0232C82C.h"
#include "dg_random.h"
#include "main_0201514C.h"
#include "overlay_29_0230BBAC.h"

extern void RevealEnemies(struct entity *user, struct entity *target);

extern void RevealItems(struct entity *user, struct entity *target);
extern void TryInflictMuzzledStatus(struct entity *user, struct entity *target, bool8 onlyCheck);
extern void TryInflictSleepStatus(struct entity *user, struct entity *target, s32 duration, bool8 onlyCheck);
extern s16 GetDamageSourceWrapper(struct move *move, enum item_id item_id);

extern const s16 SLEEP_TURN_RANGE[];

static inline struct monster *GetEntInfo(struct entity *ent)
{
    return ent->info;
}

bool8 DoMoveSiesta(struct entity *attacker, struct entity *defender, struct  move* move, enum item_id item_id)
{
    TryInflictSleepStatus(attacker, defender, CalcStatusDuration(defender, SLEEP_TURN_RANGE, TRUE), TRUE);

    return TRUE;
}

bool8 DoMoveTwoEdge(struct entity* attacker, struct entity* defender, struct  move* move, enum item_id item_id)
{
    u8 flag1;
    u8 flag2;
    s32 targetHP;
    s32 attackerHP;
    s32 flag3;
    struct monster* monster;

    flag1 = 0;
    flag2 = 0;
    monster = GetEntInfo(attacker);
    targetHP = GetEntInfo(defender)->hp - 1;
    if (targetHP < 0) {
        targetHP = 0;
    }
    CalcDamageFixedWrapper(attacker, defender, targetHP, 0, &flag1, TYPE_NONE,  GetMoveCategory(move->id), GetDamageSourceWrapper(move, item_id), 0, 0, 0);
    attackerHP = monster->hp / 2;
    if (attackerHP < 0) {
        attackerHP = 0;
    }
    CalcDamageFixedWrapper(attacker, attacker, attackerHP, 0, &flag2, TYPE_NONE, GetMoveCategory(move->id), GetDamageSourceWrapper(move, item_id), 0, 0, 0);
    
    flag1 = (flag1 == 0);
    flag2 = (flag2 == 0);
    
    if ((flag1 != 0) || (flag2 != 0)) {
        flag3 = TRUE;
    } else {
        flag3 = FALSE;
    }
    return flag3;
}

bool8 DoMoveNoMove(struct entity* attacker, struct entity* defender, struct move* move, enum item_id item_id)
{
    TryInflictMuzzledStatus(attacker, defender, FALSE);

    return TRUE;
}

bool8 DoMoveScan(struct entity* attacker, struct entity* defender, struct move* move, enum item_id item_id)
{
    RevealItems(attacker, defender);

    return TRUE;
}

bool8 DoMovePowerEars(struct entity* attacker, struct entity* defender, struct move* move, enum item_id item_id)
{
    RevealEnemies(attacker, defender);

    return TRUE;
}
