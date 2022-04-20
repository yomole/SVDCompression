#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include <fstream>
#include <csignal>
#include "managers/AssetManager.h"
#include "commands/Commands.h"
#include "python/PythonScript.h"
#include "ui/viewer/ImageViewer.h"

using sf::Event;
using sf::Mouse;
using std::cin;
using std::cout;
using std::string;
using std::getline;
using std::istringstream;
using std::vector;
using std::ifstream;

//FUNCTION PROTOTYPES:
///@brief Checks if a command is valid and is pointing to a target command.
bool isCommand(const string& command, const vector<string>& args, const string& target);

///@brief Parses a line into arguments. Arguments with quotes are read until the ending quote.
void parseArgs(istringstream& parse, vector<string>& args);

///@brief Prints the info contained in the README.md file.
void printAbout();

///@brief Checks the working directory and gets the prefix which ensures we are running in SVDCompression/
string getPrefix();

int main(int argc, char* argv[]) {

    cout << "Starting directory is: " << (getPrefix().empty() ? "SVDCompression\\" : "SVDCompression\\bin") << endl;
    sf::RenderWindow window(sf::VideoMode(0, 0),
                            "Media Compression by iCompression: Qualitative Comparison", sf::Style::Close);
    AssetManager(getPrefix().data());
    window.close();

    //Load the python interpreter to keep it alive for as long as possible.
    scope = new py::scoped_interpreter{};

    cout << "Media Compression by iCompression";

    //Load the command file, if the argument is there.
    ifstream file;
    if (argc == 2) {
        file.open(argv[1]);
        cout << ": Command File Mode";

        //Print out an error followed by cin to make sure the message is seen if the file is not valid.
        if (!file.is_open()){
            cout << endl << "File " << argv[1] << "is not valid!" << endl;
            cout << "Press enter to continue..." << endl;
            string temp;
            getline(cin,temp);
            exit(1);
        }
    }

    cout << endl << endl;

    string line, command;

    //Modified https://www.tutorialspoint.com/how-do-i-catch-a-ctrlplusc-event-in-cplusplus
    signal(SIGINT, [](int signum) -> void { exit(signum); });
    do {
        command = "";
        if (argc == 1) {
            cout << "SVDCompression> ";
            //1. Get the entire line of command.
            getline(cin, line);
        }

        else {
            if (file.is_open()) {
                getline(file, line);

                //If there is a '#' or nothing, then skip the line (is a comment).
                if (line.front() == '#' || line.empty()){
                    continue;
                }
            }

            else {
                cerr << "file at " << argv[1] << " does not exist!";
                exit(1);
            }
        }

        //2. Parse it into command parts.
        istringstream parse(line);
        vector<string> args;
        parse >> command;
        parseArgs(parse, args);

        cout << endl;

        //3. Run the appropriate command.
        if (isCommand(command, args, "add")) {
            if (command == "help" || args.size() != 1) {
                getHelp(ADD);
            }

            else if (args.size() == 1) {
                AssetManager::addFile(args.at(0));
            }
        }

        else if (isCommand(command, args, "addf")) {
            if (command == "help" || args.size() != 1) {
                getHelp(ADDF);
            }

            else if (args.size() == 1) {
                AssetManager::addFolder(args.at(0));
            }
        }

        else if (isCommand(command, args, "rm")) {
            if (command == "help" || args.size() != 1) {
                getHelp(RM);
            }

            else if (args.size() == 1) {
                AssetManager::delFile(args.at(0));
            }
        }

        else if (isCommand(command, args, "rmf")) {
            if (command == "help" || args.size() != 1) {
                getHelp(RMF);
            }

            else if (args.size() == 1) {
                AssetManager::delFolder(args.at(0));
            }
        }

        else if (isCommand(command, args, "ls")) {
            if (command == "help" || args.size() > 1) {
                getHelp(LS);
            }

            else if (args.size() == 1 && args.at(0) == "-c"){
                AssetManager::listFiles(COMPRESSED);
            }

            else{
                AssetManager::listFiles();
            }
        }

        else if (isCommand(command, args, "compress")) {
            if (command == "help" || args.size() != 2) {
                getHelp(COMPRESS);
            }

            else if (args.size() == 2) {
                SVDAlgorithm(AssetManager::getPrefix() + "res/python/SVD.py", args.at(0), args.at(1));
            }
        }

        else if (isCommand(command, args, "show")) {
            if (command == "help" || args.size() != 1) {
                getHelp(SHOW);
            }

            else if (args.size() == 1 && args.at(0) != "all") {
                showImage(args.at(0));
            }

            else{
                showImages();
            }
        }

        else if (isCommand(command, args, "about")) {
            if (command == "help") {
                getHelp(ABOUT);
            }

            else {
                printAbout();
            }
        }

        else if (isCommand(command, args, "help")) {
            if (args.size() == 1 && args.at(0) == "all"){
                listCommands();
            }
            else{
                getHelp(HELP);
            }
        }

        //Display a message indicating that there was a bad command.
        else {
            if (command != "exit") {
                cout << "Invalid Command! Use \"help [command]\" or \"help [all]\" for help with commands." << endl;
            }
        }

        cout << endl;

    } while (command != "exit");

    //Close the python interpreter.
    delete scope;

}

bool isCommand(const string& command, const vector<string>& args, const string& target){
    //1. Check that the command is correct and that
    return ((command == target) || (!args.empty() && args.at(0) == target));
}

void parseArgs(istringstream& parse, vector<string>& args){
    while(!parse.eof()){
        //Load the first part of the string.
        string i, temp;
        parse >> i;

        //If the first character is a quotation mark, keep loading until last character is a quotation mark.
        if (i.front() == '\"'){
            //Remove beginning quotation mark.
            i.erase(0, 1);

            while(i.back() != '\"' && !parse.eof()){
                parse >> temp;
                i += (" " + temp);
            }

            //Remove ending quotation mark.
            i.erase(i.end() - 1);
        }

        args.push_back(i);
    }
}

void printAbout(){
    //1. Get the readme file and pipe to CLI output line by line.
    ifstream file("README.md");

    if (file.is_open()){
        string line;
        while(getline(file, line)){
            cout << line << endl;
        }
    }
    else{
        cerr << "Unable to display information about the program. For information, please go to the github repository.";
    }
}

string getPrefix(){
    //1. Determine the current filepath. If bin, prefix is ../. If it is SVDCompression, it is nothing. Else, error.
    string currDir = fs::current_path().filename().string();

    if (currDir == "bin"){
        return "../";
    }

    else if (currDir == "SVDCompression"){
        return "";
    }

    else{
        cerr << "The executable's location or shortcut working directory is not correct!" << endl;
        exit(1);
    }
}