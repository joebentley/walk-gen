#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "Vector.h"

class Rectangle {
public:
    Rectangle() : position(TwoVector(0, 0)), dimensions(TwoVector(0, 0)) { }
    Rectangle(int x, int y, int width, int height)
        : position(TwoVector(x, y)), dimensions(TwoVector(width, height)) { }

    int getX() { return position.getX(); }
    int getY() { return position.getY(); }
    void setX(int x) { position.setX(x); }
    void setY(int y) { position.setY(y); }

    TwoVector getPosition() { return position; }
    void setPosition(TwoVector position) { this->position = position; }

    int getWidth() { return dimensions.getX(); }
    int getHeight() { return dimensions.getY(); }
    void setWidth(int width) { dimensions.setX(width); }
    void setHeight(int height) { dimensions.setY(height); }

    TwoVector getDimensions() { return dimensions; }
    void setDimensions(TwoVector dimensions) { this->dimensions = dimensions; }

    TwoVector position;
    TwoVector dimensions;
};

#endif /* RECTANGLE_H_ */
