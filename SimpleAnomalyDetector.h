/*
 * SimpleAnomalyDetector.h
 *
 * Author: 313361560 Shahar Rapp, 205866163 Ze'ev Binnes.
 */

#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>

struct correlatedFeatures{
	string feature1,feature2;  // names of the correlated features
	float corrlation;
	Line lin_reg;
	float threshold;	// the largest deviation of a point from the line
	Point circleCenter = Point(0,0);
};


class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
	vector<correlatedFeatures> cf;
public:
	SimpleAnomalyDetector();
	virtual ~SimpleAnomalyDetector();

	virtual void learnNormal(const TimeSeries& ts);
	virtual vector<AnomalyReport> detect(const TimeSeries& ts);

	vector<correlatedFeatures> getNormalModel(){
		return cf;
	}
protected:
	virtual void find_threshold(struct correlatedFeatures & cf1, vector<float> col1, vector<float> col2);
	virtual float findDeviation(Point point, struct correlatedFeatures cf1);

};



#endif /* SIMPLEANOMALYDETECTOR_H_ */
