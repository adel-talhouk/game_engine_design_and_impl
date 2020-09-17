//insert the Headername here
#ifndef MOUSEIMAGENODE_H
#define MOUSEIMAGENODE_H

#include "scene/2d/sprite.h"

class MouseImageNode : public Node2D 
{
	GDCLASS(MouseImageNode, Node2D);

protected:
    static void _bind_methods();

public:
    MouseImageNode();

    //Methods
    void updateMousePosition();
    void setImage(Sprite theSprite);

};

#endif
