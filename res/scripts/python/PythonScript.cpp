#include "PythonScript.h"

//https://docs.python.org/3/extending/embedding.html
//https://stackoverflow.com/questions/3654652/why-does-the-python-c-api-crash-on-pyrun-simplefile
void runPy(const string& fileLocation){
    //1. Initialize the python environment.
    Py_Initialize();

    //2. Create the prerequisites to open the file...
    PyObject* obj = Py_BuildValue("s", fileLocation.c_str());
    FILE* file = _Py_fopen_obj(obj, "r+");

    //3. Check that the file pointer isn't null, and run the python script.
    if (file){
        PyRun_SimpleFile(file, fileLocation.c_str());
    }
    else{
        cerr << "Python script at " << fileLocation << " does not exist!";
        return;
    }

    // Terminate the python environment.
    Py_Finalize();
}