#include "mouseImageNode.h"
#include "core/core_string_names.h"

MouseImageNode::MouseImageNode(){}

//Bind all your methods used in this class
void MouseImageNode::_bind_methods(){
    ClassDB::bind_method(D_METHOD("setTexture", "theTexture"), &MouseImageNode::setTexture);
    ClassDB::bind_method(D_METHOD("getMousePos"), &MouseImageNode::getMousePos);
}

//Set the image
void MouseImageNode::setTexture(const Ref<Texture> &theTexture)
{
    //In Sprite
    set_texture(theTexture);    //Not working: "ERROR: Can't emit non-existing signal "texture_changed" at core\object.cpp:1195"
    //set_normal_map(theTexture);

    ////Set the size
    //mTextureSize = Size2(theTexture->get_size());
    //mTextureRect = Rect2(mMousePos, mTextureSize);
    //set_region_rect(mTextureRect);
}

//Overloaded _process function
void MouseImageNode::updateMousePosition()
{
    mMousePos = get_global_mouse_position();

    //In sprite
    //set_offset(mMousePos);
}

void MouseImageNode::_notification(int p_notification)
{
    switch (p_notification)
    {
        //Notification for the _process method
    case NOTIFICATION_PROCESS:
    {
        //Update mouse pos
        updateMousePosition();
    }
    break;

    }
}