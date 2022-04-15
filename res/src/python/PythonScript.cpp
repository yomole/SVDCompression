#include "PythonScript.h"

//https://docs.python.org/3/extending/embedding.html
//https://stackoverflow.com/questions/3654652/why-does-the-python-c-api-crash-on-pyrun-simplefile
//https://pybind11.readthedocs.io/en/stable/advanced/pycpp/utilities.html#eval
//https://github.com/pybind/pybind11/issues/1543
//https://pybind11.readthedocs.io/en/stable/advanced/cast/stl.html
//https://pybind11.readthedocs.io/en/stable/advanced/cast/overview.html

/* THANK YOU AOLOE!!!!!!!!!!
 * https://github.com/aoloe/cpp-pybind11-playground/tree/master/eval-file
 */

void SVDAlgorithm(const string &size, set<string> &files){
    string SVDPython = "res/python/SVD.py";
    unsigned int sizeNum = 0;

    //If we cannot convert the size to kilobytes, or the size isn't valid, we cannot continue with the algorithm.
    if (!sizeToKilobytes(size, sizeNum)){
        return;
    }

    else if (sizeNum == 0){
        cerr << "Compression target size cannot be 0!" << endl;
        return;
    }

    else if (files.empty()){
        cerr << "There are no files in the file list!" << endl;
        return;
    }

    //Remove files from the file list that are smaller than the cutoff size.
    removeBadSizes(sizeNum, files);

    //1. Check if the file exists.
    if (exists(SVDPython)){

    //2. Import modules used in python file.
    auto modules = py::dict();

    //equivalent to import numpy as np.
    py::module_ np = py::module_::import("numpy");
    modules["np"] = np;

    //equivalent to from numpy.linalg import eig
    py::module_ linalg = py::module_::import("numpy.linalg");
    modules["eig"] = linalg.attr("eig");

    //3. Cast the file list to a python argument.
    auto arguments = py::dict();
    arguments["fileList"] = py::cast(&files);

    //4. Run the python script.
        try {
            eval_file(SVDPython, modules, arguments);
            //TODO: Cast to appropriate C++ object.
        }
        catch(cast_error& castError){
            cerr << "There was a problem when casting return of SVD algorithm to a C++ data object!" << endl;
        }
    }

    else{
        cerr << "SVD Algorithm was not found!" << endl;
        return;
    }
}

bool sizeToKilobytes(const string& size, unsigned int& sizeNum){
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
        case 'k':{}
        case 'K':{
            break;
        }

        //Convert megabytes to kilobytes.
        case 'm':{}
        case 'M':{
            sizeNum *= 1024;
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
    //1. Go through every file location in the file list.
    for (auto iter = files.begin(); iter != files.end(); iter++){
        //2. Make a directory entry for the file.
        fs::directory_entry file(iter->data());

        //3. Using the directory entry, check the file size of the file with the fileSize here.
        auto actualSize = file.file_size();
        unsigned long long fileSizeBytes = fileSize * 1024;

        if (actualSize < fileSizeBytes){
            cerr << "File " << file.path() << " is smaller than the target for compression! Removing from file list..." << endl;
            files.erase(file.path().string());
            iter = files.begin();
            removed++;
        }
    }

    cout << "Removed " << removed << " files that were smaller than the size target." << endl;
}