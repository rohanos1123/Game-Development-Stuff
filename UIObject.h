//
// Created by Rohan Rao on 8/7/22.
//

#ifndef MINESWEEPER_UIOBJECT_H
#define MINESWEEPER_UIOBJECT_H

#include <SFML/Graphics.hpp>
#include <string>



class UIObject {

private:

    std::string UItype;
    std::string tag;
    sf::Vector2f size;
    sf::Vector2f position;
    sf::Color color;
    sf::RectangleShape button;


public:
    bool isToggle = false;
    bool isActive = false;

    UIObject(std::string &i_type, bool toggle, sf::Vector2f &size, std::string i_tag);
    UIObject(bool toggle, sf::Vector2f &size, std::string i_tag);


    void setSize(sf::Vector2f &sizeVec);
    void setPosition(sf::Vector2f &posVec);
    void setPosition(float x, float y);
    void setActive(bool i_Active);
    void setColor(sf::Color color);
    void setBorderColor(sf::Color color);
    void addText(std::string in_text, sf::Font i_font, sf::Color c = sf::Color::Black, int fontSize = 10);
    void toggle();

    std::string& getTag();
    sf::RectangleShape& getButton();







};


#endif //MINESWEEPER_UIOBJECT_H
