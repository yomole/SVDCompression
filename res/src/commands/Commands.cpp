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
            cout    << "compress [Size][K/k/M/m/B/b] [file format]"
                    << endl
                    << "\tRuns the compression algorithms on the files in the program file list until we reach the "
                       "target file size and then exports the compressed images."
                    << endl
                    << "\tFile sizes can be in bytes, kilobytes, or megabytes."
                    << endl
                    << "\tValid file extensions include: \".jpg\", \".png\", \".bmp\", and \".tga\"."
                    << endl;
            break;
        }

        case CONVERT:{
            cout    << "convert \"[Original File]\" [file format]"
                    << endl
                    << "\tConverts the image file into another file format."
                    << endl
                    << "\tValid file extensions include: \".jpg\", \".png\", \".bmp\", and \".tga\"."
                    << endl;
            break;
        }

        case DECOMPRESS:{
            cout    << "decompress \"[bin file]\" \"[new file location]\""
                    << endl
                    << "\tRuns the decompression function for Huffman Encoding."
                    << endl
                    << "\tNOTE: Include the file extension in the new file location!"
                    << endl
                    << "\tValid file extensions include: \".jpg\", \".png\", \".bmp\", and \".tga\"."
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
            cout    << "ls [-c]"
                    << endl
                    << "\tLists all of the files on the file list. Use with \"-c\" to list the compressed files."
                    << endl;
            break;
        }

        case HELP:{
            cout    << "help [command/all]"
                    << endl
                    << "\tDisplays information about a command and its arguments. Use \"all\" to get a list of all the "
                       "commands available."
                    << endl;
            break;
        }

        case SHOW:{
            cout    << "show \"[File Location/all]\""
                    << endl
                    << "\tDisplays the specified image. Use \"all\" to display all compressed and original images in the"
                       " program."
                    << endl;
            break;
        }

    }
}

void listCommands(){
    cout << "Commands available in SVDCompression:" << endl;
    for (unsigned int i = 0; i < ALL; i++){
        cout <<"- ";
        getHelp(i);
        cout << endl;
    }
}
