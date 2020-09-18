//insert the Headername here
#ifndef MOUSEIMAGENODE_H
#define MOUSEIMAGENODE_H

#include "scene/2d/sprite.h"
#include "core/reference.h"

class Texture;

class MouseImageNode : public Node2D 
{
	GDCLASS(MouseImageNode, Node2D);

    //Stats
    Point2 mMousePos = Point2(300, 300);
    Sprite mSprite;

    void drawMouseImage();

protected:
    static void _bind_methods();

public:
    MouseImageNode();

    Point2 getMousePos() { return mMousePos; };

    //Methods
    void setTexture(const Ref<Texture> &theTexture);
    //void updateMousePosition(Point2 pos);

    //Overloads
    //void drawMouseImage();
    void _process(/*float delta*/);
    void _notification(int p_notification);
};

#endif
