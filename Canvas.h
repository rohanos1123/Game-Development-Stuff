//
// Created by Rohan Rao on 8/7/22.
//

#ifndef MINESWEEPER_CANVAS_H
#define MINESWEEPER_CANVAS_H

#include "Textile.h"
#include <vector>



class Canvas {
private:
    std::vector<Textile*>* tileBoard = new std::vector<Textile*>;
    std::map<std::pair<int, int>, Textile*> tileMap;
    std::vector<sf::RectangleShape*>* gridVector = new std::vector<sf::RectangleShape*>;

    float mGrid_size; // The horizontal side of the grid
    float nGrid_size; // the vertical size of the grid;

    float sq_x; //Size of each square (x component)
    float sq_y; //Size of each square (y component)

    float windowHeight;
    float windowLength;

public:
    Canvas(float m, float n, sf::Vector2f screenDimensions);
    void addPixel(float xPos, float yPos, float r, float g, float b);
    void addPixel(sf::Vector2f& i_pos, sf::Vector3f& color);
    void buildGrid();
    sf::Vector2f& getClosestSquare(sf::Vector2f& initialPostion);
    void updateCanvas(sf::RenderWindow *window);
    sf::Vector2f& getRectSize() const;
    std::vector<sf::Vector2f*>* generateSet(sf::Vector2f &initPos, sf::Vector2f &destPos);
    std::vector<Textile*>* getGameSpace();
    sf::Vector2f& getSquDim();
    Textile* getTextileFromPos(sf::Vector2f *king);

};


#endif //MINESWEEPER_CANVAS_H
