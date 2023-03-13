#include <iostream>
#include <fstream>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "UIObject.cpp"
#include "UISpace.cpp"
#include "Canvas.cpp"
#include "graphSpace.h"
#include "Matrix.cpp"

#include <cmath>

#define  PI 3.1415926





 //PLACE THE SCALING FUNCTIONS FOR EACH NODE ON LINE 280"
int main(){


    cout<<pow(2, 53)<<endl;
    //Initialize the variable Names:

    int winSizeX = 1000;
    int winSizeY = 1000;
    bool isPressed = false;
    bool isPressedRight = false;
    bool multSelect = false;
    bool calcMode = false;
    bool graphMode = false;
    int nodeNumber = 0;
    sf::Vector2f initMPos;
    sf::Vector2f destMPos;
    vector<sf::RectangleShape>* selectedSet = new vector<sf::RectangleShape>;
    vector<sf::RectangleShape> vectSet;
    map<pair<int, int>, sf::RectangleShape> selectedMap;
    int numOfRights = 0;
    Matrix jatstation(4,4);
    Matrix jatstation2(4,4);

   vector<float> j1R1;
   j1R1.push_back(1);
   j1R1.push_back(5);
   j1R1.push_back(4);
   j1R1.push_back(4);


   vector<float> j1R2;
   j1R2.push_back(6);
   j1R2.push_back(2);
   j1R2.push_back(3);
   j1R2.push_back(5);


   vector<float> j2R1;
   j2R1.push_back(1);
   j2R1.push_back(8);
   j2R1.push_back(2);
   j2R1.push_back(3);

    vector<float> j2R2;
    j2R2.push_back(9);
    j2R2.push_back(1);
    j2R2.push_back(5);
    j2R2.push_back(2);

    vector<float> j2R3;
    j2R3.push_back(7);
    j2R3.push_back(4);
    j2R3.push_back(6);
    j2R3.push_back(2);


    jatstation.insertRow(0, j1R1);
    jatstation.insertRow(1, j1R2);
    jatstation.insertRow(2, j2R1);
    jatstation.insertRow(3, j2R2);

    cout<<endl;

    jatstation.AugmentCol(j2R3);
    jatstation.print();
    cout<<endl;

    vector<float>* brian = rref(jatstation);
    for(int i = 0; i < brian->size(); i++){
        cout<<brian->at(i)<<endl;
    }

    /*
    jatstation.rowReplacement(0, 1, -6);
    jatstation.rowReplacement(0, 2, -1);

    jatstation.rowReplacement(1, 2, float(1)/5);

    //reverse row Replacement
    jatstation.rowReplacement(2, 1, 9/9.2);
    jatstation.rowReplacement(2, 0, -3/9.2);

    //
    jatstation.rowReplacement(1, 0, float(2)/5);
     */










    /*
    for(int i = 0; i < jatstation.getColumn(1)->size(); i++){
        cout<<*jatstation.getColumn(1)->at(i)<<endl;
    }
     */





    sf::Vector2f windowSize;
    windowSize.x = winSizeX;
    windowSize.y = winSizeY;



    /* INITIALIZING ASSET SPACES */


    //UI Constants and UI space initializtion
    sf::Vector2f colorButtonSize(50, 50);
    UISpace u;



    //Instantiate UI Objects


    UIObject greenButton(true, colorButtonSize, "green");
    greenButton.setPosition(1100, 100);
    greenButton.setColor(sf::Color::Green);

    UIObject redButton(true, colorButtonSize, "red");
    redButton.setPosition(1200, 100);
    redButton.setColor(sf::Color::Red);

    UIObject blueButton(true, colorButtonSize, "blue");
    blueButton.setPosition(1300, 100);
    blueButton.setColor(sf::Color::Blue);

    UIObject graphModeToggle(true, colorButtonSize, "graph");
    graphModeToggle.setPosition(1100, 300);
    graphModeToggle.setColor(sf::Color::Cyan);

    UIObject multSelectToggle(true, colorButtonSize, "multSelect");
    multSelectToggle.setPosition(1200, 300);
    multSelectToggle.setColor(sf::Color::Magenta);

;
    //Add UI objects to the UISpace
    u.addUIObject(&greenButton);
    u.addUIObject(&redButton);
    u.addUIObject(&blueButton);
    u.addUIObject(&graphModeToggle);
    u.addUIObject(&multSelectToggle);


    //Initialize the Canvas Space (for pixels)

    Canvas *c = new Canvas( 50, 50, windowSize);
    sf::RectangleShape selectionRect;

    //Initialize the Graph Space
    graphSpace *g = new graphSpace();



    //Making the selection square color and box
    sf::Color selectColor;
    selectColor.r = 255;
    selectColor.g = 255;
    selectColor.b = 0;
    selectColor.a = 100;

    selectionRect.setFillColor(selectColor);
    selectionRect.setPosition(500, 500);
    sf::Vector2f omar(c->getRectSize());
    selectionRect.setSize(omar);
    selectionRect.setOrigin(omar.x/2, omar.y/2);

    sf::CircleShape tomas;
    tomas.setOrigin(8,8);
    tomas.setRadius(8);
    tomas.setPosition(0,0);
    tomas.setFillColor(selectColor);

    //Initializing the state of the color in green

    string colorState = "green";

    sf::RenderWindow window(sf::VideoMode(winSizeX + 500, winSizeY), "Test Game", sf::Style::Close);

    while(window.isOpen()) {
        sf::Event evnt;

        while (window.pollEvent(evnt)) {
            switch (evnt.type) {
                case (sf::Event::Closed):
                    window.close();
                    break;
                case (sf::Event::TextEntered):
                    if (evnt.text.unicode < 128) {
                        cout << (char) evnt.text.unicode << endl;
                    }
                    break;
            }
        }



        /* TODO : While mouse is in game bounds (not UI Bounds) */
        if (sf::Mouse::getPosition(window).x < 1000) {
            /* TODO: While graphMode is not selected */
            // Code Relating to placing the selection rectangle sprite
            if (!graphMode) {
                /* TODO: WHILE NOT IN MULTISELCTED MODE */
                if (!multSelect) {
                    int x = sf::Mouse::getPosition(window).x;
                    int y = sf::Mouse::getPosition(window).y;
                    sf::Vector2f mousePos(x, y);
                    selectionRect.setPosition(c->getClosestSquare(mousePos));
                } else {
                    /* TODO: WHILE IN MULTSELECT MODE */
                    if (calcMode) {
                        for (int i = 0; i < c->generateSet(initMPos, destMPos)->size(); i++) {

                            float x = c->generateSet(initMPos, destMPos)->at(i)->x;
                            float y = c->generateSet(initMPos, destMPos)->at(i)->y;

                            pair<int, int> sterling((int) x, (int) y);

                            if (selectedMap.find(sterling) == selectedMap.end()) {

                                sf::RectangleShape selectionRect;
                                selectionRect.setFillColor(selectColor);
                                selectionRect.setPosition(x, y);
                                selectionRect.setSize(c->getRectSize());
                                selectionRect.setOrigin(omar.x / 2, omar.y / 2);

                                selectedMap[sterling] = selectionRect;
                            }

                        }
                    }
                    calcMode = false;
                }

                // Code for placing down a block of a certain color (what to do when mouse is clicked)
                if (!multSelect) {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        isPressed = true;
                        int x = sf::Mouse::getPosition(window).x;
                        int y = sf::Mouse::getPosition(window).y;
                        sf::Vector2f posVect(x, y);

                        if (colorState == "red") {
                            sf::Vector3f colorVect(255, 0, 0);
                            c->addPixel(posVect, colorVect);
                        } else if (colorState == "blue") {

                            sf::Vector3f colorVect(0, 0, 255);
                            c->addPixel(posVect, colorVect);

                        } else if (colorState == "green") {
                            sf::Vector3f colorVect(0, 255, 0);
                            c->addPixel(posVect, colorVect);
                        }
                    }
                } else {

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isPressed) {
                        isPressed = true;
                        initMPos.x = sf::Mouse::getPosition(window).x;
                        initMPos.y = sf::Mouse::getPosition(window).y;
                    }


                    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && isPressed) {
                        destMPos.x = sf::Mouse::getPosition(window).x;
                        destMPos.y = sf::Mouse::getPosition(window).y;

                        isPressed = false;
                        calcMode = true;

                    }

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                        isPressed = false;
                        selectedSet->clear();
                    }
                }
            }

                //TODO: If it is in graphMode
            else {
                sf::Vector2f floatMouse;
                floatMouse.x = ((float) sf::Mouse::getPosition(window).x);
                floatMouse.y = ((float) sf::Mouse::getPosition(window).y);
                sf::Vector2f akil = c->getClosestSquare(floatMouse);
                akil.x -= 10;
                akil.y -= 10;

                tomas.setPosition(akil);


                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isPressed) {
                    isPressed = true;
                    char nodeChar = 'A' + nodeNumber;
                    nodeNumber++;
                    g->addNode(nodeChar, akil);
                }
                else if(!sf::Mouse::isButtonPressed(sf::Mouse::Left) && isPressed){
                    isPressed = false;
                }



                if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !isPressedRight) {
                    isPressedRight = true;
                    sf::Vector2f floatMouse;
                    floatMouse.x = (float) sf::Mouse::getPosition(window).x;
                    floatMouse.y = (float) sf::Mouse::getPosition(window).y;
                    Node *init;
                    Node *dest;
                    if (numOfRights % 2 == 0) {
                        init = g->getNode(akil);
                    } else {
                        if (init != nullptr) {
                            dest = g->getNode(akil);
                        }

                        if (dest != nullptr && init != nullptr) {
                            g->addTensor(init, dest);
                        }

                    }
                    numOfRights++;
                }

                if (!sf::Mouse::isButtonPressed(sf::Mouse::Right) && isPressedRight) {
                    isPressedRight = false;
                }



            }
        } else {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isPressed) {
                isPressed = true;
                if (u.checkPosition(sf::Mouse::getPosition(window)) != nullptr) {
                    colorState = u.checkPosition(sf::Mouse::getPosition(window))->getTag();
                }

                if (u.checkPosition(sf::Mouse::getPosition(window))  != nullptr) {
                    if(u.checkPosition(sf::Mouse::getPosition(window))->getTag() == "graph") {

                        if (!graphMode) {
                            graphMode = true;
                        } else {
                            graphMode = false;
                        }
                    }
                }
            } else if (!sf::Mouse::Mouse::isButtonPressed(sf::Mouse::Left) && isPressed) {
                isPressed = false;
            }

        }


        c->updateCanvas(&window);
        g->draw(window);
        u.draw(window);

        if (!multSelect) {
            window.draw(selectionRect);


        } else {
            auto iter = selectedMap.begin();
            for (; iter != selectedMap.end(); iter++) {
                window.draw(iter->second);
            }
        }

        if(graphMode){
            if(g->getIntersectingPointsX(500) != nullptr){
                for(int i = 0; i < g->getIntersectingPointsX(500)->size(); i++){
                    sf::Vector2f omar = g->getIntersectingPointsX(500)->at(i);
                    cout<<omar.x<<" , "<<omar.y<<endl;


                }
                cout<<endl;
            }

            window.draw(tomas);
        }

        window.display();
        window.clear();

    }




}
