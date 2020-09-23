//insert the Headername here
#ifndef MOUSEIMAGENODE_H
#define MOUSEIMAGENODE_H

#include "core/reference.h"
#include "scene/2d/sprite.h"

//class Texture;

class MouseImageNode : public Sprite 
{
	GDCLASS(MouseImageNode, Node2D);

    //Mouse position
    Point2 mMousePos;

    //Method(s)
    void updateMousePosition();

protected:
    static void _bind_methods();

public:

    //Constructor(s)
    MouseImageNode();

    //Methods
    void setTexture(const Ref<Texture> &theTexture);
    void _notification(int p_notification);
};

#endif
