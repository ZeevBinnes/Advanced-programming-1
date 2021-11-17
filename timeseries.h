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
    vector<string> features; // names of columns
    vector<vector<float>> times; // time samples of every features

public:
	TimeSeries(const char* CSVfileName); // TimeSeries constructor accept only CSV file ant build a vectors object
    virtual ~TimeSeries(); // virtual destructor
    vector<float> getColumn(int index) const; // return the vector of all samples from one feature
	vector<float> getRow(int index) const; // // return the vector of all samples from one time
	string getHeadLine(int index) const;	// get the features name
	int getSize() const;	// get the number of columns
	int getLength() const;	// get the number of rows
	int getFeaturesIndex(string name) const;	// get the index of a feature given by name (return -1 if there isnt)
	long getTime(int index) const;	// get the time of the row in index "index"
};

#endif /* TIMESERIES_H_ */
