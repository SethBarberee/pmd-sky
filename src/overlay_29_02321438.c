#include "overlay_29_02321438.h"

bool EntityIsValid__02321438(struct entity *entity)
{
    if (entity == NULL)
    {
        return FALSE;
    }
    return entity->type != ENTITY_NOTHING;
}
