#include "Commands.h"

void getHelp(int command){
    switch(command){
        case ADD:{
            cout    << "add \"[File Location]\""
                    << endl
                    << "\tAdds a file to the program file list. Any file on the file list will be processed."
                    << endl;
            break;
        }
        case DEL:{
            cout    << "del \"[File Location]\""
                    << endl
                    << "\tRemoves a file from the program file list. Any file not on the file list will not be processed."
                    << endl;
            break;
        }
        case HELP:{
            cout    << "help [command]"
                    << endl
                    << "\tDisplays information about a command and its arguments."
                    << endl;
            break;
        }
    }
}

void listCommands(){
    cout << "Unknown command! Here are a list of available commands: " << endl;
    for (unsigned int i = 0; i < ALL; i++){
        cout <<"- ";
        getHelp(i);
    }
}
