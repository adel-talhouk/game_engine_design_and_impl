#include "Subdivision.h"
#include "scene/2d/sprite.h"
#include <core/engine.h>

#include <iostream>
#include <ctime>

//----------------------------------------------------------------------- GoDot class

SubdivisionNode::SubdivisionNode()
{
	//Make it process automatically
	set_process(true);

	//Seed rand
	srand(time(0));
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

		}

		//S Key
		if (Input::get_singleton()->is_key_pressed(KEY_S))
		{

		}
	}
}

void SubdivisionNode::_draw()
{
	//Do not let it run in the editor
	if (!Engine::get_singleton()->is_editor_hint())
	{

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