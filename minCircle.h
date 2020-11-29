
#ifndef SMALLESTCIRCLEPROBLEM_MINCIRCLE_H
#define SMALLESTCIRCLEPROBLEM_MINCIRCLE_H

#include <iostream>
#include <algorithm>
#include <utility>
#include <math.h>
#include <vector>

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

/*
 * I implemented a naive algorithm that runs at O(n^2) in theory.
 * but in fact runs even less- around 3000ms due to conditions
 * that filters irrelevant points.
 * */
const float INF = 1e18;

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

// given two points, calculate the center point and the radius and creates a small circle
// that the two points are on the circle
Circle createTwoPointCircle(Point a, Point b) {

    float radius;

    auto center = calcMiddle(a, b);
    radius = calcDistance(a, b);
    radius /= 2;

    Circle c(center, radius);

    return c;
}

// checks if a given Point is outside the boundaries of the circle.
bool isInsideCircle(Circle c, Point a) {
    return calcDistance(c.center, a) <= c.radius;
}

// checks if all points are inside the circle. if even a single point is outside- return false.
bool isValidMEC(Circle c, Point** points, size_t size) {
    for(int i = 0; i < size; i++) {
        if(!isInsideCircle(c, Point(points[i]->x, points[i]->y))) return false;
    }
    return true;
}

// return a minimal circle, enclosing all points in 2D plane.
Circle findMinCircle(Point** points,size_t size) {

    // first checks for trivial size of 0,1,2,3.
    if(size == 0) return {{0, 0}, 0};
    if(size == 1) return {Point(points[0]->x, points[0]->y), 0};
    if(size == 2) return createTwoPointCircle(Point(points[0]->x, points[0]->y),
                                              Point(points[1]->x, points[1]->y));

    // default circle.
    Circle mec = {{0, 0}, INF};

    // for every 2 points, create a circle and then check its validity and size.
    // if smaller then the current circle- update it.
    for(int i = 0; i < size; i++) {

        // this condition helps reduce the time significantly
        // because its ignoring points that are inside the circle.
        if(!isInsideCircle(mec, Point(points[i]->x, points[i]->y))) {
            for(int j = i + 1; j < size; j++) {

                if(!isInsideCircle(mec, Point(points[j]->x, points[j]->y))) {
                    Circle tmp = createTwoPointCircle(Point(points[i]->x, points[i]->y),
                                                      Point(points[j]->x, points[j]->y));
                    if(tmp.radius < mec.radius && isValidMEC(tmp, points, size)) {
                        mec = tmp;
                    }
                }
            }
        }
    }

    return mec;
}


#endif //SMALLESTCIRCLEPROBLEM_MINCIRCLE_H
