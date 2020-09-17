#include "mouseImageNode.h"

MouseImageNode::MouseImageNode(){}

//Bind all your methods used in this class
void MouseImageNode::_bind_methods(){
    //ClassDB::bind_method(D_METHOD("setImage", "theSprite"), &MouseImageNode::setImage);
    ClassDB::bind_method(D_METHOD("updateMousePosition"), &MouseImageNode::updateMousePosition);
    ClassDB::bind_method(D_METHOD("_draw"), &MouseImageNode::_draw);
    ClassDB::bind_method(D_METHOD("_process", "delta"), &MouseImageNode::_process);
}

//Set the image
void MouseImageNode::setImage(Sprite theSprite)
{

}

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
    //std::cout << "Test\n";

    //Update the mouse position


    //Draw the sprite

}