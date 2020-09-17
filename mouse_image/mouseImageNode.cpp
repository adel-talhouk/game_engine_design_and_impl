#include "mouseImageNode.h"
#include "scene/resources/texture.h"

MouseImageNode::MouseImageNode(){}

//Bind all your methods used in this class
void MouseImageNode::_bind_methods(){
    //ClassDB::bind_method(D_METHOD("setTexture", "theTexture"), &MouseImageNode::setTexture);
    ClassDB::bind_method(D_METHOD("updateMousePosition"), &MouseImageNode::updateMousePosition);
    ClassDB::bind_method(D_METHOD("_draw"), &MouseImageNode::_draw);
    ClassDB::bind_method(D_METHOD("_process", "delta"), &MouseImageNode::_process);
    ClassDB::bind_method(D_METHOD("getTestInt"), &MouseImageNode::getTestInt);
    ClassDB::bind_method(D_METHOD("_notification", "p_notification"), &MouseImageNode::_notification);
}

int MouseImageNode::getTestInt()
{
    return mTestInt;
}

//Set the image
//void MouseImageNode::setTexture(Texture theTexture)
//{
//
//}

//Update the mouse position
void MouseImageNode::updateMousePosition()
{
    //Find the mouse position


    //Draw the sprite

}

//Draw the sprite
void MouseImageNode::_draw()
{

}

//Overloaded _process function
void MouseImageNode::_process(float delta)
{
    //For testing purposes
    //mTestInt+=1;

    //Update the mouse position


    //Draw the sprite

}

void MouseImageNode::_notification(int p_notification)
{
    switch (p_notification)
    {
    case NOTIFICATION_PROCESS:
    {
        //For testing purposes
        mTestInt++;

        break;
    }
    }
}