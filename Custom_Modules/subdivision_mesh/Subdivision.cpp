#include "Subdivision.h"
#include <core/engine.h>

#include <iostream>
#include <ctime>

//----------------------------------------------------------------------- GoDot class

SubdivisionNode::SubdivisionNode()
{
	//Make it process automatically
	set_process(true);

	mNumOfSubdivisions = 0;
	mbShouldRecalculate = false;
	mbShouldRedraw = true;
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
		//We have 2 triangles
		mNumOfTriangles = 2;

		//Original vertices
		mOriginalVertices.push_back(Vector2(0, 100));
		mOriginalVertices.push_back(Vector2(100, 0));
		mOriginalVertices.push_back(Vector2(0, 0));
		mOriginalVertices.push_back(Vector2(0, 100));
		mOriginalVertices.push_back(Vector2(100, 100));
		mOriginalVertices.push_back(Vector2(100, 0));

		//Original colours
		mOriginalColours.append(Color(1, 1, 1));
		mOriginalColours.append(Color(0, 1, 0));
		mOriginalColours.append(Color(0, 0, 1));
		mOriginalColours.append(Color(1, 0, 0));
		mOriginalColours.append(Color(0, 0, 0));
		mOriginalColours.append(Color(0, 1, 0));

		//New vertices (the same as the original by default)
		mNewVertices.push_back(Vector2(0, 100));
		mNewVertices.push_back(Vector2(100, 0));
		mNewVertices.push_back(Vector2(0, 0));
		mNewVertices.push_back(Vector2(0, 100));
		mNewVertices.push_back(Vector2(100, 100));
		mNewVertices.push_back(Vector2(100, 0));

		//New colours (the same as the original by default)
		mNewColours.append(Color(1, 1, 1));
		mNewColours.append(Color(0, 1, 0));
		mNewColours.append(Color(0, 0, 1));
		mNewColours.append(Color(1, 0, 0));
		mNewColours.append(Color(0, 0, 0));
		mNewColours.append(Color(0, 1, 0));
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
			//If the number of subdivisions is greater than 1


				//Convert the mesh into a half-edge mesh


				//Subdivide the new mesh


				//Set the new values


				//Redraw it

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