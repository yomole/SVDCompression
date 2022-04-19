#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include <set>
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/eval.h>
#include <pybind11/numpy.h>
#include <pybind11/embed.h>
#include <pybind11/stl.h>
#include <SFML/Graphics.hpp>

namespace py = pybind11;
namespace fs = std::filesystem;

using std::string;
using std::cerr;
using std::set;
using std::vector;
using std::cout;
using std::endl;
using std::ifstream;
using std::getline;
using std::stoi;
using std::istringstream;
using std::invalid_argument;
using std::out_of_range;
using std::string_view;
using fs::exists;
using py::eval_file;
using py::object;
using py::module_;
using py::cast_error;
using py::initialize_interpreter;
using py::finalize_interpreter;

//As per https://github.com/numpy/numpy/issues/8097, we must keep the interpreter alive for as long as the program is open.
//Otherwise, there will be dire consequences...
static py::scoped_interpreter* scope;

//Runs the SVD Algorithm python script with size and file list arguments.
void SVDAlgorithm(const string& size, set<string>& files, const string& scriptLocation);

//Takes a size argument and converts it into kilobytes (a number and a label).
bool sizeToBytes(const string& size, unsigned long long& sizeNum);

//Removes all files that are smaller than this file size.
void removeBadSizes(const unsigned int& fileSize, set<string>& files);

//Converts the file to an array of unsigned characters.
bool imageToArray(const string& fileLocation, vector<unsigned char>& array, unsigned int& rows, unsigned int& cols);