//
// Created by Rohan Rao on 8/7/22.
//
#ifndef MINESWEEPER_TEXTILE_H
#define MINESWEEPER_TEXTILE_H


#include <SFML/Graphics.hpp>


class Textile {
private:
    float p_red;
    float p_blue;
    float p_green;
    sf::Color newColor;
    sf::Vector2f *size = new sf::Vector2f;
    sf::Vector2f *pos = new sf::Vector2f;
    sf::RectangleShape pixel;

public:


    //Default Constructor
    Textile(){
        newColor.r = 0;
        newColor.b = 0;
        newColor.g = 0;

        size->x = 10;
        size->y = 10;
        pos->x = 0;
        pos->y = 0;


        pixel.setSize(*size);
        pixel.setPosition(*pos);
        pixel.setFillColor(newColor);


    }

    //Useful Constructor
    Textile(sf::Vector2f& i_size, sf::Vector2f& i_position, int i_r, int i_g, int i_b){
        this->size = &i_size;
        this->pos = &i_position;
        this->newColor.r = i_r;
        this->newColor.g = i_g;
        this->newColor.b = i_b;
    }

    void setSize(float i_xSize, float i_ySize){
        size->x = i_xSize;
        size->y = i_ySize;
    }

    void setColor(int i_r, int i_g, int i_b){
        newColor.r = i_r;
        newColor.g = i_g;
        newColor.b = i_b;
    };

    //Input vector in form <Red, Green, Blue>
    void setColor(sf::Vector3f& colorVector){
        newColor.r = colorVector.x;
        newColor.g = colorVector.y;
        newColor.b = colorVector.z;
    };

    void setPosition(float xPos, float yPos){
        pos->x = xPos;
        pos->y = yPos;
    }

    void setPosition(sf::Vector2f &posVector){
        pos->x = posVector.x;
        pos->y = posVector.y;
    }

    void pixelUpdate(){
        pixel.setSize(*size);
        pixel.setPosition(*pos);
        pixel.setFillColor(newColor);
    }

    sf::RectangleShape& getPixel(){
        return this->pixel;
    }


};


#endif //MINESWEEPER_TEXTILE_H
