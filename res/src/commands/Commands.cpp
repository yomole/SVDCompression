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
                    << endl
                    << "\tNOTE: On windows, the filesystem is case-insensitive. Make sure that you type the right "
                       "image name!"
                    << endl;
            break;
        }

        case ADDF:{
            cout    << "addf \"[Folder Location]\""
                    << endl
                    << "\tAdds all valid image files in a folder to the program file list."
                    << endl
                    << "\tValid file extensions include: .jpg, .png, .bmp, and .tga"
                    << endl
                    << "\tNOTE: On windows, the filesystem is case-insensitive. Make sure that you type the right "
                       "directory name!"
                    << endl;
            break;
        }

        case COMPRESS:{
            cout    << "compress [Size][K/k/M/m/B/b]"
                    << endl
                    << "\tRuns the compression algorithms on the files in the program file list until we are at or a "
                       "bit below the target file size. File sizes can be in bytes, kilobytes, and megabytyes."
                    << endl;
            break;
        }

        case RM:{
            cout    << "rm \"[File Location]\""
                    << endl
                    << "\tRemoves an image file from the program file list. Any file not on the file list will not be "
                       "processed."
                    << endl
                    << "\tNOTE: On windows, the filesystem is case-insensitive. Make sure that you type the right "
                       "image name!"
                    << endl;
            break;
        }

        case RMF:{
            cout    << "rmf \"[Folder Location]\""
                    << endl
                    << "\tRemoves all valid image files in a folder from the program file list."
                    << endl
                    << "\tNOTE: On windows, the filesystem is case-insensitive. Make sure that you type the right "
                       "directory name!"
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

        case HELP:{
            cout    << "help [command]"
                    << endl
                    << "\tDisplays information about a command and its arguments."
                    << endl;
            break;
        }

        case EXPORT:{
            cout    << "export [image name] [file format]"
                    << endl
                    << "\tExports a compressed file to the output folder in the specified valid file format "
                       "(without the period)."
                    << endl
                    << "\tValid file formats include: jpg, png, tga, bmp."
                    << endl
                    << "\tNOTE: You can use \"*\" instead to export all files currently in the compressed files list"
                    << endl;
            break;
        }

        case SHOW:{
            cout    << "show \"[File Location]\""
                    << endl
                    << "\tDisplays the specified image."
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
        cout << endl;
    }
}
