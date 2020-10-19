//insert the Headername here
#ifndef ECS_H
#define ECS_H
#include <vector>
#include <map>
#include "scene/2d/node_2d.h"
#include "scene/2d/sprite.h"
#include "core/array.h"
#include "core/color.h"
#include "core/os/keyboard.h"
#include "core/os/input_event.h"
#include "core/os/input.h"

class SubdivisionNode : public Node2D
{
	//The GoDot class
	GDCLASS(SubdivisionNode, Node2D);

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
