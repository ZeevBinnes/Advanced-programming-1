/*
 * commands.h
 *
 * Author: 313361560 Shahar Rapp, 205866163 Ze'ev Binnes.
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO{
public:
	virtual string read()=0;
	virtual void write(string text)=0;
	virtual void write(float f)=0;
	virtual void read(float* f)=0;
	virtual ~DefaultIO(){}

	// you may add additional methods here
	void createCSV(std::string fileName) {
		ofstream file(fileName);
		std::string line = read();
		while (line.compare("done") != 0) {
			file << line << std::endl;
			line = read();
		}
		write("Upload complete.\n");
	}
};

class StandardIO : public DefaultIO {
public:
	virtual string read() {
		std::string input;
		std::cin >> input;
		return input;
	}
	virtual void write(string text) {
		std::cout << text;
	}
	virtual void write(float f) {
		std::cout << f;
	}
	virtual void read(float* f) {
		std::cin >> *f;
	}
};

// you may add here helper classes

// instead of AnomalyReport, because I can't change it's defaults.
class Report {
public:
	string description;
	long timeStep;
	Report(string description, long timeStep):description(description),timeStep(timeStep){}
};

class TimeInterval {
public:
	long start;
	long end;
	TimeInterval(long s, long e) : start(s), end(e) {}
};

// holds data and detector for use of all commands.
class DetectorData {
private:
	HybridAnomalyDetector ad = HybridAnomalyDetector();
	float correlation = ad.getThreshold();
public:
	vector<Report> reports;
	long numOfLinesTest;
	DetectorData() {}

	// help commands call AnomalyDetector methods
	void anomalyTrain(const char* fileName) {
		TimeSeries tsTrain = TimeSeries(fileName);
		ad.learnNormal(tsTrain);
	}
	void anomalyTest(const char* fileName) {
		TimeSeries tsTest = TimeSeries(fileName);
		numOfLinesTest = tsTest.getLength();
		std::vector<AnomalyReport> reportsFromAd = ad.detect(tsTest);
		reports.clear();
		for (auto a : reportsFromAd) {
			reports.push_back(Report(a.description, a.timeStep));
		}
	}
	// get and set the algorithm's correlation threshold.
	float getCorrelation() {return correlation;}
	void setCorrelation(float newCor) {
		ad.setThreshold(newCor);
		correlation = newCor;
	}
	// get anomaly time intervals from the report.
	vector<TimeInterval>* getAlgTimeIntervals() {
		vector<TimeInterval>* timeIntervalP = new vector<TimeInterval>;
		map<string, vector<long>> timesPerDescription;
		for (Report r : reports) {
			vector<long> v;
			timesPerDescription.insert({r.description, v});
			timesPerDescription[r.description].push_back(r.timeStep);
		}
		for (auto it = timesPerDescription.begin(); it != timesPerDescription.end(); ++it) {
			sort(it->second.begin(), it->second.end());
			findSeries(timeIntervalP, it->second);
		}
		return timeIntervalP;
	}
	~DetectorData(){
		reports.clear();
	}

private:
	// help getAlgTimeIntervals().
	void findSeries(vector<TimeInterval>* ti, vector<long> vl) {
		long start = vl[0]; long end = start;
		for (long l : vl) {
			if (l == end)
				++ end;
			else {
				TimeInterval t = TimeInterval(start,end-1);
				ti->push_back(t);
				start = l;
				end = start + 1;
			}
		}
		TimeInterval t = TimeInterval(start,end-1);
		ti->push_back(t);
	}
};

// you may edit this class
class Command{
protected:
	DefaultIO* dio;
	DetectorData* dd;
public:
	Command(DefaultIO* dio, DetectorData* dd):dio(dio),dd(dd) {}
	virtual void execute()=0;
	virtual ~Command(){}
	virtual void print_description() {
		this->dio->write(description());
	}
	virtual std::string description()=0;
};

// implement here your command classes

class UploadCommand : public Command {
public:
	UploadCommand(DefaultIO* dio, DetectorData* dd) : Command(dio,dd) {}
	virtual std::string description() {return "1.upload a time series csv file\n";}
	virtual void execute() {
		std::string fileNames[] = {"anomalyTrain.csv", "anomalyTest.csv"};
		std::string instruction[] = {"Please upload your local train CSV file.\n",
			"Please upload your local test CSV file.\n"};
		std::string line;
		for (int i = 0; i <= 1; ++i) {
			dio->write(instruction[i]);
			dio->createCSV(fileNames[i]);
		}
	}
};

class AlgSettingsCommand : public Command {
public:
	AlgSettingsCommand(DefaultIO* dio, DetectorData* dd) : Command(dio,dd) {}
	virtual std::string description() {return "2.algorithm settings\n";}
	virtual void execute() {
		float newCor;
		float currentCor = this->dd->getCorrelation();
		dio->write("The current correlation threshold is ");
		dio->write(currentCor);
		dio->write("\n");
		dio->write("Type a new threshold\n");
		dio->read(&newCor);
		while (newCor < 0 || newCor > 1) {
			dio->write("please choose a value between 0 and 1.\n");
			dio->read(&newCor);
		}
		this->dd->setCorrelation(newCor);
	}
};

class DetectCommand : public Command {
public:
	DetectCommand(DefaultIO* dio, DetectorData* dd) : Command(dio,dd) {}
	virtual std::string description() {return "3.detect anomalies\n";}
	virtual void execute() {
		dd->anomalyTrain("anomalyTrain.csv");
		dd->anomalyTest("anomalyTest.csv");
		dio->write("anomaly detection complete.\n");
	}
};


class DisplayResultsCommand : public Command {
public:
	DisplayResultsCommand(DefaultIO* dio, DetectorData* dd) : Command(dio,dd) {}
	virtual std::string description() {return "4.display results\n";}
	virtual void execute() {
		for (Report r : dd->reports) {
			dio->write(to_string(r.timeStep) + "\t" + r.description + "\n");
		}
		dio->write("Done.\n");
	}
};

class UploadAndAnalyzeCommand : public Command {
public:
	UploadAndAnalyzeCommand(DefaultIO* dio, DetectorData* dd) : Command(dio,dd) {}
	virtual std::string description() {return "5.upload anomalies and analyze results\n";}
	virtual void execute() {
		vector<TimeInterval> times = getInputTimes();
		float p = (float)times.size();
		int fp=0, tp=0;
		long totalNumOfLines = dd->numOfLinesTest;
		long numOfBadTimeSteps = 0;
		for (TimeInterval t : times) {
			numOfBadTimeSteps += (t.end-t.start+1);
		}
		vector<TimeInterval>* algTimes = dd->getAlgTimeIntervals();
		// count the true and false positive alerts.
		bool tpFlag = false;
		for (TimeInterval fromAlg : *algTimes) {
			tpFlag = false;
			for (TimeInterval fromClient : times) {
				if (fromAlg.start <= fromClient.end &&
						fromAlg.end >= fromClient.start) {
					++tp;
					tpFlag = true;
					break;
				}
			}
			if (!tpFlag)
				++fp;
		}
		// compute rate and send to output.
		float truePositiveRate = (float)tp / (float)p;
		float falsePositiveRate = (float)fp / (float)(totalNumOfLines - numOfBadTimeSteps);
		truePositiveRate = floor(truePositiveRate * 1000) / 1000;
		falsePositiveRate = floor(falsePositiveRate * 1000) / 1000;
		dio->write("True Positive Rate: ");
		dio->write(truePositiveRate);
		dio->write("\n");
		dio->write("False Positive Rate: ");
		dio->write(falsePositiveRate);
		dio->write("\n");
		times.clear();
		algTimes->clear();
		delete algTimes;
	}
private:
	vector<TimeInterval> getInputTimes() {
		dio->write("Please upload your local anomalies file.\n");
		std::string line = dio->read();
		std::string x;
		vector<long> time;
		vector<TimeInterval> times;
		while (line.compare("done") != 0) {
			std::stringstream splitting(line);
			while(getline(splitting, x, ',')) {
				time.push_back(stol(x));
			}
			TimeInterval t = TimeInterval(time[0], time[1]);
			times.push_back(t);
			time.clear();
			line = dio->read();
		}
		dio->write("Upload complete.\n");
		return times;
	}
};

class ExitCommand : public Command {
public:
	ExitCommand(DefaultIO* dio, DetectorData* dd) : Command(dio,dd) {}
	virtual std::string description() {return "6.exit\n";}
	virtual void execute() {
	}
};


#endif /* COMMANDS_H_ */
