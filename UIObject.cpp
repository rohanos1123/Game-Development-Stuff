//
// Created by Rohan Rao on 8/7/22.
//

#include "UIObject.h"
using namespace std;


UIObject::UIObject(std::string &i_type, bool toggle, sf::Vector2f &size, std::string i_tag) {
    this->UItype = i_type;
    this->isToggle = toggle;
    this->button.setSize(size);
    this->button.setOrigin(size.x/2,size.y/2);
    this->tag = i_tag;
}


UIObject::UIObject(bool toggle, sf::Vector2f &size, std::string i_tag) {
    this->UItype = "Button";
    this->isToggle = toggle;
    this->button.setSize(size);
    this->button.setOrigin(size.x/2,size.y/2);
    this->tag = i_tag;
}



void UIObject::toggle(){
    if(!this->isActive) {
        this->isActive = true;
    }
    else{
        this->isActive = false;
    }
}

void UIObject::setPosition(sf::Vector2f &posVec) {
   this->position.x = posVec.x;
   this->position.y = posVec.y;
   this->button.setSize(this->position);
}


void UIObject::setPosition(float x, float y) {
    this->position.x = x;
    this->position.y = y;
    this->button.setPosition(x, y);
}

void UIObject::setSize(sf::Vector2f &sizeVec) {
    this->button.setSize(sizeVec);
}

void UIObject::setColor(sf::Color color) {
    this->button.setFillColor(color);
}

void UIObject::setActive(bool i_Active){
    this->isActive = i_Active;
}

void UIObject::setBorderColor(sf::Color color) {
    this->button.setOutlineColor(color);
}

void UIObject::addText(std::string in_text, sf::Font i_font, sf::Color c, int fontSize) {
    sf::Text omar;
    omar.setFont(i_font);
    omar.setString(in_text);
    omar.setFillColor(c);
    omar.setCharacterSize(fontSize);
    omar.setOrigin(omar.getCharacterSize() * omar.getString().getSize() , omar.getCharacterSize()/2);
    omar.setPosition(this->position);
}

std::string& UIObject::getTag() {
    return this->tag;
}


sf::RectangleShape& UIObject::getButton() {
    return this->button;
}



