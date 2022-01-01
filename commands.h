

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
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


// you may edit this class
class Command{
protected:
	DefaultIO* dio;
public:
	Command(DefaultIO* dio):dio(dio){}
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
	UploadCommand(DefaultIO* dio) : Command(dio) {}
	virtual std::string description() {return "1. upload a time series csv file\n";}
	virtual void execute() {
		std::string fileNames[] = {"anomalyTrain.csv", "anomalyTest.csv"};
		std::string instruction[] = {"Please upload your local train CSV file.\n",
			"Please upload your local test CSV file.\n"};
		std::string line;
		for (int i = 0; i <= 1; ++i) {
			ofstream file(fileNames[i]);
			dio->write(instruction[i]);
			line = dio->read();
			while (!line.compare("done") == 0) {
				file << line << std::endl;
				line = dio->read();
			}
			dio->write("Upload complete.\n");
		}
	}
};

class AlgSettingsCommand : public Command {
public:
	AlgSettingsCommand(DefaultIO* dio) : Command(dio) {}
	virtual std::string description() {return "2. algorithm settings\n";}
	virtual void execute() {
	}
};

class DetectCommand : public Command {
public:
	DetectCommand(DefaultIO* dio) : Command(dio) {}
	virtual std::string description() {return "3. detect anomalies\n";}
	virtual void execute() {
	}
};


class DisplayResultsCommand : public Command {
public:
	DisplayResultsCommand(DefaultIO* dio) : Command(dio) {}
	virtual std::string description() {return "4. display results\n";}
	virtual void execute() {
	}
};

class UploadAndAnalyzeCommand : public Command {
public:
	UploadAndAnalyzeCommand(DefaultIO* dio) : Command(dio) {}
	virtual std::string description() {return "5. upload anomalies and analyze results\n";}
	virtual void execute() {
	}
};

class ExitCommand : public Command {
public:
	ExitCommand(DefaultIO* dio) : Command(dio) {}
	virtual std::string description() {return "6. exit\n";}
	virtual void execute() {
	}
};


#endif /* COMMANDS_H_ */
