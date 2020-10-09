#include "register_types.h"
#include "core/class_db.h"
#include "ECS.h"

void register_ecs_arch_types(){
	ClassDB::register_class<PlayerNode>();
	ClassDB::register_class<EnemyNode>();
}

void unregister_ecs_arch_types() {
}
