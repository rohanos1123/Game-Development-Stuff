//
// Created by Rohan Rao on 8/9/22.
//

#ifndef MINESWEEPER_UISPACE_H
#define MINESWEEPER_UISPACE_H
#include <SFML/Graphics.hpp>
#include "UIObject.h"
#include <vector>


class UISpace {
private:
    std::vector<UIObject*> *UISet = new std::vector<UIObject*>;

public:
    UISpace();
    void addUIObject(UIObject *newObj);
    UIObject* checkPosition(sf::Vector2<int> pos);
    std::vector<UIObject*>* getUISpace();
    UIObject* getUIWithTag(std::string omar);
    void draw(sf::RenderWindow &window);





};


#endif //MINESWEEPER_UISPACE_H
