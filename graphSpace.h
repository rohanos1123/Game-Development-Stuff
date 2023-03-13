//
// Created by Rohan Rao on 8/10/22.
//

#ifndef MINESWEEPER_GRAPHSPACE_H
#define MINESWEEPER_GRAPHSPACE_H
#include "Node.h"
#include "Tensor.h"
#include <vector>
#include "Textile.h"
#include <cmath>
#include <SFML/Graphics.hpp>

#define PI 3.1415926

class graphSpace {
private:
    std::vector<Node*>* nodeSet = new std::vector<Node*>;
    std::vector<Tensor*>* tensorSet = new std::vector<Tensor*>;
    std::vector<Textile *> *encapsulatedSet = new std::vector<Textile *>;

    std::string excludeChar(std::string i_string, char target){
        std::string modString = "";

        for(int i = 0; i < i_string.size(); i++){
            if(i_string.at(i) != target){
                modString.push_back(i_string.at(i));
            }
        }

        return modString;
    }

public:
    graphSpace(){};

    void addNode(char tag, sf::Vector2f &i_pos){
        Node *n = new Node(tag, i_pos);
        nodeSet->push_back(n);
    }

    void addTensor(Node* i_init, Node* i_dest){
        Tensor *t = new Tensor(i_init, i_dest);
        tensorSet->push_back(t);
    }

    void draw(sf::RenderWindow &window){

        for(int i = 0; i < nodeSet->size(); i++){
            nodeSet->at(i)->update();
            window.draw(nodeSet->at(i)->getNodeSprite());
        }

        for(int i = 0; i < tensorSet->size(); i++){
            tensorSet->at(i)->update();
            window.draw(tensorSet->at(i)->getTensorSprite());
        }

    }

    //Gets the y Extrema of the graph in format <min, max>
    sf::Vector2<Node*>* getYextrema(){
        float minY = 0;
        float maxY = 0;
        sf::Vector2<Node*> *yExtrema = new sf::Vector2<Node*>;

        if(!this->nodeSet->empty()) {

            Node *minNodeY;
            Node *maxNodeY;

            for (int i = 0; i < this->nodeSet->size(); i++) {
                if (this->nodeSet->at(i)->getPosition().y > minY) {
                    minY = this->nodeSet->at(i)->getPosition().y;
                    minNodeY = this->nodeSet->at(i);
                } else if (this->nodeSet->at(i)->getPosition().y > maxY) {
                    maxY = this->nodeSet->at(i)->getPosition().y;
                    maxNodeY = this->nodeSet->at(i);
                }
            }
            yExtrema->x = minNodeY;
            yExtrema->y = maxNodeY;
            return yExtrema;
        }
        return nullptr;
    }


    //Gets x extrema of the graph of the <min, max>
    sf::Vector2<Node*>* getXExtrema(){
        float minX = 0;
        float maxX = 0;
        sf::Vector2<Node*>* xExtrema = new sf::Vector2<Node*>;

        if(!this->nodeSet->empty()) {
            Node* xMinNode;
            Node* xMaxNode;

            for (int i = 0; i < this->nodeSet->size(); i++) {
                if(this->nodeSet->at(i)->getPosition().x < minX){
                    minX = this->nodeSet->at(i)->getPosition().x;
                    xMinNode = this->nodeSet->at(i);
                }
                else if(this->nodeSet->at(i)->getPosition().x > maxX){
                    maxX = this->nodeSet->at(i)->getPosition().x;
                    xMaxNode = this->nodeSet->at(i);
                }
            }
            xExtrema->x = xMinNode;
            xExtrema->y = xMaxNode;
            return xExtrema;
        }
        else{
            return nullptr;
        }
    }

    //WHEN USING THIS CHECK IF RETURN IS A NULLPTR
    Node* getNodeWithTag(char tag){
        Node* desNode = nullptr;

        for(int i = 0; i < this->nodeSet->size(); i++){
            if(this->nodeSet->at(i)->getTag() == tag){
                desNode = this->nodeSet->at(i);
            }
        }

        return desNode;

    }

    std::vector<Tensor*>* getTensorsWithNode(char nodeTag){
        std::vector<Tensor*> *omar = new std::vector<Tensor*>;
        if(!this->tensorSet->empty()) {
            for (int i = 0; i < this->tensorSet->size(); i++) {
                if (this->tensorSet->at(i)->getTag().find(nodeTag) != std::string::npos) {
                    omar->push_back(this->tensorSet->at(i));
                }
            }
            return omar;
        }
        else{
            return nullptr;
        }
    }

    std::vector<sf::Vector2f>* vectRemove(std::vector<sf::Vector2f> *in_vect, int remIndex){
        std::vector<sf::Vector2f>* tempVec = new std::vector<sf::Vector2f>;
        for(int i = 0; i < in_vect->size(); i++){
            if(i != remIndex){
                tempVec->push_back(in_vect->at(i));
            }
        }
        return tempVec;
    }

    std::vector<Node*>* getNeighborNodes(char target){
        std::vector<Node*>* neighboringNodes = new std::vector<Node*>;
        std::vector<Tensor*>* conEdges = this->getTensorsWithNode(target);

        if(conEdges != nullptr) {
            for (int i = 0; i < conEdges->size(); i++) {
                char targetTag = this->excludeChar(conEdges->at(i)->getTag(), target)[0];
                neighboringNodes->push_back(this->getNodeWithTag(targetTag));
            }
        }

        return neighboringNodes;
    }

    //Encapsulate algorithm
    std::vector<std::vector<Textile*>*> EncapsulatePixels(Canvas *c){
        int minPos = getYextrema()->x->getPosition().y;
        int maxPos = getYextrema()->y->getPosition().y;
        for(int i = minPos; i < maxPos; i += c->getSquDim().y){

        }
    }

    //Get the x range of each Tensor

    /*
     * Given a vertical Line of X = xCoord find the tensors that intersect with
     * the line (assuming all tensors are continuous)
     */



    std::vector<Tensor*>* getIntersectingTensorsX(float xCoord){

        std::vector<Tensor*>* intersectingTensors = new std::vector<Tensor*>;

        for(int i = 0; i < this->tensorSet->size(); i++) {
            sf::Vector2f* vecXRange = this->tensorSet->at(i)->getXrange();
            if((xCoord >= vecXRange->x) && (xCoord) <= vecXRange->y){
                intersectingTensors->push_back(this->tensorSet->at(i));
            }
        }
        return intersectingTensors;
    }


    std::vector<Tensor*>* getIntersectingTensorsY(float yCoord) {
        std::vector<Tensor*> *intersectTensor = new std::vector<Tensor*>;
        for (int i = 0; i < this->tensorSet->size(); i++) {
            sf::Vector2f *vecYrange = this->tensorSet->at(i)->getYRange();
            if ((yCoord >= vecYrange->x) && (yCoord <= vecYrange->y)) {
                intersectTensor->push_back(this->tensorSet->at(i));
            }
        }
        return intersectTensor;
    }



    Node* getClosestBehind(float i_x) {
        float min = 100000000;
        Node *closestNode = nullptr;


        for (int i = 0; i < this->nodeSet->size(); i++) {
            float distance = this->nodeSet->at(i)->getPosition().x - i_x;
            if (distance < 0) {
                if (abs(distance) < min) {
                    min = abs(distance);
                    closestNode = this->nodeSet->at(i);
                }
            }
        }

        return closestNode;
    }

    //Gets the intersecting points (in order of lowest to highest y coordinate)

    std::vector<sf::Vector2f>*  getIntersectingPointsX(float xCoord){

        std::vector<Tensor*>* in_Tens = this->getIntersectingTensorsX(xCoord);
        std::vector<sf::Vector2f>* vec_inCoords = new std::vector<sf::Vector2f>;

        if(in_Tens->size() > 1) {
            for (int i = 0; i < in_Tens->size(); i++) {
                //Get left most Tensor (node of tensor with the smaller x value)

                Node *origin = in_Tens->at(i)->getNodesHor().x;
                //cout<<origin->getTag()<<endl;
                sf::Vector2f tE = in_Tens->at(i)->getTensorEquation(origin->getTag());
                float yVal = tE.x * xCoord + tE.y;
                sf::Vector2f coord(xCoord, yVal);
                vec_inCoords->push_back(coord);
            }

            vec_inCoords = this->orderVectSetY(vec_inCoords);
            return vec_inCoords;
        }
        else{
            return nullptr;
        }
    }



    std::vector<sf::Vector2f>* getIntersectingPointsY(float yCoord){
        std::vector<Tensor*>* in_tens = this->getIntersectingTensorsY(yCoord);
        std::vector<sf::Vector2f>* in_coords = new std::vector<sf::Vector2f>;

        if(in_tens->size() > 1){
        for(int i = 0; i < in_tens->size(); i++){
                Node *origin = in_tens->at(i)->getNodesHor().x;
                sf::Vector2f tE = in_tens->at(i)->getTensorVector(origin->getTag());
                float xVal = (yCoord - tE.y)/tE.x;
                sf::Vector2f n_coord(xVal, yCoord);
                in_coords->push_back(n_coord);
;            }
            //TODO: Build a method to order a set by X coordinates
            in_coords = this->orderVectSetX(in_coords);
        }
        else{
            return nullptr;

        }




    }





    std::vector<sf::Vector2f>* orderVectSetY(std::vector<sf::Vector2f>* in_vect){
        std::vector<sf::Vector2f>* orderedVectSet = new std::vector<sf::Vector2f>;
        auto ogSize = in_vect->size();
        sf::Vector2f smallestVect(0,0);
        int removeIndex = 0;


        for(int j = 0; j < ogSize; j++) {
            float min = 1000000;
            for (int i = 0; i < in_vect->size(); i++) {
                sf::Vector2f currVect = in_vect->at(i);

                if(currVect.y < min){
                    min = currVect.y;
                    smallestVect = currVect;
                    removeIndex = i;
                }
            }

            in_vect = this->vectRemove(in_vect, removeIndex);
            orderedVectSet->push_back(smallestVect);
        }
        return orderedVectSet;
    }

    //Order the vect set by the value of the X coordinate
    std::vector<sf::Vector2f>* orderVectSetX(std::vector<sf::Vector2f>* in_vect){
        std::vector<sf::Vector2f>* orderedVectSet = new std::vector<sf::Vector2f>;
        auto ogSize = in_vect->size();
        sf::Vector2f smallestVect(0,0);
        int removeIndex = 0;


        for(int j = 0; j < ogSize; j++) {
            float min = 1000000;
            for (int i = 0; i < in_vect->size(); i++) {
                sf::Vector2f currVect = in_vect->at(i);

                if(currVect.x < min){
                    min = currVect.x;
                    smallestVect = currVect;
                    removeIndex = i;
                }
            }

            in_vect = this->vectRemove(in_vect, removeIndex);
            orderedVectSet->push_back(smallestVect);
        }
        return orderedVectSet;
    }





    void encapsulate(Canvas *c) {
        float leftNodeX = this->getXExtrema()->x->getPosition().x;
        float rightNodeX = this->getXExtrema()->y->getPosition().x;


        for (int i = leftNodeX; i < rightNodeX; i += c->getSquDim().x) {
            std::vector<sf::Vector2f> *intersectingPoints = this->getIntersectingPointsX(i);
            sf::Vector2f entryPoint;
            sf::Vector2f exitPoint;

            if (intersectingPoints->size() > 1) {
                for (int j = 0; j < intersectingPoints->size(); j++) {
                    if (j % 2 == 0) {
                        entryPoint = intersectingPoints->at(j);
                    } else {
                        exitPoint = intersectingPoints->at(j);
                        std::vector<sf::Vector2f *> *king = c->generateSet(entryPoint, exitPoint);
                        for (int k = 0; k < king->size(); k++) {
                            Textile* targetTextile = c->getTextileFromPos(king->at(i));
                            if(targetTextile != nullptr){
                                this->encapsulatedSet->push_back(targetTextile);
                            }
                        }
                    }
                }
            }
        }
    }














    float getAngle(char nodeTag){
        auto bruh = this->getTensorsWithNode(nodeTag);
        float angle = -1;
        if(bruh != nullptr) {
            if (bruh->size() == 2) {
                Tensor *t1 = bruh->at(0);
                Tensor *t2 = bruh->at(1);

                //Calculate the angle between the vectors using the dot product:
                float dotProd = (t1->getTensorVector(nodeTag).x * t2->getTensorVector(nodeTag).x) +
                        (t1->getTensorVector(nodeTag).y * t2->getTensorVector(nodeTag).y);

                float arcCosThis = dotProd/(t1->getMagnitude() * t2->getMagnitude());
                angle = acos(arcCosThis)  * 180/PI;
            } else {
                cout << "Node is not connected to 2 tensors" << endl;
            }
        }

        return angle;
    }




    std::vector<Node*>* getNodeSet(){
        return this->nodeSet;
    }

    std::vector<Tensor*>* getTensorSet(){
        return this->tensorSet;
    }






    // Triangualize a polygon with the nodes in the graphSpace
    // void Triangualize()

    //  Triangualize a polygon with given nodes in the graphSpace (if degree > 1) make each triangle a wheel node
    //Void Triangualize(int degrees = 1)


    Node* getNode(sf::Vector2f const &i_pos){
        for(int i = 0; i < this->nodeSet->size(); i++){
            if(this->nodeSet->at(i)->getNodeSprite().getGlobalBounds().contains(i_pos)){
                return nodeSet->at(i);
            }
        }
        return nullptr;
    }







};


#endif //MINESWEEPER_GRAPHSPACE_H
