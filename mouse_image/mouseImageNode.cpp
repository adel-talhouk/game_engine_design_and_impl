#include "mouseImageNode.h"

MouseImageNode::MouseImageNode(){}

//Bind all your methods used in this class
void MouseImageNode::_bind_methods(){
  ClassDB::bind_method(D_METHOD("updateMousePosition"), &MouseImageNode::updateMousePosition);
  //ClassDB::bind_method(D_METHOD("setImage", "theSprite"), &MouseImageNode::setImage);
}


//Custom Functions
void MouseImageNode::updateMousePosition()
{
    //Find the mouse position


    //Draw the sprite

}

void MouseImageNode::setImage(Sprite theSprite)
{

}