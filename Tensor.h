//
// Created by Rohan Rao on 8/10/22.
//

#ifndef MINESWEEPER_TENSOR_H
#define MINESWEEPER_TENSOR_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Node.h"
#include <string>
#include <cmath>

#define PI 3.1415926


class Tensor {
private:
    sf::RectangleShape tensorSprite;

    //Variables values during transformation
    float magnitude;
    sf::Vector2f position;
    sf::Vector2f vector;
    sf::Vector2f unitVector;

    //Values established at initial condition
    Node *init;
    Node *dest;
    std::string tensorTag;

    sf::Vector2f initialVector;
    sf::Vector2f destIniPos;
    sf::Vector2f initIniPos;
    float initialMagnitude;

public:
    Tensor(Node* i_init, Node* i_dest) {
        this->init = i_init;
        this->dest = i_dest;

        this->initIniPos = i_init->getPosition();
        this->destIniPos = i_dest->getPosition();

        this->initialVector = sf::Vector2f(destIniPos.x - initIniPos.x, destIniPos.y - initIniPos.y);
        this->vector = sf::Vector2f(destIniPos.x - initIniPos.x, destIniPos.y - initIniPos.y);
        std::string s1(1, init->getTag());
        std::string s2(1, dest->getTag());
        this->tensorTag = s1 + s2;



        float angle = atan(vector.y / vector.x) * 180 / PI;
        this->magnitude = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
        this->initialMagnitude = magnitude;


        this->unitVector = this->vector / magnitude;

        if (vector.x == 0) {
            angle = 90;
            if (vector.y <= 0) {
                tensorSprite.setPosition(dest->getPosition().x + 32, dest->getPosition().y + 32);
            } else {
                tensorSprite.setPosition(init->getPosition().x + 32, init->getPosition().y + 32);
            }
        } else if (vector.y == 0) {
            if (vector.x <= 0) {
                tensorSprite.setPosition(dest->getPosition().x + 32, dest->getPosition().y + 32);
            } else {
                tensorSprite.setPosition(init->getPosition().x + 32, init->getPosition().y + 32);
            }
        } else {
            if ((vector.x < 0 && vector.y < 0) || (vector.x <= 0 && vector.y > 0)) {
                tensorSprite.setPosition(dest->getPosition().x + 32, dest->getPosition().y + 32);
            } else if (vector.x > 0 && vector.y > 0 || vector.y <= 0 && vector.x > 0) {
                tensorSprite.setPosition(init->getPosition().x + 32, init->getPosition().y + 32);
            }
        }
    }


        void update() {

            vector = dest->getPosition() - init->getPosition();
            float angle = atan(vector.y / vector.x) * 180 / PI;
            this->magnitude = sqrt(pow(vector.x, 2) + pow(vector.y, 2));

            sf::Vector2f rectSize(magnitude, 5);
            tensorSprite.setSize(rectSize);
            tensorSprite.setOrigin(magnitude / 2, 5 / 2);
            tensorSprite.setFillColor(sf::Color::White);
            tensorSprite.setRotation(angle);
            sf::Vector2f tensorPos = sf::Vector2f((dest->getPosition().x + init->getPosition().x) / 2,
                                                  (dest->getPosition().y + init->getPosition().y) / 2);
            tensorSprite.setPosition(tensorPos);
        }



        std::string getTag(){
        return this->tensorTag;
    }

    sf::Vector2f getTensorVector(){
        return this->vector;
    }

    sf::Vector2f& getTensorVector(char originTag){
        Node* originNode = nullptr;
        Node* destNode = nullptr;
        sf::Vector2f* tensorVector = new sf::Vector2f(0,0);
        float slope = 0;

        if(this->init->getTag() == originTag){
            originNode = this->init;
            destNode = this->dest;
        }
        else {
            originNode = this->dest;
            destNode = this->init;
        }

        //Now that we have an origin Node we can...
        //SAVE THE WORLD

        if((originNode != nullptr) && (destNode != nullptr)) {
            tensorVector->x = destNode->getPosition().x - originNode->getPosition().x;
            tensorVector->y = -(dest->getPosition().y - originNode->getPosition().y);
        }
        return *tensorVector;
    }


    sf::Vector2f& getTensorEquation(char originTag){
       sf::Vector2f tensorVector = this->getTensorVector(originTag);
       sf::Vector2f *slopeForm = new sf::Vector2f(0,0); // slope is in vector 2 form containing <m, b> for (mx + b)
       float slope = tensorVector.y/tensorVector.x;
       float b = 0;
       Node* originNode = nullptr;

        if(this->init->getTag() == originTag){
            originNode = this->init;
        }
        else{
            originNode = this->dest;
        }

        if(originNode != nullptr) {
            b = originNode->getPosition().y - (originNode->getPosition().x)*(slope);
            slopeForm->x = slope;
            slopeForm->y = b;
        }

        return *slopeForm;
    }




    //Gets the numerical range (in terms of the original coordinates
    sf::Vector2f* getXrange(){
        float originPoint = 0;
        float destPoint = 0;
        sf::Vector2f* xRange = new sf::Vector2f;

        if(init->getPosition().x < dest->getPosition().x){
            originPoint = init->getPosition().x;
            destPoint = dest->getPosition().x;
        }
        else{
            originPoint = dest->getPosition().x;
            destPoint = init->getPosition().x;
        }

        xRange->x = originPoint;
        xRange->y = destPoint;

        return xRange;
    }

    //Gets the maximum and minimum y coordinates in the grid
    sf::Vector2f* getYRange(){
        float originPoint = 0;
        float destPoint = 0;
        sf::Vector2f* yRange = new sf::Vector2f;

        if(init->getPosition().y > dest->getPosition().y){
            originPoint = init->getPosition().y;
            destPoint = dest->getPosition().y;
        }
        else{
            originPoint = dest->getPosition().y;
            destPoint = init->getPosition().y;
        }
        yRange->x = originPoint;
        yRange->y = destPoint;
    }




    float getMagnitude() {
        return this->magnitude;
    }



    sf::Vector2<Node*>& getNodesHor(){

            sf::Vector2<Node*>* orderNodes = new sf::Vector2<Node*>;
            if(this->init->getPosition().x < this->dest->getPosition().x){
                orderNodes->x = this->init;
                orderNodes->y = this->dest;
            }
            else{
                orderNodes->x = this->dest;
                orderNodes->y = this->init;
            }
            return *orderNodes;

    }





        sf::RectangleShape& getTensorSprite() {
            return this->tensorSprite;
        }

    };



#endif //MINESWEEPER_TENSOR_H
