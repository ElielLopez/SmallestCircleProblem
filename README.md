# SmallestCircleProblem

## Finding the smallest circle enclosing all points in plane.

Given points in 2D plane (x, y), this algorithm finds the smallest circle
enclosing all the points in the plane.
meaning, the points are inside the enclosing circle or on it.

using functions to calculate distance and middle of a line to create a circle, composed by 2 points.
to help find the MEC, i use 2 ohter functions.
the first function checks if a certain point is inside a specific circle by checking the distance from the center of the circle.
the second function checks the validity of MEC by checking if all pointa are inside it.

the main goal is to find the MEC in O(n) time.
I used 2 loops so in theory the running time is O(n^2).
inserting 2 conditionals help reduce the time to 40+- ms for 250 given points.

### MEC- minimum enclosing circle
