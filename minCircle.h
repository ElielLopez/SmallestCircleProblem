// 309288777
//
// Created by eliel on 26/11/2020.
//

#ifndef SMALLESTCIRCLEPROBLEM_MINCIRCLE_H
#define SMALLESTCIRCLEPROBLEM_MINCIRCLE_H

#include <iostream>

using namespace std;

// ------------ DO NOT CHANGE -----------
class Point{
public:
    float x,y;
    Point(float x,float y):x(x),y(y){}
};

class Circle{
public:
    Point center;
    float radius;
    Circle(Point c,float r):center(c),radius(r){}
};
// --------------------------------------

// implement
Circle findMinCircle(Point** points,size_t size){
    return Circle(Point(0,0),0);
}

// return the middle point by equation: x = (x1-x2) / 2, y = (y1-y2) / 2.
Point calcMiddle(Point a, Point b) {

    float ax, ay;
    float bx, by;
    float x, y;

    ax = a.x;
    ay = a.y;
    bx = b.x;
    by = b.y;

    x = (ax + bx) / 2;
    y = (ay + by) / 2;

    Point middle(x, y);

    return middle;
}

// return the distance between two point by the equation:
// D = sqrt((x1-x2)^2 + (y1-y2)^2)
float calcDistance(Point a, Point b) {

    float distance;
    float ax, ay;
    float bx, by;
    float x, y;

    ax = a.x;
    ay = a.y;
    bx = b.x;
    by = b.y;

    x = ax - bx;
    y = ay - by;

    x = pow(x, 2);
    y = pow(y, 2);

    distance = x + y;
    distance = sqrtf(distance);

    return distance;
}

// checks if a given point is outside the current circle.
bool isBigger(Point center, Point a, float radius) {

    float dist;
    bool isBiggerThenR = false;

    dist = calcDistance(center, a);
    if(radius < dist) isBiggerThenR = true;

    return isBiggerThenR;

}

// given two points, calculate the center point and the radius and creates a small circle
// that the two points are on the circle
Circle createTwoPointCircle(Point a, Point b) {

    float radius;

    auto center = calcMiddle(a, b);
    radius = calcDistance(a, b);
    radius /= 2;

    //Point center(x, y);
    Circle c(center, radius);
    return c;
}




#endif //SMALLESTCIRCLEPROBLEM_MINCIRCLE_H
