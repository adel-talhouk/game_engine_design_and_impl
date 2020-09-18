#include "mouseImageNode.h"
#include "scene/resources/texture.h"
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
    mTexture = theTexture;

    if (mTexture.is_valid())
        mTexture->disconnect(CoreStringNames::get_singleton()->changed, this, "_texture_changed");

    mTexture = theTexture;

    if (mTexture.is_valid())
        mTexture->connect(CoreStringNames::get_singleton()->changed, this, "_texture_changed");
}

//Draw the sprite
//void MouseImageNode::drawMouseImage()
//{
//    //mSprite.get_texture()->draw(mSprite.get_texture()->get_rid(), mMousePos);
//    //mTexture->draw(get_canvas_item(), mMousePos);
//}

//Overloaded _process function
void MouseImageNode::updateMousePosition()
{
    mMousePos = get_global_mouse_position();
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

        break;
    }
    }
}