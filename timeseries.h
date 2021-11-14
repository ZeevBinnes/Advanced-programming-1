

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <string>
#include <vector>

using namespace std;

class TimeSeries{

public:

	TimeSeries(const char* CSVfileName){
	}

	float* getColumn(int index) const;
	vector<float> getRow(int index) const;
	string getHeadLine(int index) const;	// get the features name
	int getSize() const;	// get the number of columns
	int getLength() const;	// get the number of rows
	int getFeaturesIndex(string name) const;	// get the index of a feature given by name
	long getTime(int index) const;	// get the time of the row in index "index"

};



#endif /* TIMESERIES_H_ */
