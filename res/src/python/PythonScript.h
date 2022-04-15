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

namespace py = pybind11;
namespace fs = std::filesystem;

using std::string;
using std::cerr;
using std::set;
using std::vector;
using std::cout;
using std::endl;
using std::stoi;
using std::invalid_argument;
using std::out_of_range;
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
void SVDAlgorithm(const string& size, set<string>& files);

//Takes a size argument and converts it into kilobytes (a number and a label).
bool sizeToKilobytes(const string& size, unsigned int& sizeNum);

//Removes all files that are smaller than this file size.
void removeBadSizes(const unsigned int& fileSize, set<string>& files);