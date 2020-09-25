//insert the Headername here
#ifndef ENTITY_H
#define ENTITY_H

#include "core/reference.h"

typedef Uint32 EntityID;
const UnitID INVALID_ENTITY_ID = UINT_MAX;

class Entity : public Node2D
{
	GDCLASS(Entity, Node2D);

	//ID
	EntityID mID;
};

#endif
