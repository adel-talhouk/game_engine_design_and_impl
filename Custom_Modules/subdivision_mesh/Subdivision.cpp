#include "Subdivision.h"
#include <core/engine.h>

#include <iostream>
#include <ctime>

//----------------------------------------------------------------------- GoDot class

SubdivisionNode::SubdivisionNode()
{
	//Make it process automatically
	set_process(true);
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
		//Get the mesh


		//Set the original values

	}
}

void SubdivisionNode::_update()
{
	//Start the game	(make sure this does not happen in the editor)
	if (!Engine::get_singleton()->is_editor_hint())
	{
		//W Key
		if (Input::get_singleton()->is_key_pressed(KEY_W))
		{
			//Update the number of subdivisions


			//If the number of subdivisions is greater than 1


				//Convert the mesh into a alf-edge mesh


				//Subdivide the new mesh


				//Set the new values


				//Redraw it

		}

		//S Key
		if (Input::get_singleton()->is_key_pressed(KEY_S))
		{
			//Update the number of subdivisions


			//How do I undo a subdivision?

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