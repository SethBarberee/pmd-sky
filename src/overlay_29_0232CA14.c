#include "overlay_29_0232CA14.h"
#include "dg_camera.h"
#include "dungeon_logic_7.h"
#include "dungeon_util_2.h"
#include "move_orb_effects.h"
#include "overlay_29_022E0A04.h"
#include "overlay_29_0234B340.h"
#include "overlay_29_0234BA54.h"

extern void TryInflictPetrifiedStatus(struct entity *user, struct entity *target);
extern void TryPounce(struct entity *user, struct entity *target, s32);
extern void TryTrawl(struct entity *user, struct entity *target);
extern void TryDrought(struct entity *user, struct entity *target);

extern struct dungeon* DUNGEON_PTR;

bool8 DoMoveSlowDown(struct entity* attacker, struct entity* defender, struct move* move, enum item_id item_id)
{
    LowerSpeed(attacker, defender, 1, TRUE);

    return TRUE;
}

bool8 DoMoveSearchlight(struct entity* attacker, struct entity* defender, struct move* move, enum item_id item_id)
{
    RevealWholeFloor(attacker, defender);

    return TRUE;
}

bool8 DoMovePetrify(struct entity* attacker, struct entity* defender, struct move* move, enum item_id item_id)
{
    TryInflictPetrifiedStatus(attacker, defender);

    return TRUE;
}

bool8 DoMovePounce(struct entity* attacker, struct entity* defender, struct move* move, enum item_id item_id)
{
    TryPounce(attacker, defender, 8);

    return TRUE;
}

bool8 DoMoveTrawl(struct entity* attacker, struct entity* defender, struct move* move, enum item_id item_id)
{
    TryTrawl(attacker, defender);

    return TRUE;
}

bool8 DoMoveEscape(struct entity *attacker, struct entity *defender, struct move* move, enum item_id item_id)
{
    s32 var_r0;

    SubstitutePlaceholderStringTags(0, attacker, 0);
    if (DUNGEON_PTR->thief_alert) {
#ifdef JAPAN
        LogMessageByIdWithPopupCheckUserTarget(attacker, defender, 0xC46);
#else
        LogMessageByIdWithPopupCheckUserTarget(attacker, defender, 0xF04);
#endif
    } else {
        if (!IsSecretBazaarNpc(attacker)) {
            var_r0 = TRUE;
        } else {
            var_r0 = FALSE;
        }
        if (var_r0 & 0xFF) {
#ifdef JAPAN
        LogMessageByIdWithPopupCheckUserTarget(attacker, defender, 0xC45);
#else
        LogMessageByIdWithPopupCheckUserTarget(attacker, defender, 0xF03);
#endif

            WaitUntilAlertBoxPauseIsOver(0xA);
        }
        SetDungeonEscapeFields(1, 1);
    }
    return FALSE;
}

bool8 DoMoveDrought(struct entity* attacker, struct entity* defender, struct move* move, enum item_id item_id)
{
    TryDrought(attacker, defender);

    return TRUE;
}

