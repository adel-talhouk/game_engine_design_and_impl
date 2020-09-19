//insert the Headername here
#ifndef MOUSEIMAGENODE_H
#define MOUSEIMAGENODE_H

#include "core/reference.h"
#include "scene/2d/sprite.h"

//class Texture;

class MouseImageNode : public Sprite 
{
	GDCLASS(MouseImageNode, Node2D);

    //Stats
    Point2 mMousePos;
    Size2 mTextureSize;
    Rect2 mTextureRect;
    //Ref<Texture> mTexture;

    //void drawMouseImage();
    void updateMousePosition();

protected:
    static void _bind_methods();

public:
    MouseImageNode();

    Point2 getMousePos() { return mMousePos; };

    //Methods
    void setTexture(const Ref<Texture> &theTexture);
    void _notification(int p_notification);
};

#endif
