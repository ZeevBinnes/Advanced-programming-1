

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <string>

using namespace std;

class TimeSeries{

public:

	TimeSeries(const char* CSVfileName){
	}

	float* getColumn(int index) const;
	string getHeadLine(int index) const;	// get the features name
	int getSize() const;	// get the number of columns
	int getLength() const;	// get the number of rows

};



#endif /* TIMESERIES_H_ */
