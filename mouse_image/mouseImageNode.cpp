#include "mouseImageNode.h"
#include "scene/resources/texture.h"
//#include "core/os/input.h"

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
//void MouseImageNode::setTexture(const Ref<Texture> &theTexture)
//{
//    mSprite.set_texture(theTexture);
//}

//Update the mouse position
void MouseImageNode::updateMousePosition()
{
    //For testing purposes
    mTestInt = 5;

    //Find the mouse position


    //Draw the sprite

}

//Draw the sprite
void MouseImageNode::_draw()
{
    mSprite.get_texture()->draw(mSprite.get_texture()->get_rid(), mMousePos);
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

        //Draw
        _draw();

        break;
    }
    //case NOTIFICATION_INPUT:
    //case NOTIFICATION_TRANSLATION_CHANGED:
    //case NOTIFICATION_WM_MOUSE_ENTER:
    //{
    //    //If the mouse moved
    //    if (Input::get_singleton()->get_mouse_mode() == Input::MOUSE_MODE_CAPTURED)
    //    {
    //        //Update mouse position
    //        updateMousePosition();
    //    }
    //    break;
    //}
    }
}