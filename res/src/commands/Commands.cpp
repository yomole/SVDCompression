#include "Commands.h"

void getHelp(int command){
    switch(command){
        case ABOUT:{
            cout    << "about"
                    << endl
                    << "\tDisplays information about the program along with a list of references."
                    << endl;
            break;
        }

        case ADD:{
            cout    << "add \"[File Location]\""
                    << endl
                    << "\tAdds an image file to the program file list. Any file on the file list will be processed."
                    << endl
                    << "\tValid file extensions include: .jpg, .png, .bmp, and .tga"
                    << endl;
            break;
        }

        case ADDF:{
            cout    << "addf \"[Folder Location]\""
                    << endl
                    << "\tAdds all valid image files in a folder to the program file list."
                    << endl
                    << "\tValid file extensions include: .jpg, .png, .bmp, and .tga"
                    << endl;
            break;
        }

        case COMPRESS:{
            cout    << "compress [Size][K/M]"
                    << endl
                    << "\tRuns the compression algorithms on the files in the program file list until we are at or a "
                       "bit below the target file size."
                    << endl;
            break;
        }

        case RM:{
            cout    << "rm \"[File Location]\""
                    << endl
                    << "\tRemoves an image file from the program file list. Any file not on the file list will not be "
                       "processed."
                    << endl;
            break;
        }

        case RMF:{
            cout    << "rmf \"[Folder Location]\""
                    << endl
                    << "\tRemoves all valid image files in a folder from the program file list."
                    << endl;
            break;
        }

        case LS:{
            cout    << "ls"
                    << endl
                    << "\tLists all of the files on the file list."
                    << endl;
            break;
        }

        case PYTHON:{
            cout    << "python \"[Script Location]\""
                    << endl
                    << "\tRuns a python script from the command line. NOTE: remove upon release!"
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
