//insert the Headername here
#ifndef SUBDIVISION_H
#define SUBDIVISION_H

//#include "scene/2d/node_2d.h"
#include "scene/2d/mesh_instance_2d.h"
#include "scene/resources/mesh.h"
#include "core/math/triangle_mesh.h"
#include "core/os/keyboard.h"
#include "core/os/input.h"

#include <sstream>
#include <vector>

////https://www.flipcode.com/archives/The_Half-Edge_Data_Structure.shtml
//struct Vertex
//{
//	Vector3 mPosition = Vector3(0, 0, 0);	//Position
//	HalfEdge* mpHalfEdge;					//Half-edge it points to
//};
//
////https://www.flipcode.com/archives/The_Half-Edge_Data_Structure.shtml
//struct HalfEdge
//{
//	Vertex* mpVertex;						//Vertex
//	HalfEdge* mpHalfEdgePair;				//Pair half-edge
//	Face* mpFace;							//Face
//	HalfEdge* mpHalfEdgeNext;				//Next half-edge
//};
//
////https://www.flipcode.com/archives/The_Half-Edge_Data_Structure.shtml
//struct Face
//{
//	HalfEdge* mpHalfEdge;					//One of the half-edges
//};

class SubdivisionNode : public MeshInstance2D
{
	//The GoDot class
	GDCLASS(SubdivisionNode, MeshInstance2D);

	//Data
	int mNumOfSubdivisions;
	int mNumOfTriangles;
	bool mbShouldRecalculate;
	bool mbShouldRedraw;

	//Original values
	PoolVector2Array mOriginalVertices;
	PoolColorArray mOriginalColours;

	//Updated values
	PoolVector2Array mNewVertices;
	PoolColorArray mNewColours;

	//Methods
	//void readInObjFile(std::ifstream& objFileName);
	//void convertToHalfEdgeMesh();
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
