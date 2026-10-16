#include "overlay_29_023293E4.h"
#include "main_0201514C.h"
#include "moves_2.h"
#include "overlay_29_022E563C.h"
#include "overlay_29_022E9FC0.h"
#include "overlay_29_023047B8.h"
#include "overlay_29_0230BBAC.h"
#include "overlay_29_02315118.h"
#include "overlay_29_02318A4C.h"

void WaitUntilFadeIsFinished(s32); 
void WaitUntilMonsterFliesOffscreen(struct entity*);
void WaitUntilMonsterIsBackOnGround(struct entity*);
void StartFadeDungeonWrapper(s32, s32, s32);
extern s16 GetDamageSourceWrapper(struct move *move, enum item_id item_id);
void ov29_022ECAFC(s32);

static inline struct monster *GetEntInfo(struct entity *ent)
{
    return ent->info;
}

bool8 DoMoveSeismicToss(struct entity* attacker, struct entity* defender, struct move* move, enum item_id item_id)
{
    bool8 sp1C;
    u32 level;
    struct monster* monster;

    sp1C = FALSE;
    monster = GetEntInfo(defender);
    level = GetEntInfo(attacker)->level;
    if (ShouldDisplayEntityAdvanced(defender)) {
        ChangeMonsterAnimation(defender, 0xC, monster->action.direction % NUM_DIRECTIONS);
        SetTwoTurnInvincibility(defender, 1);
        PlaySeByIdIfShouldDisplayEntity(defender, 0x221);
        WaitUntilMonsterFliesOffscreen(defender);
        ov29_022EA370(0x10, 0x67);
        SetTwoTurnInvincibility(defender, 0);
        ChangeMonsterAnimation(defender, 0xC, monster->action.direction % NUM_DIRECTIONS);
        WaitUntilMonsterIsBackOnGround(defender);
        PlaySeByIdIfShouldDisplayEntity(defender, 0x210);
        StartFadeDungeonWrapper(5, 0x2000, 0);
        WaitUntilFadeIsFinished(0);
        StartFadeDungeonWrapper(4, 0x400, 0);
        ov29_022ECAFC(1);
        WaitUntilFadeIsFinished(0);
    }

    CalcDamageFixedWrapper(attacker, defender, level, 1, &sp1C, GetMoveType(move), GetMoveCategory(move->id), GetDamageSourceWrapper(move, item_id), 0, 1, 0);
    sp1C = sp1C == 0;
    return sp1C;
}

bool8 DoMoveConfuse(struct entity* attacker, struct entity* defender, struct move* move, enum item_id item_id)
{
    TryInflictConfusedStatus(attacker, defender, TRUE, FALSE);

    return TRUE;
}

extern void TryInflictTauntStatus(struct entity *user, struct entity *target, bool8 onlyCheck);

bool8 DoMoveTaunt(struct entity* attacker, struct entity* defender, struct move* move, enum item_id item_id)
{
    TryInflictTauntStatus(attacker, defender, FALSE);

    return TRUE;
}
