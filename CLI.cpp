#include "CLI.h"

CLI::CLI(DefaultIO* dio){
    this->dio = dio;
//    HybridAnomalyDetector *ad = new HybridAnomalyDetector();
    this->dd = new DetectorData();
    this->commands.push_back(new UploadCommand(dio, dd));
    this->commands.push_back(new AlgSettingsCommand(dio, dd));
    this->commands.push_back(new DetectCommand(dio, dd));
    this->commands.push_back(new DisplayResultsCommand(dio, dd));
    this->commands.push_back(new UploadAndAnalyzeCommand(dio, dd));
    this->commands.push_back(new ExitCommand(dio, dd));
}

void CLI::start(){
    while (true) {
        CLI::printMenu();
        std:string strOption;
        strOption = dio->read();
        int option;
        try {
            option = std::stoi(strOption);
        } catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }        
//        std::cin >> option;
        if (option == 6) {
            break;
        }
        if (option > 0 && option < 6)
            commands[option - 1]->execute();       
    }
}

void CLI::printMenu() {
    std::string menuStartText = 
        "Welcome to the Anomaly Detection Server.\nPlease choose an option:\n";
    this->dio->write(menuStartText);
    for (auto c : commands) {
        c->print_description();
    }
}


CLI::~CLI() {
    this->commands.clear();
}

