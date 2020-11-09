#include "Subdivision.h"
#include <core/engine.h>

#include <iostream>
#include <fstream>

SubdivisionNode::SubdivisionNode()
{
	//Make it process automatically
	set_process(true);

	mNumOfSubdivisions = 0;
	mNumOfTriangles = 0;
	mbShouldRecalculate = false;
	mbShouldRedraw = true;

	//Create the original half-edge mesh
	he_mesh = new meshparse::mesh();
	std::ifstream infile;
	infile.open("roosterTri.obj");
	meshparse::load_obj(infile, *he_mesh);
}

SubdivisionNode::~SubdivisionNode()
{
	
}


void SubdivisionNode::_bind_methods()
{
	
}

void SubdivisionNode::_ready()
{
	//Do not let it run in the editor
	if (!Engine::get_singleton()->is_editor_hint())
	{
		//There are as many triangles as the half-edge mesh has faces
		mNumOfTriangles = he_mesh->faces.size();

		//Set the original vertices and colours
		for (std::vector<face*>::iterator it = he_mesh->faces.begin(); it != he_mesh->faces.end(); ++it)
		{
			Vector3 v0, v1, v2, v3;
			v0 = (*it)->e->vert->loc;
			mOriginalVertices.push_back(Vector2(v0.x, v0.y));
			v1 = (*it)->e->next->vert->loc;
			mOriginalVertices.push_back(Vector2(v1.x, v1.y));
			v2 = (*it)->e->next->next->vert->loc;
			mOriginalVertices.push_back(Vector2(v2.x, v2.y));
			v3 = (*it)->e->next->next->next->vert->loc;
			mOriginalVertices.push_back(Vector2(v3.x, v3.y));

			mOriginalColours.append(Color(1, 1, 1));
			mOriginalColours.append(Color(0, 1, 0));
			mOriginalColours.append(Color(0, 0, 1));
			mOriginalColours.append(Color(1, 0, 0));

		}

		//Copy the original values to the newVertices and newColours
		mNewVertices = mOriginalVertices;
		mNewColours = mOriginalColours;
	}
}

void SubdivisionNode::_update()
{
	//Start the game	(make sure this does not happen in the editor)
	if (!Engine::get_singleton()->is_editor_hint())
	{
		//1 subdivision
		if (Input::get_singleton()->is_key_pressed(KEY_1))
		{
			//The old number of subdivisions
			int oldNumOfSubdivisions = mNumOfSubdivisions;

			//If it's new
			if (mNumOfSubdivisions != oldNumOfSubdivisions)
			{
				//Update it
				mNumOfSubdivisions = 1;
				mbShouldRecalculate = true;
			}

		}

		//2 subdivisions
		if (Input::get_singleton()->is_key_pressed(KEY_2))
		{
			//The old number of subdivisions
			int oldNumOfSubdivisions = mNumOfSubdivisions;

			//If it's new
			if (mNumOfSubdivisions != oldNumOfSubdivisions)
			{
				//Update it
				mNumOfSubdivisions = 2;
				mbShouldRecalculate = true;
			}
		}

		//3 subdivisions
		if (Input::get_singleton()->is_key_pressed(KEY_3))
		{
			//The old number of subdivisions
			int oldNumOfSubdivisions = mNumOfSubdivisions;

			//If it's new
			if (mNumOfSubdivisions != oldNumOfSubdivisions)
			{
				//Update it
				mNumOfSubdivisions = 3;
				mbShouldRecalculate = true;
			}
		}

		//4 subdivisions
		if (Input::get_singleton()->is_key_pressed(KEY_4))
		{
			//The old number of subdivisions
			int oldNumOfSubdivisions = mNumOfSubdivisions;

			//If it's new
			if (mNumOfSubdivisions != oldNumOfSubdivisions)
			{
				//Update it
				mNumOfSubdivisions = 4;
				mbShouldRecalculate = true;
			}
		}

		//5 subdivisions
		if (Input::get_singleton()->is_key_pressed(KEY_5))
		{
			//The old number of subdivisions
			int oldNumOfSubdivisions = mNumOfSubdivisions;

			//If it's new
			if (mNumOfSubdivisions != oldNumOfSubdivisions)
			{
				//Update it
				mNumOfSubdivisions = 5;
				mbShouldRecalculate = true;
			}
		}

		//If it should recalculate
		if (mbShouldRecalculate)
		{
			//Subdivide the new half-edge mesh mNumOfsubdivisions times
			subdivideMesh(mNumOfSubdivisions);

			//Convert it back to a normal mesh
			revertMesh();

			//Redraw it
			mbShouldRedraw = true;

			//Do not recalculate
			mbShouldRecalculate = false;
		}
	}
}

void SubdivisionNode::_draw()
{
	//Do not let it run in the editor
	if (!Engine::get_singleton()->is_editor_hint())
	{
		//If it should redraw
		if (mbShouldRedraw)
		{
			//Draw here
			Ref<ArrayMesh> a = memnew(ArrayMesh);
			Array arrays;
			arrays.resize(ArrayMesh::ARRAY_MAX);

			arrays[ArrayMesh::ARRAY_VERTEX] = mNewVertices;
			arrays[ArrayMesh::ARRAY_COLOR] = mNewColours;

			//optionally u can add texture coordinates and attach a texture from the editor to this arraymesh in the scene

			a->add_surface_from_arrays(Mesh::PRIMITIVE_TRIANGLES, arrays);

			if (this != NULL)
				this->set_mesh(a);

			//Do not redraw
			mbShouldRedraw = false;
		}
	}
}

void SubdivisionNode::_notification(int p_what)
{
	switch (p_what) 
	{
	case NOTIFICATION_READY:
	{
		_ready();
		break;
	}
	case NOTIFICATION_PROCESS:
	{
		_update();
		update();
		break;
	}
	case NOTIFICATION_DRAW:
	{
		_draw();
		break;
	}

	}
}

//http://www.rorydriscoll.com/2008/08/01/catmull-clark-subdivision-the-basics/
void SubdivisionNode::subdivideMesh(int numOfSubdivisions)
{
	//The 4 vertices in each face
	vertex* vert0;
	vertex* vert1;
	vertex* vert2;
	vertex* vert3;

	//The 4 vertices in the face touching the half-edge's pair
	vertex* pairVert0;
	vertex* pairVert1;
	vertex* pairVert2;
	vertex* pairVert3;

	//Iterate through all the faces
	for (std::vector<face*>::iterator it = he_mesh->faces.begin(); it != he_mesh->faces.end(); ++it)
	{
		//The 4 vertices in this face 
		vert0 = (*it)->e->vert;
		vert1 = (*it)->e->next->vert;
		vert2 = (*it)->e->next->next->vert;
		vert3 = (*it)->e->next->next->next->vert;

		//The 4 vertices in the face touching the half-edge's pair
		pairVert0 = (*it)->e->pair->vert;
		pairVert1 = (*it)->e->pair->next->vert;
		pairVert2 = (*it)->e->pair->next->next->vert;
		pairVert3 = (*it)->e->pair->next->next->next->vert;

		//If any edge is a boundary-edge, skip it
		if (vert0->onboundary() || vert1->onboundary() || vert2->onboundary() || vert3->onboundary())
			continue;

		//1. Calculate face-point
		Vector3 facePointPos;
		facePointPos = (vert0->loc + vert1->loc + vert2->loc + vert3->loc) / 4;

		//2. Calculate edge-point
		Vector3 edgePoint;
		Vector3 controlPointsAveragePos = (vert0->loc + vert1->loc) / 2;
		Vector3 pairFacePointPos = (pairVert0->loc + pairVert1->loc + pairVert2->loc + pairVert3->loc) / 4;
		Vector3 touchingFacePointsAveragePos = (facePointPos + pairFacePointPos) / 2;
		edgePoint = (controlPointsAveragePos + touchingFacePointsAveragePos) / 2;

		//2.1 Make the new half-edges in the face


		//3. Move the control-point to the new position (vertex-point)
		Vector3 newVertPoint0;
		Vector3 newVertPoint1;

		//4. Connect the new points

	}
}

void SubdivisionNode::revertMesh()
{

}