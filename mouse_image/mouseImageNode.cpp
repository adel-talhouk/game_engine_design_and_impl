#include "mouseImageNode.h"
#include "scene/resources/texture.h"

MouseImageNode::MouseImageNode(){}

//Bind all your methods used in this class
void MouseImageNode::_bind_methods(){
    ClassDB::bind_method(D_METHOD("setTexture", "theTexture"), &MouseImageNode::setTexture);
    ClassDB::bind_method(D_METHOD("updateMousePosition", "pos"), &MouseImageNode::updateMousePosition);
    //ClassDB::bind_method(D_METHOD("drawMouseImage"), &MouseImageNode::drawMouseImage);
    //ClassDB::bind_method(D_METHOD("_process", "delta"), &MouseImageNode::_process);
    ClassDB::bind_method(D_METHOD("getMousePos"), &MouseImageNode::getMousePos);
    ClassDB::bind_method(D_METHOD("_notification", "p_notification"), &MouseImageNode::_notification);
}

//Set the image
void MouseImageNode::setTexture(const Ref<Texture> &theTexture)
{
    mSprite.set_texture(theTexture);
}

//Update the mouse position
void MouseImageNode::updateMousePosition(Point2 pos)
{
    //Update the mouse position
    mMousePos = pos;
}

//Draw the sprite
void MouseImageNode::drawMouseImage()
{
    mSprite.get_texture()->draw(mSprite.get_texture()->get_rid(), mMousePos);
    //mSprite.get_texture()->draw(mSprite.get_canvas_item(), mMousePos);
}

//Overloaded _process function
//void MouseImageNode::_process(float delta)
//{
//    //Update the mouse position
//
//
//    //Draw the sprite
//
//}

void MouseImageNode::_notification(int p_notification)
{
    switch (p_notification)
    {
    case NOTIFICATION_PROCESS:
    {
        //Draw
        //drawMouseImage();

        break;
    }
    }
}