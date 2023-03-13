//
// Created by Rohan Rao on 8/10/22.
//

#include "Node.h"
//
// Created by Rohan Rao on 8/10/22.
//

#ifndef MINESWEEPER_NODE_H
#define MINESWEEPER_NODE_H

#include <SFML/Graphics.hpp>
#include "Canvas.h"
#include <vector>

class Node {
private:
    sf::Vector2f position;
    //std::vector<T> *infoVector = new std::vector<T>;
    sf::CircleShape circleShape;
    char tag;


public:
    Node(char i_tag, sf::Vector2f &i_pos){
        this->tag = i_tag;
        this->circleShape.setOrigin(8,8);
        this->position = i_pos;
        this->circleShape.setRadius(8);

        sf::Color nodeColor;
        nodeColor.r = 0;
        nodeColor.g = 130;
        nodeColor.b = 40;

        this->circleShape.setFillColor(nodeColor);
    }

    sf::CircleShape& getNodeSprite(){
        return this->circleShape;
    }

    sf::Vector2f& getPosition(){
        return this->position;
    }

    void setColor(sf::Color color){
        this->circleShape.setFillColor(color);
    }

    char getTag(){
        return this->tag;
    }

    void update(){
        this->circleShape.setPosition(this->position);
    }





};


#endif //MINESWEEPER_NODE_H
