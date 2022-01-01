#include "CLI.h"

CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
    this->commands.push_back(new UploadCommand(dio));
    this->commands.push_back(new AlgSettingsCommand(dio));
    this->commands.push_back(new DetectCommand(dio));
    this->commands.push_back(new DisplayResultsCommand(dio));
    this->commands.push_back(new UploadAndAnalyzeCommand(dio));
    this->commands.push_back(new ExitCommand(dio));
}

void CLI::start(){
    while (true) {
        CLI::printMenu();
        int option;
        // maybe add try - catch!!!!!!!!!!!!!!!!!
        std::cin >> option;
        if (option == 6) {
            break;
        }
//        if (isValidOption(option))
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

//bool isValidOption(int option) {
//    return (option > 0 && option <= 6);
//}


CLI::~CLI() {
    this->commands.clear();
}

