//
// Created by Rohan Rao on 8/7/22.
//

#include "Canvas.h"
#include <vector>


Canvas::Canvas(float i_m, float i_n, sf::Vector2f screenDimension){
    this->mGrid_size = i_m; // Determines the number of grid spaces in (Row) m direction
    this->nGrid_size = i_n; // Determines the number of grid spaces in (Row) n direction

    this->sq_x = screenDimension.x/nGrid_size; //Initialize the x size of each square
    this->sq_y = screenDimension.y/mGrid_size; //Initialize the y size of each square

    this->windowHeight = screenDimension.y; // Initialize the height of the window
    this->windowLength = screenDimension.x; // Initialize the length of window

    buildGrid();
}

sf::Vector2f& Canvas::getClosestSquare(sf::Vector2f& initialPosition){

    float nSqu = int((initialPosition.x)/(sq_x));
    float mSqu = int((initialPosition.y)/(sq_y));

    float gridPositionX = nSqu * this->sq_x + this->sq_x/2;
    float gridPositionY = mSqu * this->sq_y + this->sq_y/2;

    sf::Vector2f coords;
    coords.x = gridPositionX;
    coords.y = gridPositionY;

    return coords;
}


void Canvas::addPixel(float xPos, float yPos, float r, float g, float b) {
    sf::Vector2f pos = sf::Vector2f(xPos, yPos);
    sf::Vector3f color = sf::Vector3f(r,g,b);


   pos = Canvas::getClosestSquare(pos);
   std::pair<int, int> omar(int(pos.x), int(pos.y));


    Textile *p = new Textile;
    p->setPosition(pos);
    p->setSize(sq_x, sq_y);
    p->setColor(color);
    p->getPixel().setOrigin(sq_x/2,sq_y/2);


    this->tileMap[omar] = p;


    this->tileBoard->push_back(this->tileMap[omar]);
}

void Canvas::addPixel(sf::Vector2f &i_pos, sf::Vector3f &color) {

    sf::Vector2f pos = Canvas::getClosestSquare(i_pos);
    std::pair<int, int> omar(int(pos.x), int(pos.y));

    Textile *p = new Textile;
    p->setPosition(pos);
    p->setSize(sq_x, sq_y);
    p->setColor(color);
    p->getPixel().setOrigin(sq_x/2, sq_y/2);

    tileMap[omar] = p;

    this->tileBoard->push_back(p);
}

std::vector<Textile*>* Canvas::getGameSpace(){
    return this->tileBoard;
}

void Canvas::buildGrid(){
    for(int i = 0; i <= this->mGrid_size; i++){
        //Calculate DEST:
        int dest = i * this->sq_y;

        sf::Vector2f size(windowLength, 2);
        sf::RectangleShape *horizontalLine = new sf::RectangleShape(size);
        horizontalLine->setOrigin(windowLength/2, 1);
        horizontalLine->setPosition(windowLength/2, dest);

        this->gridVector->push_back(horizontalLine);
    }


    for(int j = 0; j <= this->nGrid_size; j++){

        //Calculate dest
        int dest = j * this->sq_x;

        sf::Vector2f size(windowHeight, 2);
        sf::RectangleShape *verticalLine = new sf::RectangleShape(size);
        verticalLine->setOrigin(windowHeight/2, 1);
        verticalLine->setRotation(90);

        verticalLine->setPosition(dest, windowLength/2);

        this->gridVector->push_back(verticalLine);
    }


}

void Canvas::updateCanvas(sf::RenderWindow *window) {

    for(int i = 0; i < this->gridVector->size(); i++){
        window->draw(*gridVector->at(i));
    }

    for(int i = 0; i < tileBoard->size(); i++){
        tileBoard->at(i)->pixelUpdate();
        window->draw(tileBoard->at(i)->getPixel());
    }
}

//Returns the rectangular subset of the main grid that is encompassed by the diagonal

std::vector<sf::Vector2f*>* Canvas::generateSet(sf::Vector2f &initPos, sf::Vector2f &destPos) {
    sf::Vector2f newInit = getClosestSquare(initPos);
    sf::Vector2f newDest = getClosestSquare(destPos);

    std::vector<sf::Vector2f*>* selectSubset = new std::vector<sf::Vector2f*>;

    float minX;
    float maxX;

    float minY;
    float maxY;

    //Determine the max and min values for the square Range
    if(newInit.x > newDest.y){
        minX = newDest.x;
        maxX = newInit.x;
    }
    else{
        maxX = newDest.x;
        minX = newInit.x;
    }

    if(newInit.y > newDest.y){
        minY = newDest.y;
        maxY = newInit.y;
    }
    else{
        minY = newInit.y;
        maxY = newDest.y;
    }

    for(int i = 0; i <=  (maxY - minY)/sq_y; i++){
        for(int j = 0; j <= (maxX - minX)/sq_x; j++) {


            sf::Vector2f *newVectPos1 = new sf::Vector2f;
            newVectPos1->x = minX + ((float)j * sq_x);
            newVectPos1->y = minY + ((float)i * sq_y);

            selectSubset->push_back(newVectPos1);

        }
    }

    return selectSubset;
}




sf::Vector2f& Canvas::getRectSize() const{
    sf::Vector2f rectSize(sq_x, sq_y);
    return rectSize;
}


Textile* Canvas::getTextileFromPos(sf::Vector2f *omar){
    sf::Vector2f nPos = this->getClosestSquare(*omar);
    pair<int, int> posPair((int)nPos.x, (int)nPos.y);
    if(this->tileMap.find(posPair) != this->tileMap.end()){
        return this->tileMap[posPair];
    }
    else
        cout<<"Tile not Found"<<endl;
        return nullptr;


}

sf::Vector2f& Canvas::getSquDim() {
    sf::Vector2f *omar = new sf::Vector2f;
    omar->x = this->sq_x;
    omar->y = this->sq_y;
    return *omar;
}





