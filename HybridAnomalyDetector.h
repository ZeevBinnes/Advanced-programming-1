/*
 * HybridAnomalyDetector.h
 *
 * Author: 313361560 Shahar Rapp, 205866163 Ze'ev Binnes.
 */

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
	HybridAnomalyDetector();
	virtual ~HybridAnomalyDetector();
protected:
    virtual void find_threshold(struct correlatedFeatures & cf1, vector<float> col1, vector<float> col2);
	virtual float findDeviation(Point point, struct correlatedFeatures cf1);
};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
