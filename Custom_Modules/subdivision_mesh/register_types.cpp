#include "register_types.h"
#include "core/class_db.h"
#include "Subdivision.h"

void register_subdivision_mesh_types(){
	ClassDB::register_class<SubdivisionNode>();
}

void unregister_subdivision_mesh_types() {
}
