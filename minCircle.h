// 309288777
//
// Created by eliel on 26/11/2020.
//

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
//    x = fabs(ax - bx);
//    y = fabs(ay - by);

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
    radius = calcDistance(a, b); // diameter
    radius /= 2; // radius

    Circle c(center, radius);

    return c;
}

// returns the center point of a circle, given 2 points.
Point getCenterOfCircle(Point a, Point b) {

    float c, d, e;

    c = pow(a.x, 2) + pow(a.y, 2);
    d = pow(b.x, 2) + pow(b.y, 2);
    e = a.x * b.y - a.y * b.x;

    return {(b.y * c - a.y * d) / (2 * e), (a.x * d - b.x * c) / (2 *e)};
}

// returns the center point of a circle, given 4 floats
Point getCenterOfCircle(float bx, float by, float cx, float cy) {

    float b, c, d;

    b = pow(bx, 2) + pow(by, 2);
    c = pow(cx, 2) + pow(cy, 2);
    d = (bx * cy) - (by * cx);

    return {(cy * b - by * c) / (2 * d), (bx * c - cx * b) / (2 * d)};
}

Circle threePointsCircle(Point a, Point b, Point c) {
    Point center = getCenterOfCircle(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
    center.x += a.x;
    center.y += a.y;
    return {center, calcDistance(center, a)};
}

// checks if a given point is inside a certain circle.
bool isInside(Circle c, Point a) {
    return calcDistance(c.center, a) <= c.radius;
}

// functions to check if all points are inside the circle.
bool isValid(Circle c, Point** points) {
    for(int i = 0; i < 250; i++) {
        if(!isInside(c, Point(points[i]->x, points[i]->y))) return false;
    }
    return true;
}

// return a minimum circle that enclose all points in 2D plane.
Circle findMinCircle(Point** points,size_t size) {

    // trivial mec- minimum enclosing circle.
    if(size == 0) return {{0, 0}, 0};
    if(size == 1) return {Point(points[0]->x, points[0]->y), 0};
    if(size == 2) return createTwoPointCircle(Point(points[0]->x, points[0]->y),
                                              Point(points[1]->x, points[1]->y));

    // if the number of the points are 4 or more, set a circle from the first 3 points.
    // every boundary point is on the circle and not inside.
    Point boundary1(points[0]->x, points[0]->y);
    Point boundary2(points[1]->x, points[1]->y);
    Point boundary3(points[2]->x, points[2]->y);

    Circle mecOfThreePoints = threePointsCircle(boundary1, boundary2, boundary3);

    for(int i = 4; i < size; i++) {

        Point p(points[i]->x, points[i]->y);

        // check if point is inside circle, if not, enter.
        if(!isInside(mecOfThreePoints, p)) {

            // check distances between the current point to the boundaries points.
            float distPTob1 = calcDistance(p, boundary1);
            float distPTob2 = calcDistance(p, boundary2);
            float distPTob3 = calcDistance(p, boundary3);

            // b1 is the furthest.
            if(distPTob2 < distPTob1 && distPTob3 < distPTob1) {
                if(distPTob2 < distPTob3) {
                    boundary3 = p; // b1, b2, p
                    //boundary3 = {points[i]->x, points[i]->y}; // b1, b2, p
                }
                if(distPTob3 < distPTob2) {
                    boundary2 = p; // b1, p, b3
                }
            }

            // b2 is the furthest.
            if(distPTob1 < distPTob2 && distPTob3 < distPTob2) {
                if(distPTob3 < distPTob1) {
                    boundary1 = p; // b1, b2, p
                }
                if(distPTob1 < distPTob3) {
                    boundary3 = p; // p, b2, b3
                }
            }

            // b3 is the furthest.
            if(distPTob1 < distPTob3 && distPTob2 < distPTob3) {
                if(distPTob1 < distPTob2) {
                    boundary2 = p; // p, b2, b3
                }
                if(distPTob2 < distPTob1) {
                    boundary1 = p; // b1, p, b3
                }
            }
        }
        mecOfThreePoints = threePointsCircle(boundary1, boundary2, boundary3);
    }

    return mecOfThreePoints;
}

#endif //SMALLESTCIRCLEPROBLEM_MINCIRCLE_H
