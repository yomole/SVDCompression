#include "PythonScript.h"

//References for Pybind implementation can be found on README.md.
//Literally all of them were used, and some code snippets were modified to suit our implementation
//(I'm never embedding Python ever again ;_; ).

void SVDAlgorithm(const string &size, set<string> &files, const string& scriptLocation){
    unsigned long long sizeNum = 0;

    //1. Try to convert the target size to bytes.
    if (!sizeToBytes(size, sizeNum)){
        return;
    }
    else if (sizeNum == 0){
        cerr << "Compression target size cannot be 0!" << endl;
        return;
    }

    //Check if the files list is empty when we first run the program.
    else if (files.empty()){
        cerr << "There are no files in the file list!" << endl;
        return;
    }

    //Remove files from the file list that are smaller than the cutoff size.
    removeBadSizes(sizeNum, files);

    //Check if the file list is empty after we remove those that are smaller than the target.
    if (files.empty()) {
        cerr << "There are no files in the file list!" << endl;
        return;
    }

    //1. Check if the script file exists.
    if (exists(scriptLocation)) {
        auto global = py::dict();
        auto local = py::dict();

        //2. Import global used in python file.
        //equivalent to import struct.
        py::module_ structMod = py::module_::import("struct");
        global["struct"] = structMod;

        //equivalent to import numpy as np.
        py::module_ np = py::module_::import("numpy");
        global["np"] = np;

        //equivalent to from numpy.linalg import eig
        py::module_ linalg = py::module_::import("numpy.linalg");
        global["eig"] = linalg.attr("eig");

        //equivalent to from numpy.linalg import eig
        global["norm"] = linalg.attr("norm");

        for (const string &file: files) {
            unsigned int row,col;
            vector<unsigned char> array;

            //Convert the image to an array of unsigned chars (pixel 0: R,G,B,A; pixel 1: R,G,B,A;....)
            if (!imageToArray(file, array, row, col)) {
                cerr << "Could not convert file " << file << " to a character array! Skipping..." << endl;
                continue;
            }

            //3. Cast the required arguments to python variables.
            global["fileLocation"] = py::cast(&file);
            global["fileLim"] = py::cast(sizeNum);
            global["charArray"] = py::cast(&array);
            global["sizeRow"] = py::cast(row);
            global["sizeColumn"] = py::cast(col);

            //4. Run the python script.
            try {
                eval_file(scriptLocation, global, local);
            }
            catch(py::error_already_set& exception){
                cerr << "Program encountered an issue when running " << scriptLocation << endl;
                exception.trace();
            }
        }
    }

    else{
        cerr << "SVD Algorithm was not found!" << endl;
        return;
    }
}

bool sizeToBytes(const string& size, unsigned long long& sizeNum){
    //1. Isolate the character for kilo/megabyte and the rest of the string for numbers.
    unsigned int labelPos = size.length()-1;
    char sizeLabel = size.at(labelPos);

    string sizeNumString = size.substr(0,labelPos);
    try{
        sizeNum = stoi(sizeNumString);
    }
    catch(invalid_argument& invalidArgument){
        cerr << "Size argument was not formatted correctly!" << endl;
    }
    catch(out_of_range& outOfRange){
        cerr << "Size argument is too big!" << endl;
    }

    //Adjust the value of the size based on if it is kilobytes or megabytes.
    switch(sizeLabel){
        case 'b':{}
        case 'B':{
            break;
        }

        case 'k':{}
        case 'K':{
            sizeNum *= 1024;
            break;
        }

        //Convert megabytes to kilobytes.
        case 'm':{}
        case 'M':{
            sizeNum *= (1024 * 1024);
            break;
        }

        default:{
            cerr << "Size is not in megabytes or kilobytes!" << endl;
            return false;
        }

    }
    return true;
}

void removeBadSizes(const unsigned int& fileSize, set<string>& files){
    unsigned int removed = 0;
    set<string> newFiles;
    //1. Go through every file location in the file list.
    for (const auto & iter : files){
        //2. Make a directory entry for the file.
        fs::directory_entry file(iter.data());

        //3. Using the directory entry, check the file size of the file with the fileSize here.
        auto actualSize = file.file_size();
        unsigned long long fileSizeBytes = fileSize;

        if (actualSize < fileSizeBytes){
            cerr << "File " << file.path().string() << " is smaller than the target for compression! Removing from file list..." << endl;
            removed++;
        }
        else{
            newFiles.insert(file.path().string());
        }
    }

    files.swap(newFiles);

    cout << "Removed " << removed << " files that were smaller than the size target." << endl;
}

bool imageToArray(const string& fileLocation, vector<unsigned char>& array, unsigned int& rows, unsigned int& cols){
    //1. Create a sf image for the file.
    sf::Image image;

    //2. Load the image from the file.
    if (!image.loadFromFile(fileLocation)){
        cerr << "Image " << fileLocation << " could not be loaded!" << endl;
        return false;
    }

    //3. Get the number of bytes, make a suitable array, and get a pointer to the RGBA array.
    unsigned long long numBytes = image.getSize().x * image.getSize().y * 4;

    rows = image.getSize().x;
    cols= image.getSize().y;

    array.resize(numBytes);
    auto* pointer = image.getPixelsPtr();

    //4. Loop through all indies of the RGBA array and copy the values to our array.
    for (unsigned long long i = 0; i < numBytes; i++){
        array.at(i) = *(pointer++);
    }

    return true;
}