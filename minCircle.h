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

// you may add helper functions here


#endif //SMALLESTCIRCLEPROBLEM_MINCIRCLE_H
