/*
 * minCircle.cpp
 *
 * Author: 313361560 Shahar Rapp, 205866163 Ze'ev Binnes.
 */
#include "minCircle.h"
#include <algorithm>
#include <math.h>
#include <vector>
using namespace std;

// Returns a float of the distance between two points
float dist(const Point& a, const Point& b)
{
    return pow(pow(a.x - b.x, 2) + pow(a.y - b.y, 2),0.5);
}

// Returns a boolean if a point is in/on the circle
bool is_inside(const Circle& c, const Point& p)
{
    return dist(c.center, p) <= c.radius;
}

// returns the circle that connect these 3 points
Circle circle_connects(const Point& A, const Point& B,
                   const Point& C)
{
    float a = B.x - A.x;
    float b = B.y - A.y;
    float c = C.x - A.x;
    float d = C.y - A.y;
    float e = a * a + b * b;
    float f = c * c + d * d;
    float g = 2 * (a * d - b * c);

    Point center = {((d * e - b * f) / g) + A.x,((a * f - c * e) / g) + A.y};
    
    return { center, (dist(center, A)) };
}

// returns the circle that connect these 2 points
Circle circle_connects(const Point& A, const Point& B)
{
    Point center = { ((A.x + B.x) / 2), ((A.y + B.y) / 2) };
    
    return { center, (dist(A, B) / 2) };
}

// Returns a boolean if all the points is in the circle
bool is_all_inside(const Circle& c, const vector<Point>& P)
{
    for (const Point& p : P)
        if (!is_inside(c, p))
            return false;
    return true;
}

// Returns the minimum enclosing circle for n <= 3
Circle MEC_3(vector<Point>& P)
{
    if (P.empty()) {
        return { { 0, 0 }, 0 };
    }
    else if (P.size() == 1) {
        return { P[0], 0 };
    }
    else if (P.size() == 2) {
        return circle_connects(P[0], P[1]);
    }
    return circle_connects(P[0], P[1], P[2]);
}

// Returns the MEC using Welzl's algorithm
Circle MEC_welzl(vector<Point>& P,vector<Point> R, int n)
{
    // stop condition
    if (n == 0 || R.size() == 3) {
        return MEC_3(R);
    }

    int i = rand() % n;
    Point p = P[i];
    swap(P[i], P[n - 1]);
    // recursion without p
    Circle c = MEC_welzl(P, R, n - 1);
    if (is_inside(c, p)) {
        return c;
    }

    R.push_back(p);
    return MEC_welzl(P, R, n - 1);
}

// main function to find and returns the minimum enclosing circle
Circle findMinCircle(Point** points,size_t size)
{
    vector<Point> P_copy;
    for (int i = 0; i < size; i++) {
        P_copy.push_back(*points[i]);
    }
    random_shuffle(P_copy.begin(), P_copy.end());
    return MEC_welzl(P_copy, {}, P_copy.size());
}

Circle findMinCircle(vector<Point> points) {
    vector<Point> P_copy;
    for (int i = 0; i < points.size(); i++) {
        P_copy.push_back(points[i]);
    }
    random_shuffle(P_copy.begin(), P_copy.end());
    return MEC_welzl(P_copy, {}, P_copy.size());
}