/*
 * HybridAnomalyDetector.cpp
 *
 * Author: 313361560 Shahar Rapp, 205866163 Ze'ev Binnes.
 */

#include "HybridAnomalyDetector.h"
#include <math.h>

void HybridAnomalyDetector::find_threshold(struct correlatedFeatures & cf1, vector<float> col1, vector<float> col2) {
    if (cf1.corrlation >= this->getThreshold()) {
        SimpleAnomalyDetector::find_threshold(cf1, col1, col2);
        return;
    } else if (cf1.corrlation >= 0.5) {
        vector<Point> pointVect;
        for (int k = 0; k < col1.size(); k++) {
            pointVect.push_back(Point(col1[k], col2[k]));
        }
        Circle c = findMinCircle(pointVect);
        cf1.threshold = c.radius;
        cf1.circleCenter = c.center;
    }
}

float HybridAnomalyDetector::findDeviation(Point point, struct correlatedFeatures cf1) {
    if (cf1.corrlation >= this->getThreshold())
        return SimpleAnomalyDetector::findDeviation(point, cf1);
    return sqrt(pow((point.x - cf1.circleCenter.x),2) +
                pow((point.y - cf1.circleCenter.y),2));
}

HybridAnomalyDetector::HybridAnomalyDetector(){
}

HybridAnomalyDetector::~HybridAnomalyDetector(){
}