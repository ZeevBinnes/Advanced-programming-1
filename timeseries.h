/*
 * timeseries.h
 *
 * Author: 313361560 Shahar Rapp, 205866163 Ze'ev Binnes.
 */

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <string>
#include <vector>
#include <map>



using namespace std;

class TimeSeries{
    vector<string> features;
    vector<vector<float>> times;
public:

	TimeSeries(const char* CSVfileName);
    vector<float> getColumn(int index) const;
	vector<float> getRow(int index) const;
	string getHeadLine(int index) const;	// get the features name
	int getSize() const;	// get the number of columns
	int getLength() const;	// get the number of rows
	int getFeaturesIndex(string name) const;	// get the index of a feature given by name
	long getTime(int index) const;	// get the time of the row in index "index"
    void readCSV(const char* CSVfileName);


};



#endif /* TIMESERIES_H_ */
