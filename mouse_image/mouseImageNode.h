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

    //For testing purposes
    int mTestInt = 0;

protected:
    static void _bind_methods();

public:
    MouseImageNode();

    //For testing purposes
    int getTestInt();

    //Methods
    void setImage(Sprite theSprite);
    void updateMousePosition();
    void _draw();

    //Overloads
    void _process(float delta);
};

#endif
