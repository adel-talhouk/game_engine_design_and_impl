#include "register_types.h"
#include "core/class_db.h"
#include "Entity.h"

void register_ecs_arch_types(){
	ClassDB::register_class<Entity>();
}

void unregister_ecs_arch_types() {
}
