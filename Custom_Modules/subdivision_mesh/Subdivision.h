//insert the Headername here
#ifndef SUBDIVISION_H
#define SUBDIVISION_H

#include "scene/2d/node_2d.h"
#include "scene/2d/mesh_instance_2d.h"
//#include "scene/3d/mesh_instance.h"
#include "scene/resources/mesh.h"
#include "core/math/triangle_mesh.h"
#include "core/os/keyboard.h"
#include "core/os/input.h"

#include "he_mesh.h"
#include "objparse.h"

#include <sstream>
#include <vector>

using namespace meshparse;

class SubdivisionNode : public MeshInstance2D
{
	//The GoDot class
	GDCLASS(SubdivisionNode, MeshInstance2D);

	//Data
	int mNumOfSubdivisions;
	int mNumOfTriangles;
	bool mbShouldRecalculate;
	bool mbShouldRedraw;

	//Half-edge mesh
	meshparse::mesh* he_mesh;

	//Original values
	PoolVector2Array mOriginalVertices;
	PoolColorArray mOriginalColours;

	//Updated values
	PoolVector2Array mNewVertices;
	PoolColorArray mNewColours;

	//Methods
	void subdivideMesh(int numOfSubdivisions);
	void revertMesh();

protected:

	static void _bind_methods();

public:

	//Constructor(s) and Destructor
	SubdivisionNode();
	~SubdivisionNode();

	//Overridden methods
	void _ready();
	void _update();
	void _draw();
	void _notification(int p_what);
};


#endif
