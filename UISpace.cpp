//
// Created by Rohan Rao on 8/9/22.
//

#include "UISpace.h"
UISpace::UISpace() {}

void UISpace::addUIObject(UIObject *newObj) {
    this->UISet->push_back(newObj);

}

UIObject* UISpace::checkPosition(sf::Vector2<int> pos) {
    for (int i = 0; i < this->UISet->size(); i++) {
        if (this->UISet->at(i)->getButton().getGlobalBounds().contains(pos.x, pos.y)) {
            if(this->UISet->at(i)->isToggle) {
                this->UISet->at(i)->toggle();
            }
            return this->UISet->at(i);
        }
    }

    return nullptr;
}

void UISpace::draw(sf::RenderWindow &window) {
    for(int i = 0; i < this->UISet->size(); i++) {
        window.draw(UISet->at(i)->getButton());
    }
}

UIObject* UISpace::getUIWithTag(std::string omar) {
    for(int i = 0; i < this->UISet->size(); i++){
        if(this->UISet->at(i)->getTag() == omar){
            return this->UISet->at(i);
        }
    }
    return nullptr;
}

std::vector<UIObject*>* UISpace::getUISpace(){
    return this->UISet;
}



