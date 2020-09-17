#include "mouseImageNode.h"

MouseImageNode::MouseImageNode(){}

//Bind all your methods used in this class
void MouseImageNode::_bind_methods(){
  ClassDB::bind_method(D_METHOD("updateMousePosition"), &MouseImageNode::updateMousePosition);
  //ClassDB::bind_method(D_METHOD("setImage", "theSprite"), &MouseImageNode::setImage);
  ClassDB::bind_method(D_METHOD("_draw"), &MouseImageNode::_draw);
  ClassDB::bind_method(D_METHOD("update"), &MouseImageNode::update);
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

void MouseImageNode::_draw()
{

}

void MouseImageNode::update()
{
    //Update the position


    //Draw

}