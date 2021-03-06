#include "mouseImageNode.h"
#include "core/core_string_names.h"

MouseImageNode::MouseImageNode(){}

//Bind all your methods used in this class
void MouseImageNode::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("setTexture", "theTexture"), &MouseImageNode::setTexture);
    ADD_SIGNAL(MethodInfo("texture_changed"));
}

//Set the image
void MouseImageNode::setTexture(const Ref<Texture> &theTexture)
{
    //In Sprite
    set_texture(theTexture);
    update();
}

void MouseImageNode::updateMousePosition()
{
    //mMousePos = get_global_mouse_position();
    mMousePos = get_local_mouse_position();

    //In sprite
    set_offset(mMousePos);
}

void MouseImageNode::_notification(int p_notification)
{
    switch (p_notification)
    {
    case NOTIFICATION_PROCESS:
    {
        //Update mouse position
        updateMousePosition();
    }
    break;

    case NOTIFICATION_DRAW:
    {
        //Get the sprite to draw
        Sprite::_notification(NOTIFICATION_DRAW);
    }
    break;

    }
}