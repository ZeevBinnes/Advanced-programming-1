
#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
}

/*
This function will iterate trough a time series table,
find pair of correlated features, and add them to the list of correlated fatures,
which is a member of the "SimpleAnomalyDetector" Class.
*/
void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
    // Iterate through the columns.
    for (int i = 0; i < ts.getSize(); i++) {
        int maxPearson = 0;      // the pearson with the most matching column.
        int c = -1;     // will save the matching column.
        float* col1 = ts.getColumn(i);
        // check the next columns, and choose the one that has the best match.
        for (int j = i + 1; j < ts.getSize(); j++) {
            float* col2 = ts.getColumn(j);
            float p = std::fabs(pearson(col1, col2, ts.getLength()));
            if (p > maxPearson) {
                maxPearson = p;  // save the best pearson.
                c = j;  // save the best match.
            }
        }
        // If any match was found, save the best one to the correlated features list.
        if (c != -1) {
            float* col2 = ts.getColumn(c);
            struct correlatedFeatures cf1;
            cf1.feature1 = ts.getHeadLine(i);
            cf1.feature2 = ts.getHeadLine(c);
            cf1.corrlation = maxPearson;
            cf1.lin_reg = linear_reg(col1, col2, ts.getLength());   // !!!!! I added a new function to util, to prevent double work.
            cf1.max_offset = 0;
            // Find the max offset from the line.
            for (int k = 0; k < ts.getLength(); k++) {
                float d = dev(Point(col1[k], col2[k]), cf1.lin_reg);    // !!!!!!! check if the function has to be const.
                if (d > cf1.max_offset) {
                    cf1.max_offset = d;
                }
            }
            cf1.max_offset = 1.1 * cf1.max_offset;  // allow a small deviation.
            this->cf.push_back(cf1);    // add the pair to the list of correlated features.
        }
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
}

