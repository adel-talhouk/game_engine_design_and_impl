//insert the Headername here
#ifndef MOUSEIMAGENODE_H
#define MOUSEIMAGENODE_H

#include "scene/2d/sprite.h"

class MouseImageNode : public Node2D 
{
	GDCLASS(MouseImageNode, Node2D);

    //Stats
    Point2 mMousePos;
    Sprite mSprite;

protected:
    static void _bind_methods();

public:
    MouseImageNode();

    //Methods
    void setImage(Sprite theSprite);
    void updateMousePosition();
    void _draw();

    //Overloads
    void _process(float delta);
};

#endif
