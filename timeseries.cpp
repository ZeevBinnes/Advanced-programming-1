/*
 * timeseries.cpp
 *
 * Author: 313361560 Shahar Rapp, 205866163 Ze'ev Binnes.
 */

#include "timeseries.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;


TimeSeries::TimeSeries (const char *CSVfileName){
    fstream csv;
    csv.open(CSVfileName);
    // check if file is operable
    if(!csv.is_open()) {
        cout << "Failed to open file" << endl;
        return;
    }
    // get features
    string line;
    string feature;
    getline(csv, line);
    stringstream first(line);
    while(getline(first, feature, ',')){
        this->features.push_back(feature);
    }
    // get samples
    while(getline(csv, line)){
        string x;
        vector<float> time;
        stringstream row(line);
        while(getline(row, x, ',')){
            time.push_back(stof(x));
        }
        this->times.push_back(time);
    }
}


vector<float> TimeSeries::getColumn(int index) const{
    vector<float> column;
    for (int i = 0; i < this->times.size(); i++){
        column.push_back(times[i][index]);
    }
    return column;
}

vector<float> TimeSeries::getRow(int index) const{
    return times[index];
}

string TimeSeries::getHeadLine(int index) const{
    return features[index];
}
// get the number of columns
int TimeSeries::getSize() const{
    return features.size();
}
// get the number of rows
int TimeSeries::getLength() const{
    return times.size();
}
// get the index of a feature given by name (return -1 if there isnt)
int TimeSeries::getFeaturesIndex(const string name) const{
    for (int i = 0; i < features.size(); i++){
        if(features[i].compare(name) == 0){
            return i;
        }
    }
    cout << "No such feature" << endl;
    return -1;
}
// get the time of the row in index "index"
long TimeSeries::getTime(int index) const{
    return times[index][0];
}