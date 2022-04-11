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

void runPy(const string& fileLocation){
    //1. Initialize python interpreter.
    scoped_interpreter python;

    //1. Check that the file exists. If so, evaluate it.
    if (exists(fileLocation)){
        eval_file(fileLocation);
    }

    else{
        cerr << "Python script at " << fileLocation << " does not exist!";
        return;
    }
}

void runPy(const string& fileLocation, set<string>& files){
    //1. Create a vector from the set.
    vector<string> iHatePython;
    iHatePython.reserve(files.size());
for (const string& i : files){
        iHatePython.push_back(i);
    }

    //2. Initialize python interpreter.
    scoped_interpreter python{};

    auto arguments = py::dict();
    arguments["fileList"] = py::cast(iHatePython);

    //3. Check that the python file exists, and run the python script.
    if (exists(fileLocation)){
        eval_file(fileLocation, py::globals(), arguments);
    }
    else{
        cerr << "Python script at " << fileLocation << " does not exist!";
        return;
    }
}