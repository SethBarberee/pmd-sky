#include "overlay_29_02329534.h"
#include "dungeon_pokemon_attributes.h"
#include "dungeon_util_2.h"
#include "main_0201514C.h"
#include "move_orb_effects.h"
#include "moves_2.h"
#include "overlay_29_0230BBAC.h"
#include "overlay_29_0234B340.h"

extern const struct StatIndex ATK_STAT_IDX;

extern const struct StatIndex SPATK_STAT_IDX;

extern s16 GetDamageSourceWrapper(struct move *move, enum item_id item_id);

extern void TryIncreaseHp(struct entity *, struct entity *, s16, s32, bool8);

bool8 DoMoveHornDrill(struct entity* attacker, struct entity* defender, struct move* move, enum item_id item_id)
{
    u8 sp1C = 0;
    
    if ((ov29_0230D4A4(attacker, defender, GetMoveType(move), AbilityIsActiveVeneer(attacker, ABILITY_SCRAPPY))) == 0) {
#ifdef JAPAN
        LogMessageByIdWithPopupCheckUserTarget(attacker, defender, 0xC1B);
#else
        LogMessageByIdWithPopupCheckUserTarget(attacker, defender, 0xED9);
#endif
        return 0;
    }

    CalcDamageFixedWrapper(attacker, defender, 0x270F, 1, &sp1C, GetMoveType(move), GetMoveCategory(move->id), GetDamageSourceWrapper(move, item_id), 0, 0, 0);
    sp1C = sp1C == 0;
    SubstitutePlaceholderStringTags(0, defender, 0);
    return sp1C;
}

bool8 DoMoveSwordsDance(struct entity* attacker, struct entity* defender, struct move* move, enum item_id item_id)
{
    BoostOffensiveStat(attacker, defender, ATK_STAT_IDX, 2);

    return TRUE;
}
